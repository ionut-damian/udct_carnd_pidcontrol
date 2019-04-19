#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"

#include "Twiddle.h"

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s)
{
    auto found_null = s.find("null");
    auto b1 = s.find_first_of("[");
    auto b2 = s.find_last_of("]");
    if (found_null != string::npos)
    {
        return "";
    }
    else if (b1 != string::npos && b2 != string::npos)
    {
        return s.substr(b1, b2 - b1 + 1);
    }
    return "";
}

int main()
{
    uWS::Hub h;

    /**
     * Initialize the pid variable.
     */
    Twiddle twiddle(0); //our parameter optimizer
    twiddle.params = { 0.2, 0, 3.0 };
    twiddle.dparams = { 0.1, 0.001, 0.5 };

    PID pid;
    pid.Init(twiddle.params[0], twiddle.params[1], twiddle.params[2]);

    int count = 0;
    double total_error = 0;

#ifdef _MSC_VER    
    h.onMessage([&pid, &twiddle, &count, &total_error](uWS::WebSocket<uWS::SERVER>* ws, char *data, size_t length, uWS::OpCode opCode)
#else
    h.onMessage([&pid, &twiddle, &count, &total_error](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode)
#endif
    {
        // "42" at the start of the message means there's a websocket message event.
        // The 4 signifies a websocket message
        // The 2 signifies a websocket event
        if (length && length > 2 && data[0] == '4' && data[1] == '2')
        {
            auto s = hasData(string(data).substr(0, length));

            if (s != "")
            {
                auto j = json::parse(s);

                string event = j[0].get<string>();

                if (event == "telemetry")
                {
                    // j[1] is the data JSON object
                    double cte = std::stod(j[1]["cte"].get<string>());
                    double speed = std::stod(j[1]["speed"].get<string>());
                    double angle = std::stod(j[1]["steering_angle"].get<string>());
                    double steer_value;
                    /**
                     * TODO: Calculate steering value here, remember the steering value is
                     *   [-1, 1].
                     * NOTE: Feel free to play around with the throttle and speed.
                     *   Maybe use another PID controller to control the speed!
                     */

                    //perform parameter optimization
                    
                    count++;
                    int num_steps = 400;

                    if (count > num_steps)
                    {
                        total_error += pow(cte, 2);
                    }
                    
                    if (count > 2* num_steps)
                    {
                        twiddle.update(total_error / num_steps);
                        printf("{%.4f, %.5f, %.4f} -> best error: %.6f (#%d, param %d, phase %s)\n", 
                            twiddle.params[0], twiddle.params[1], twiddle.params[2],
                            twiddle.best_err,
                            twiddle.steps, twiddle.current_param, twiddle.Phase_str[twiddle.current_phase]);

                        pid.Init(twiddle.params[0], twiddle.params[1], twiddle.params[2]);
                        
                        total_error = 0;
                        count = 0;
                    }

                    pid.UpdateError(cte);
                    steer_value = -pid.TotalError();

                     // DEBUG
                    //std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

                    json msgJson;
                    msgJson["steering_angle"] = steer_value;
                    msgJson["throttle"] = (twiddle.steps > 100) ? 0.5 : 0.3; //accelerate after the optimization phase
                    auto msg = "42[\"steer\"," + msgJson.dump() + "]";
                    //std::cout << msg << std::endl;
#ifdef _MSC_VER      
                    ws->send(msg.data(), msg.length(), uWS::OpCode::TEXT); //vs
#else
                    ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT); //gcc
#endif
                }  // end "telemetry" if
            }
            else
            {
                // Manual driving
                string msg = "42[\"manual\",{}]";
#ifdef _MSC_VER      
                ws->send(msg.data(), msg.length(), uWS::OpCode::TEXT); //vs
#else
                ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT); //gcc
#endif
            }
        }  // end websocket message if
    }); // end h.onMessage

#ifdef _MSC_VER      
    h.onConnection([&h](uWS::WebSocket<uWS::SERVER>* ws, uWS::HttpRequest req) //vs
#else
    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) //gcc
#endif
    {
        std::cout << "Connected!!!" << std::endl;
    });

#ifdef _MSC_VER      
    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER>* ws, int code, char *message, size_t length) //vs
    {
        ws->close();
        std::cout << "Disconnected" << std::endl;
    });
#else
    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) //gcc
    {
        ws.close();
        std::cout << "Disconnected" << std::endl;
    });
#endif

    int port = 4567;
    auto host = "127.0.0.1";
    if (h.listen(host, port))
    {
        std::cout << "Listening to port " << port << std::endl;
    }
    else
    {
        std::cerr << "Failed to listen to port" << std::endl;
        return -1;
    }

    h.run();
}
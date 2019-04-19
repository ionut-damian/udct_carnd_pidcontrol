#include <vector>


#pragma once
class Twiddle
{
public:
    enum Phase
    {
        INIT,
        INCREMENT,
        DECREMENT
    };

    const char* Phase_str[3]
    {
        "INIT",
        "INCREMENT",
        "DECREMENT"
    };


    Twiddle(double threshold);
    ~Twiddle();

    void update(double total_error);

    std::vector<double> params;
    std::vector<double> dparams;

    double best_err;
    double threshold;

    int current_param;
    Phase current_phase;

    int steps;
};


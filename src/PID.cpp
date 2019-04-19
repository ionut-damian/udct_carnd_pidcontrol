#include "PID.h"
#include <math.h>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_)
{
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;

    p_error = 0;
    p_error_prev = 0;
    d_error = 0;
    i_error = 0;

    firstUpdate = true;
}

void PID::UpdateError(double cte)
{
    p_error_prev = p_error;
    p_error = cte;

    d_error = firstUpdate ? 0 : p_error - p_error_prev;

    i_error += cte;

    firstUpdate = false;
}

double PID::TotalError()
{
    return Kp * p_error + Kd * d_error + Ki * i_error;
}
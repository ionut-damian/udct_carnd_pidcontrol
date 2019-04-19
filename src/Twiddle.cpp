#include "Twiddle.h"



Twiddle::Twiddle(double threshold_) : threshold(threshold_)
{
    params = { 0,0,0 };
    dparams = { 1, 1, 1 };

    best_err = 99999;

    current_param = 0;
    current_phase = INIT;

    steps = 0;
}


Twiddle::~Twiddle()
{
}


void Twiddle::update(double total_error)
{
    double sum = 0;
    for (int i = 0; i < dparams.size(); i++)
        sum += dparams[i];

    if (sum < threshold)
        return; //stop when optimization is "done"

    switch (current_phase)
    {
    case INIT:
        params[current_param] += dparams[current_param];
        current_phase = INCREMENT;
        break;

    case INCREMENT:
        if (total_error < best_err)
        {
            best_err = total_error;
            dparams[current_param] *= 1.1;

            current_phase = INIT;
            if (current_param == params.size() - 1)
            {
                current_param = 0;
                steps++;
            }
            else
            {
                current_param++;
            }
        }
        else
        {
            params[current_param] -= 2* dparams[current_param];
            current_phase = DECREMENT;
        }
        break;

    case DECREMENT:
        if (total_error < best_err)
        {
            best_err = total_error;
            dparams[current_param] *= 1.1;

            current_phase = INIT;
            if (current_param == params.size() - 1)
            {
                current_param = 0;
                steps++;
            }
            else
            {
                current_param++;
            }
        }
        else
        {
            params[current_param] += dparams[current_param]; //reset param
            dparams[current_param] *= 0.9;

            current_phase = INIT;
            if (current_param == params.size() - 1)
            {
                current_param = 0;
                steps++;
            }
            else
            {
                current_param++;
            }
        }
        break;
    }
}

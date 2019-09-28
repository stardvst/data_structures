#include <math.h>
#include <stdlib.h>

double calculate(double input)
{
    //return sqrt(rand() * input);
    return 0;
}

double O_n(unsigned int iterations)
{
    double ops = 0;
    for(unsigned int i = 0; i < iterations; i++)
    {
        calculate(i);
        ops++;
    }

    return ops;
}

double O_n_2(unsigned int iterations)
{
    double ops = 0;
    for(unsigned int i = 0; i < iterations; i++)
    {
        ops += O_n(iterations);
    }

    return ops;
}

double O_n_3(unsigned int iterations)
{
    double ops = 0;
    for(unsigned int i = 0; i < iterations; i++)
    {
        ops += O_n_2(iterations);
    }

    return ops;
}

double O_log_n(unsigned int iterations)
{
    iterations = (unsigned int)log(iterations);
    double ops = 0;
    for(unsigned int i = 0; i < iterations; i++)
    {
        calculate(i);
        ops++;
    }

    return ops;
}

double O_n_log_n(unsigned int iterations)
{
    iterations = iterations * (unsigned int)log(iterations);
    double ops = 0;
    for(unsigned int i = 0; i < iterations; i++)
    {
        calculate(i);
        ops++;
    }

    return ops;
}

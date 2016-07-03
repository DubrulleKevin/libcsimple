#include "utils.h"


unsigned int umax(unsigned int a, unsigned int b)
{
    return a > b ? a : b;
}

bool_t double_equals(double a, double b)
{
    const double epsilon = 0.000001f;

    return fabs(a - b) < epsilon ? TRUE : FALSE;
}

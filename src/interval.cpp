
#include <interval.hpp>

static const Interval empty(R_INFINITY, -R_INFINITY);
static const Interval universe(-R_INFINITY, R_INFINITY);

double Interval::clamp(double x) const
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
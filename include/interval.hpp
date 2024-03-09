#ifndef INTERVAL_H
#define INTERVAL_H

#include <constants.hpp>

class Interval {

public:
    double min, max;

    Interval() 
        : min(R_INFINITY), max(-R_INFINITY) {} // default interval in empty

    Interval(double in_min, double in_max) : min(in_min), max(in_max) {}

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x  < max;
    }

    double clamp(double x) const;

    static const Interval empty, universe;
};



#endif
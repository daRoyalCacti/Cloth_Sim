//
// Created by jacob on 24/1/21.
//

#ifndef CLOTH_SIM_COMMON_H
#define CLOTH_SIM_COMMON_H

#include <array>
#include <cmath>
#include <numeric>

inline double distance(const std::array<double, 3> a, const std::array<double, 3> b) {
    //computes the Euclidian distance between 2 points in R3
    return std::sqrt( std::transform_reduce(a.begin(), a.end(), b.begin(), 0,   //could also use std::inner_product
                                         [](const double &x, const double &y){return x+y;},
                                         [](const double &x, const double &y){return (x-y)*(x-y);}));
}

inline double length(std::array<double, 3> x) {
    return std::sqrt( x[0]*x[0] + x[1]*x[1] + x[2]*x[2] );
    /*return std::sqrt( std::inner_product(x.begin(), x.end(), x.begin(), 0,
                [](const double &x, const double &y){return x+y;},
                [](const double &x, const double &y){return x*y;}));*/
}

inline std::array<double, 3> normalize(const std::array<double, 3> x) {
    const auto l_inv = 1/length(x);
    return {x[0]*l_inv, x[1]*l_inv, x[2]*l_inv};
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


#endif //CLOTH_SIM_COMMON_H

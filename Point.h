//
// Created by jacob on 24/1/21.
//

#ifndef CLOTH_SIM_POINT_H
#define CLOTH_SIM_POINT_H

#include <array>

class Point {
public:
    std::array<double, 3> pos{};
    std::array<double, 3> prev_pos{};
    std::array<double, 3> vel{0, 0, 0};
    std::array<double, 3> force{0,0,0};
    const double m = 1;

    const bool is_fixed = true;

    Point() = default;
    Point(const double x, const double y, const double z, bool fixed, const double mass = 1) : pos{x, y, z}, prev_pos{x, y, z}, is_fixed(fixed), m(mass) {}

    inline void update(const double x, const double y, const double z, const double timestep) {
        const double inv_2t = 1 / (2 * timestep);
        //using central distance method
        vel[0] = (x - prev_pos[0]) * inv_2t;
        vel[1] = (y - prev_pos[1]) * inv_2t;
        vel[2] = (z - prev_pos[2]) * inv_2t;
        prev_pos = pos;
        pos = {x, y, z};
    }
};


#endif //CLOTH_SIM_POINT_H

//
// Created by jacob on 25/1/21.
//

#ifndef CLOTH_SIM_FORCE_H
#define CLOTH_SIM_FORCE_H

#include <array>
#include "Point.h"
#include <cmath>
#include <memory>

struct force {
    [[nodiscard]] virtual std::array<double, 3> evaluate(std::shared_ptr<Point>, double) const = 0;
};

namespace e_force {
    struct gravity : public force {
        [[nodiscard]] std::array<double, 3> evaluate(const std::shared_ptr<Point> p, const double t) const override {
            return {0, 0, p->m * -9.81};
        }
    };

    struct damped_spring : public force {
        const double kd;
        damped_spring() = delete;
        damped_spring(const double stren) : kd(stren) {}

        [[nodiscard]] std::array<double, 3> evaluate(const std::shared_ptr<Point> p, const double t) const override {
            return {-p->vel[0] * kd, -p->vel[1] * kd, -p->vel[2] * kd};
        }
    };

    struct drag : public force {
        [[nodiscard]] std::array<double, 3> evaluate(const std::shared_ptr<Point> p, const double t) const override {
            return {sgn(p->vel[0])*p->vel[0]*p->vel[0]*0.25, sgn(p->vel[1])*p->vel[1]*p->vel[1]*0.25, sgn(p->vel[2])*p->vel[2]*p->vel[2]*0.25};
        }
    };

    struct wind : public force {
        [[nodiscard]] std::array<double, 3> evaluate(const std::shared_ptr<Point> p, const double t) const override {
            return {0.2*std::sin(0.2 * t + 0.3 * p->pos[0]), 0, 0};
        }
    };

}


#endif //CLOTH_SIM_FORCE_H

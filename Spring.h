//
// Created by jacob on 24/1/21.
//

#ifndef CLOTH_SIM_SPRING_H
#define CLOTH_SIM_SPRING_H

#include <memory>   //for shared pointer
#include <utility>

#include "Point.h"
#include "Common.h"


class Spring {
public:
    std::shared_ptr<Point> base; //base of the spring
    std::shared_ptr<Point> conn; //end point of the spring
    double initial_length = -1; //should always be positive
    const double k = -1;

    Spring() = default;
    Spring(std::shared_ptr<Point> b, std::shared_ptr<Point> c, const double stren) :base(std::move(b)), conn(std::move(c)), k(stren) {
        initial_length = distance(base->pos, conn->pos);
    }

    inline double get_length() const {
        return distance(base->pos, conn->pos);
    }

      inline std::array<double, 3> force_exerted() const {
        const auto mag_force = k*(get_length() - initial_length);
        const std::array<double, 3> dir_vec = normalize({base->pos[0] - conn->pos[0], base->pos[1] - conn->pos[1], base->pos[2] - conn->pos[2]});
    /*
        std::cout << mag_force << " " << k << " " << get_length() << " " << initial_length << " (" << dir_vec[0] << ", " << dir_vec[1] << ", " << dir_vec[2] << ")\n";
        std::cout << "\t(" <<  base->pos[0] << ", " << base->pos[1] << ", " << base->pos[2] << ")  (" << conn->pos[0] << ", " << conn->pos[1] << ", " << conn->pos[2] << ") ("
        <<  base->pos[0] - conn->pos[0] << ", " << base->pos[1] - conn->pos[1] << ", " << base->pos[2] - conn->pos[2] << ")\n";
        std::cout << length({base->pos[0] - conn->pos[0], base->pos[1] - conn->pos[1], base->pos[2] - conn->pos[2]}) << '\n';
*/
        return {dir_vec[0]*mag_force, dir_vec[1]*mag_force, dir_vec[2]*mag_force};
    }



};


#endif //CLOTH_SIM_SPRING_H

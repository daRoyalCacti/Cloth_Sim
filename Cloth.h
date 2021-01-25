//
// Created by jacob on 24/1/21.
//

#ifndef CLOTH_SIM_CLOTH_H
#define CLOTH_SIM_CLOTH_H

#include "Grid.h"
#include <utility>
#include <vector>

template<size_t width, size_t height>
class Cloth {
public:
    Grid<width, height> grid;

    //set using external functions because a spring requires a pointer to a point
    // - in this case this means that the vectors of springs must reference grid
    // - it generally requires the grid to set the functions so might as well set them there
    std::vector<Spring> springs;

    Cloth() = default;
    Cloth(Grid<width, height> g, const double struc_stren, const double shear_stren, const double bend_stren)
        : grid(g), struc_k(struc_stren), shear_k(shear_stren), bend_k(bend_stren) {}


    const double struc_k = -1;
    const double shear_k = -1;
    const double bend_k = -1;
};

/*
template<size_t width, size_t height>
void set_rec_old_springs(Cloth<width, height> &cloth) {
    set_rec_old_struc_springs(cloth);
    set_rec_old_shear_springs(cloth);
    set_rec_old_bend_springs(cloth);
}

template<size_t width, size_t height>
void set_rec_old_struc_springs(Cloth<width, height> &cloth) {
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const auto index = Grid<width, height>::id_at(i, j);
            const auto left = Grid<width, height>::id_at(i - 1, j);
            const auto right = Grid<width, height>::id_at(i + 1, j);
            const auto up = Grid<width, height>::id_at(i, j - 1);
            const auto down = Grid<width, height>::id_at(i, j + 1);

            const bool can_left = i - 1 > 0;
            const bool can_right = i + 1 < width;
            const bool can_up = j - 1 > 0;
            const bool can_down = j + 1 < height;
            if (can_left) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[left], cloth.struc_k );
            }
            if (can_right) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[right], cloth.struc_k );
            }
            if (can_up) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[up], cloth.struc_k );
            }
            if (can_down) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[down], cloth.struc_k );
            }

        }
    }
}

template<size_t width, size_t height>
void set_rec_old_shear_springs(Cloth<width, height> &cloth) {
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const auto index = Grid<width, height>::id_at(i, j);
            const auto left_up = Grid<width, height>::id_at(i - 1, j - 1);
            const auto left_down = Grid<width, height>::id_at(i - 1, j + 1);
            const auto right_up = Grid<width, height>::id_at(i + 1, j - 1);
            const auto right_down = Grid<width, height>::id_at(i + 1, j + 1);

            const bool can_left = i - 1 > 0;
            const bool can_right = i + 1 < width;
            const bool can_up = j - 1 > 0;
            const bool can_down = j + 1 < height;
            if (can_left && can_up) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[left_up], cloth.shear_k );
            }
            if (can_left && can_down) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[left_down], cloth.shear_k );
            }
            if (can_right && can_up) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[right_up], cloth.shear_k );
            }
            if (can_right && can_down) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[right_down], cloth.shear_k );
            }

        }
    }
}

template<size_t width, size_t height>
void set_rec_old_bend_springs(Cloth<width, height> &cloth) {
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const auto index = Grid<width, height>::id_at(i, j);

            const auto left_up = Grid<width, height>::id_at(i - 2, j - 2);
            const auto left_down = Grid<width, height>::id_at(i - 2, j + 2);
            const auto right_up = Grid<width, height>::id_at(i + 2, j - 2);
            const auto right_down = Grid<width, height>::id_at(i + 2, j + 2);

            const auto left = Grid<width, height>::id_at(i - 2, j);
            const auto right = Grid<width, height>::id_at(i + 2, j);
            const auto up = Grid<width, height>::id_at(i, j - 2);
            const auto down = Grid<width, height>::id_at(i, j + 2);

            const bool can_left = i - 2 > 0;
            const bool can_right = i + 2 < width;
            const bool can_up = j - 2 > 0;
            const bool can_down = j + 2 < height;
            if (can_left && can_up) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[left_up], cloth.bend_k );
            }
            if (can_left && can_down) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[left_down], cloth.bend_k );
            }
            if (can_right && can_up) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[right_up], cloth.bend_k );
            }
            if (can_right && can_down) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[right_down], cloth.bend_k );
            }
            if (can_left) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[left], cloth.bend_k );
            }
            if (can_right) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[right], cloth.bend_k );
            }
            if (can_up) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[up], cloth.bend_k );
            }
            if (can_down) {
                cloth.springs.push_back( cloth.grid[index], cloth.grid[down], cloth.bend_k );
            }
        }
    }
}
*/


//https://creativecoding.soe.ucsc.edu/courses/cs488/finalprojects/cloth/cloth.pdf
template<size_t width, size_t height>
void set_rec_springs(Cloth<width, height> &cloth) {
    set_rec_struc_springs(cloth);
    set_rec_shear_springs(cloth);
    set_rec_bend_springs(cloth);
}

template<size_t width, size_t height>
void set_rec_struc_springs(Cloth<width, height> &cloth) {
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const auto index = Grid<width, height>::id_at(i, j);
            const auto right = Grid<width, height>::id_at(i + 1, j);
            const auto down = Grid<width, height>::id_at(i, j + 1);

            const bool can_right = i + 1 < width;
            const bool can_down = j + 1 < height;

            if (can_right) {
                cloth.springs.push_back( Spring(cloth.grid.points[index], cloth.grid.points[right], cloth.struc_k) );
            }

            if (can_down) {
                cloth.springs.push_back( Spring(cloth.grid.points[index], cloth.grid.points[down], cloth.struc_k) );
            }

        }
    }
}

template<size_t width, size_t height>
void set_rec_shear_springs(Cloth<width, height> &cloth) {
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const auto index = Grid<width, height>::id_at(i, j);

            const auto right = Grid<width, height>::id_at(i + 1, j);
            const auto down = Grid<width, height>::id_at(i, j + 1);

            const auto right_down = Grid<width, height>::id_at(i + 1, j + 1);

            const bool can_right = i + 1 < width;
            const bool can_down = j + 1 < height;
            if (can_right && can_down) {
                cloth.springs.push_back( Spring(cloth.grid.points[index], cloth.grid.points[right_down], cloth.shear_k ));
                cloth.springs.push_back( Spring(cloth.grid.points[down], cloth.grid.points[right], cloth.shear_k ));
            }


        }
    }
}

template<size_t width, size_t height>
void set_rec_bend_springs(Cloth<width, height> &cloth) {
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const auto index = Grid<width, height>::id_at(i, j);

            const auto right_down = Grid<width, height>::id_at(i + 2, j + 2);

            const auto right = Grid<width, height>::id_at(i + 2, j);
            const auto down = Grid<width, height>::id_at(i, j + 2);

            const bool can_right = i + 2 < width;
            const bool can_down = j + 2 < height;

            if (can_right && can_down) {
                cloth.springs.push_back( Spring(cloth.grid.points[index], cloth.grid.points[right_down], cloth.bend_k ));
                cloth.springs.push_back( Spring(cloth.grid.points[down], cloth.grid.points[right], cloth.bend_k ));
            }
            if (can_right) {
                cloth.springs.push_back( Spring(cloth.grid.points[index], cloth.grid.points[right], cloth.bend_k ));
            }
            if (can_down) {
                cloth.springs.push_back( Spring(cloth.grid.points[index], cloth.grid.points[down], cloth.bend_k ));
            }


        }
    }
}


#endif //CLOTH_SIM_CLOTH_H

//
// Created by jacob on 24/1/21.
//

#ifndef CLOTH_SIM_GRID_H
#define CLOTH_SIM_GRID_H

#include <cstdio>
#include <utility>
#include <vector>
#include <memory>
#include <fstream>

#include "Spring.h"

template <size_t width, size_t height>
class Grid {
public:
    static constexpr size_t w = width;
    static constexpr size_t h = height;

    std::array<std::shared_ptr<Point>, width*height> points;

    constexpr static unsigned id_at(unsigned int x, unsigned int y) {
        return y*width + x;
    }

    Grid() = default;
    explicit Grid(const std::array<std::shared_ptr<Point>, width*height> p) : points(p) {}
};

template<size_t width, size_t height>
constexpr std::array<bool, width*height> top_row_fixed() {
    std::array<bool, width*height> ret_val{};
    for (int i = 0; i < width; i++) {
        ret_val[Grid<width, height>::id_at(i,0)] = true;
    }
    return ret_val;
}


template<size_t width, size_t height>
std::array<std::shared_ptr<Point>, width*height> vertical_cloth(const std::array<bool, width*height> fixed, const double point_mass, const double h_gap = 1, const double v_gap = 1) {
    //h_gap = horizontal gap between points
    //v_gap = vertical gap between points
    const double max_height = h_gap * height;

    std::array<std::shared_ptr<Point>, width*height> ret_val;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            const auto id = Grid<width, height>::id_at(i, j);
            ret_val[id] = std::make_shared<Point>( i*h_gap, 0, max_height - j*v_gap, fixed[id], point_mass);  //left to right, top to bottom
        }
    }

    return ret_val;
}

template<size_t width, size_t height>
void write_grid(const Grid<width, height> grid, const char* file_loc) {
    std::ofstream output(file_loc);

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const auto index = Grid<width, height>::id_at(i, j);
            output << grid.points[index]->pos[0] << ' ' << grid.points[index]->pos[1] << ' ' << grid.points[index]->pos[2] << '\n';
        }
    }
}

#endif //CLOTH_SIM_GRID_H

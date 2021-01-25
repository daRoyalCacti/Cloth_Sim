#include <iostream>

#include "Cloth.h"
#include "force.h"
#include "integrate.h"
#include <chrono>


constexpr size_t width = 16;
constexpr size_t height = 9;
constexpr double timestep = 1e-5;
constexpr double end_time = 1;
constexpr unsigned steps = end_time / timestep;



constexpr double struct_spring_k = 3e-2;//10;
constexpr double shear_spring_k = 1e-30;//1;
constexpr double bend_spring_k = 1e-30;//0.01;

constexpr double point_mass = 0.001;



int main() {
    Grid<width, height> grid(vertical_cloth<width, height>(top_row_fixed<width, height>(), point_mass) );

    Cloth cloth(grid, struct_spring_k, shear_spring_k, bend_spring_k);

    set_rec_springs(cloth);

    velet V(cloth, timestep);

    V.set_forces(std::make_shared<e_force::gravity>(), std::make_shared<e_force::damped_spring>(0.1));
    try {
        V.integrate(steps);
        write_grid(grid, "../frame_data/test.txt");
    } catch (const std::runtime_error &s) {
        std::cerr << "Runtime error : " << s.what() << std::endl;
        write_grid(grid, "../frame_data/failed.txt");
    }


    return 0;
}
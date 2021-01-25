//
// Created by jacob on 25/1/21.
//

#ifndef CLOTH_SIM_INTEGRATE_H
#define CLOTH_SIM_INTEGRATE_H

#include <vector>
#include <memory>
#include "force.h"
#include "Cloth.h"
#include <stdexcept>
#include <iomanip>

struct integrator {
    virtual void integrate(unsigned num_steps) const = 0;
};

template<size_t width, size_t height>
struct velet : public integrator {
    std::vector<std::shared_ptr<force>> forces;
    Cloth<width, height> cloth;
    const double timestep;

    template<typename ...T>
    inline void set_forces(const T& ... f) {
        (void)std::initializer_list<int>{ (forces.push_back(f), 0)... };
    }


    velet(const Cloth<width, height> &c, const double delta_t) : cloth(c), timestep(delta_t){}

    void integrate(const unsigned num_steps) const override {
        double time = 0;
        unsigned counter = 0;
        std::cout << std::flush;
#pragma omp parallel for private(time) shared(counter)
        for (unsigned n = 0; n < num_steps; n++) {
            counter++;
            if (counter % 1000 == 0) {
                std::cout << std::setprecision(3) << "\rmain loop : " << 100 * counter / (double)num_steps << '%'<< std::flush;
            }
            time += timestep;



            //evaluating spring forces
            for (auto &s : cloth.springs) {
                const auto current_force = s.force_exerted();
                s.base->force[0] += current_force[0];
                s.base->force[1] += current_force[1];
                s.base->force[2] += current_force[2];

                s.conn->force[0] -= current_force[0];   //"-=" because force points in the opposite direction
                s.conn->force[1] -= current_force[1];
                s.conn->force[2] -= current_force[1];

#ifndef NDEBUG
                if (!std::isfinite(current_force[0])) {
                    std::cerr << "spring force x : " << current_force[0] << "\ttime = " << time << '\n';
                    throw std::runtime_error("spring force is infinite");
                }
                if (!std::isfinite(current_force[1])) {
                    std::cerr << "spring force y : " << current_force[1] << "\ttime = " << time << '\n';
                    throw std::runtime_error("spring force is infinite");
                }
                if (!std::isfinite(current_force[0])) {
                    std::cerr << "spring force z : " << current_force[2] << "\ttime = " << time << '\n';
                    throw std::runtime_error("spring force is infinite");
                }
#endif
            }


            //evaluating external forces
            // and integrating
            for (size_t i = 0; i < width; i++) {
                for (size_t j = 0; j < height; j++) {
                    const auto index = Grid<width, height>::id_at(i, j);

                    for (const auto& f : forces) {
                        const auto current_force = f->evaluate(cloth.grid.points[index], time);
                        cloth.grid.points[index]->force[0] += current_force[0];
                        cloth.grid.points[index]->force[1] += current_force[1];
                        cloth.grid.points[index]->force[2] += current_force[2];
#ifndef NDEBUG
                        if (!std::isfinite(current_force[0])) {
                            std::cerr << "external force x : " << current_force[0] << "\ttime = " << time << '\n';
                            throw std::runtime_error("external force is infinite");
                        }
                        if (!std::isfinite(current_force[1])) {
                            std::cerr << "external force y : " << current_force[1] << "\ttime = " << time << '\n';
                            throw std::runtime_error("external force is infinite");
                        }
                        if (!std::isfinite(current_force[0])) {
                            std::cerr << "external force z : " << current_force[2] << "\ttime = " << time << '\n';
                            throw std::runtime_error("external force is infinite");
                        }
#endif
                    }



                    //integrating
                    if (!cloth.grid.points[index]->is_fixed) {
                        cloth.grid.points[index]->update(
                                2 * cloth.grid.points[index]->pos[0] - cloth.grid.points[index]->prev_pos[0] + cloth.grid.points[index]->force[0] * timestep * timestep / cloth.grid.points[index]->m,
                                2 * cloth.grid.points[index]->pos[1] - cloth.grid.points[index]->prev_pos[1] + cloth.grid.points[index]->force[1] * timestep * timestep / cloth.grid.points[index]->m,
                                2 * cloth.grid.points[index]->pos[2] - cloth.grid.points[index]->prev_pos[2] + cloth.grid.points[index]->force[2] * timestep * timestep / cloth.grid.points[index]->m,
                                timestep);
                    }


                    //clean up
                    cloth.grid.points[index]->force = {0, 0, 0};
                }
            }




        }

        std::cout << "\rmain loop : " << 100 << '%'<< std::flush;

    }
};


#endif //CLOTH_SIM_INTEGRATE_H

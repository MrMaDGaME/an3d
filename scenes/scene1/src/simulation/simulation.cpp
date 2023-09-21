#include "simulation.hpp"

using namespace cgp;

void simulate(particle_structure &particle, const std::vector<plane_structure *> &ground, float dt) {
    vec3 const g = {0, 0, -9.81f};
    vec3 const f = particle.m * g;
    particle.v = (1 - 0.9f * dt) * particle.v + dt * f;
    particle.p = particle.p + dt * particle.v;

    // To do :
    //  Handle collision

    for (auto &plane: ground) {
        vec3 const sp = particle.p - plane->p;
        float d = dot(sp, plane->n);
        if (d < particle.r) {
            particle.p = particle.p + (particle.r - d) * plane->n;
            particle.v = particle.v - 2 * dot(particle.v, plane->n) * plane->n;
        }
    }

}

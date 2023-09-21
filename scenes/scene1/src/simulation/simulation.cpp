#include "simulation.hpp"

using namespace cgp;

void simulate(particle_structure &particle, const std::vector<plane_structure *> &ground, float dt) {
    vec3 const g = {0, 0, -9.81f};
    vec3 const f = particle.m * g;
    particle.v = (1 - 0.9f * dt) * particle.v + dt * f;
    particle.p = particle.p + dt * particle.v;

    // To do :
    //  Handle collision

    /*for (size_t k = 0; k < N; ++k) {
        particle_structure &particle = particles[k];
        for (size_t i = 0; i < N; ++i) {
            if (i == k) continue;
            particle_structure &other = particles[i];
            vec3 const d = particle.p - other.p;
            float const r = particle.r + other.r;
            vec3 const d_norm = normalize(d);
            if (norm(d) < r) {
                particle.p = particle.p + (r - norm(d)) * d_norm;
                other.p = other.p - (r - norm(d)) * d_norm;
                vec3 particleproj = dot(particle.v, d_norm) * d_norm;
                vec3 otherproj = dot(other.v, d_norm) * d_norm;
                particle.v = (particle.v - particleproj + otherproj);
                other.v = (other.v - otherproj + particleproj);
            }
        }
    }*/

    if (particle.p.z<-(1 - particle.r) || particle.p.z>(1 - particle.r)) {
        particle.p.z = particle.p.z < -(1 - particle.r) ? -((1 - particle.r)) : (1 - particle.r);
        particle.v.z = -particle.v.z * 0.9f;
    }
    if (particle.p.x<-(1 - particle.r) || particle.p.x>(1 - particle.r)) {
        particle.p.x = particle.p.x < -(1 - particle.r) ? -(1 - particle.r) : (1 - particle.r);
        particle.v.x = -particle.v.x * 0.9f;
    }
    if (particle.p.y<-(1 - particle.r) || particle.p.y>(1 - particle.r)) {
        particle.p.y = particle.p.y < -(1 - particle.r) ? -(1 - particle.r) : (1 - particle.r);
        particle.v.y = -particle.v.y * 0.9f;
    }

    for (auto &plane: ground) {
        vec3 const sp = plane->p - particle.p;
        float d = dot(sp, plane->n);
        if (d < particle.r) {
            particle.p = particle.p + (particle.r - d) * plane->n;
            particle.v = particle.v - 2 * dot(particle.v, plane->n) * plane->n;
        }
    }
}

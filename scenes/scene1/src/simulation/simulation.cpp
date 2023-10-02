#include "simulation.hpp"

using namespace cgp;

void simulate(particle_structure &particle, const std::vector<plane_structure *> &planes, const std::vector<sphere_structure *> &spheres, float dt) {
    vec3 const g = {0, 0, -9.81f};
    vec3 const f = particle.m * g;
    particle.v = (1 - 0.9f * dt) * particle.v + dt * f;
    particle.p = particle.p + dt * particle.v;

    // To do :
    //  Handle collision

    for (auto &plane: planes) {
        vec3 ab = plane->x2 - plane->x1;
        vec3 ac = plane->x4 - plane->x1;
        vec3 normal = cross(ab, ac);
        normal = normal / norm(normal);
        float d = dot(normal, particle.p - plane->x1);
        if (d < 0){
            normal = -normal;
            d = -d;
        }
        vec3 proj = particle.p - d * normal - plane->x1;
        float y = (proj.y * ab.x - proj.x * ab.y) / (ac.y * ab.x - ac.x * ab.y);
        if (y < 0 || y > 1) {
            continue;
        }
        float x = (proj.x - y * ac.x) / ab.x;
        if (x < 0 || x > 1) {
            continue;
        }
        if (d < particle.r) {
            particle.p = particle.p + (particle.r - d) * normal;
            particle.v = particle.v - 2 * dot(particle.v, normal) * normal * 0.9f;
//            particle.p = {0, 0, 1};
//            particle.v = {0, 0, 0};
        }
    }

    for (auto &sphere: spheres) {
        vec3 normal = particle.p - sphere->p;
        float d = norm(normal);
        if (d < particle.r + sphere->r) {
            normal = normal / d;
            particle.p = particle.p + (particle.r + sphere->r - d) * normal;
            particle.v = particle.v - 2 * dot(particle.v, normal) * normal * 0.9f;
        }
    }

    if (particle.p.z < -6) {
        particle.p = {0, 0, 1};
        particle.v = {0, 0, 0};
    }
}

#include "simulation.hpp"

using namespace cgp;

void simulate(particle_structure &particle, const std::vector<plane_structure *> &planes,
              const std::vector<sphere_structure *> &spheres,
              const std::vector<moving_sphere_structure *> &moving_spheres,
              const std::vector<cylinder_structure *> &cylinders, float dt){
    vec3 const g = {0, 0, -9.81f};
    vec3 const f = particle.m * g;
    particle.v = (1 - 0.9f * dt) * particle.v + dt * f;
    particle.p = particle.p + dt * particle.v;

    if (norm(particle.v) < 0.7f && norm(particle.p - vec3(0, 38, 0.5f)) < 0.5f){
        particle.p = {0, 0, 1};
        particle.v = {0, 0, 0};
    }

    // Collision
    // Planes
    for (auto &plane: planes) {
        vec3 ab = plane->x2 - plane->x1;
        vec3 ac = plane->x4 - plane->x1;
        vec3 normal = cross(ab, ac);
        normal = normal / norm(normal);
        float d = dot(normal, particle.p - plane->x1);
        if (d < 0) {
            normal = -normal;
            d = -d;
        }

        float detX;
        float detY;

        vec3 proj = particle.p - d * normal - plane->x1;
        float detA = ab.x * ac.y - ab.y * ac.x;
        if (detA == 0) {
            detA = ab.z * ac.y - ab.y * ac.z;
            if (detA == 0) {
                detA = ab.x * ac.z - ab.z * ac.x;
                detX = proj.x * ac.z - proj.z * ac.x;
                detY = ab.x * proj.z - ab.z * proj.x;
            }
            else {
                detX = proj.z * ac.y - proj.y * ac.z;
                detY = ab.z * proj.y - ab.y * proj.z;
            }
        }
        else {
            detX = proj.x * ac.y - proj.y * ac.x;
            detY = ab.x * proj.y - ab.y * proj.x;
        }
        // Calcul des coefficients x et y
        float x = detX / detA;
        float y = detY / detA;
        if (y < 0 || y > 1) {
            continue;
        }
        if (x < 0 || x > 1) {
            continue;
        }
        if (d < particle.r) {
            particle.p = particle.p + (particle.r - d) * normal;
            particle.v = particle.v - 2 * dot(particle.v, normal) * normal * 0.9f;
        }
    }
    // Spheres
    for (auto &sphere: spheres) {
        vec3 normal = particle.p - sphere->p;
        float d = norm(normal);
        if (d < particle.r + sphere->r) {
            normal = normal / d;
            particle.p = particle.p + (particle.r + sphere->r - d) * normal;
            particle.v = particle.v - 2 * dot(particle.v, normal) * normal * 0.9f;
        }
    }
    for (auto &moving_sphere: moving_spheres) {
        moving_sphere->t += moving_sphere->hz * dt;
        if (moving_sphere->t > 2 * M_PI) {
            moving_sphere->t -= 2 * M_PI;
        }
        moving_sphere->p = moving_sphere->p + moving_sphere->amp * sin(moving_sphere->t) * moving_sphere->axis;
        vec3 normal = particle.p - moving_sphere->p;
        float d = norm(normal);
        if (d < particle.r + moving_sphere->r) {
            normal = normal / d;
            particle.p = particle.p + (particle.r + moving_sphere->r - d) * normal;
            particle.v = particle.v - 2 * dot(particle.v, normal) * normal * 0.9f;
        }
    }

    // Cylinders
    for (auto &cylinder: cylinders) {
        vec3 v = particle.p - cylinder->p;
        vec3 proj = cylinder->p + dot(v, cylinder->v) / dot(cylinder->v, cylinder->v) * cylinder->v;
        vec3 normal = proj - particle.p;
        float d = norm(normal);
        float axis;
        if (cylinder->v.x == 0){
            if (cylinder->v.y == 0){
                axis = (proj - cylinder->p).z / cylinder->v.z;
            }
            else{
                axis = (proj - cylinder->p).y / cylinder->v.y;
            }
        }
        else{
            axis = (proj - cylinder->p).x / cylinder->v.x;
        }
        if (d < cylinder->r + particle.r && axis > 0 && axis < 1) {

            particle.p = particle.p + (particle.r - d) * normal;
            particle.v = particle.v - 2 * dot(particle.v, normal) * normal * 0.9f;
        }
    }

    // Ground
    if (particle.p.z < -6) {
        particle.p = {0, 0, 1};
        particle.v = {0, 0, 0};
    }
}

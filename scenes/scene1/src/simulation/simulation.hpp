#pragma once

#include "cgp/cgp.hpp"

struct particle_structure {
    cgp::vec3 p; // Position
    cgp::vec3 v; // Speed

    cgp::vec3 c; // Color
    float r;     // Radius
    float m;     // mass
    bool changed = false;
};
struct plane_structure {
    // Edges
    cgp::vec3 x1;
    cgp::vec3 x2;
    cgp::vec3 x3;
    cgp::vec3 x4;
    cgp::vec3 c;    // Color
};

struct sphere_structure {
    cgp::vec3 p; // Position
    cgp::vec3 c; // Color
    float r;     // Radius
};

struct moving_sphere_structure {
    cgp::vec3 p; // Position
    cgp::vec3 c; // Color
    float r;     // Radius
    float t = 0;    // Time
    float hz;   // Frequency
    float amp;    // Amplitude
    cgp::vec3 axis; // Axis
};

void simulate(particle_structure &particle, const std::vector<plane_structure *> &planes, const std::vector<sphere_structure *> &spheres, const std::vector<moving_sphere_structure *> &moving_spheres, float dt);

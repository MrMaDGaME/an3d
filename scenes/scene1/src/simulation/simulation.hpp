#pragma once

#include "cgp/cgp.hpp"

struct particle_structure {
    cgp::vec3 p; // Position
    cgp::vec3 v; // Speed

    cgp::vec3 c; // Color
    float r;     // Radius
    float m;     // mass
};
struct plane_structure {
    cgp::vec3 p;    // Position
    cgp::vec3 n;    // Normal
    cgp::vec3 c;    // Color
    float s;        // Size
};

void simulate(particle_structure &particle, const std::vector<plane_structure *> &ground, float dt);

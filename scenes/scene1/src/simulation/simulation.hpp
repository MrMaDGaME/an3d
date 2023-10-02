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
    // Edges
    cgp::vec3 x1;
    cgp::vec3 x2;
    cgp::vec3 x3;
    cgp::vec3 x4;
    cgp::vec3 c;    // Color
};

void simulate(particle_structure &particle, const std::vector<plane_structure *> &planes, float dt);

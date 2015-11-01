#pragma once
#include <algorithm>

struct Particle
{
    Particle() = default;
    Particle(float mass, float position[2], float velocity[2])
        : mass(mass)  
    {
        std::copy(position, position + 2, this->position);
        std::copy(velocity, velocity + 2, this->velocity);
    }
    Particle(const Particle&) = default;
    Particle& operator=(const Particle&) = default;

    float mass;
    float position[2];
    float velocity[2];
};

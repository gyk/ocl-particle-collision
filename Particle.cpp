#include "Particle.h"

float Particle::kineticEnergy() const
{
    return mass * (velocity[0] * velocity[0] + velocity[1] * velocity[1]) / 2;
}

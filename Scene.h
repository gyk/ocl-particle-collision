#pragma once
#include "Collision.h"

class Scene
{
public:
    Scene(float sizeX, float sizeY, int nParticles);
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    ~Scene();
    void fillWithRandom();
    Collision nextCollisionTime() const;
    Particle& getParticleAt(int index) const;

private:
    float sizeX, sizeY;
    int nParticles;
    Particle* particles;
};

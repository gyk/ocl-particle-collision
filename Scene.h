#pragma once

#include <vector>
#include "Collision.h"

class Scene
{
public:
    Scene(float sizeX, float sizeY, int nParticles);
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    ~Scene() = default;
    void fillWithRandom();
    Collision nextCollisionTime() const;
    void collideAndUpdate(Collision colli);
    Particle& getParticleAt(int index);
    const Particle& getParticleAt(int index) const;

private:
    float sizeX, sizeY;
    int nParticles;
    std::vector<Particle> particles;
};

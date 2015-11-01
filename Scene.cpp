#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <limits>
#include <utility>
#include <stdexcept>

#include "config.h"
#include "Particle.h"
#include "Scene.h"
#include "Collision.h"

Scene::Scene(float sizeX, float sizeY, int nParticles)
    : sizeX(sizeX), sizeY(sizeY), nParticles(nParticles)
{
    particles = new Particle[nParticles];
}

Scene::~Scene()
{
    delete[] particles;
}

void Scene::fillWithRandom()
{
    std::srand(std::time(0));
    const auto& uniform = [](float minv, float maxv) {
        return minv + (float)std::rand() / RAND_MAX * (maxv - minv);
    };

    const auto& eps = std::numeric_limits<float>::epsilon();
    for (int i=0; i<nParticles; i++) {
        Particle& p = particles[i];
        p.mass = uniform(MIN_MASS, MAX_MASS);
        p.position[0] = uniform(eps, sizeX - eps);
        p.position[1] = uniform(eps, sizeY - eps);
        p.velocity[0] = uniform(MIN_VEL, MAX_VEL);
        p.velocity[1] = uniform(MIN_VEL, MAX_VEL);
    }
}

Collision Scene::nextCollisionTime() const
{
    Collision earliest;

    for (int i=0; i<nParticles; i++) {
        Particle& p1 = this->getParticleAt(i);
        // colliding with walls?
        float _px = p1.position[0];
        float _py = p1.position[1];
        float _vx = p1.velocity[0];
        float _vy = p1.velocity[1];

        Collision col_LR, col_UD;
        if (_vx > 0) {
            col_LR = Collision((sizeX - _px) / _vx, i, CollisionObject::R_Wall);
        } else {
            col_LR = Collision((0 - _px) / _vx, i, CollisionObject::L_Wall);
        }

        if (_vy > 0) {
            col_UD = Collision((sizeY - _py) / _vy, i, CollisionObject::U_Wall);
        } else {
            col_UD = Collision((0 - _py) / _vy, i, CollisionObject::D_Wall);
        }

        if (col_LR.occurTime < earliest.occurTime) {
            earliest = col_LR;
        }

        if (col_UD.occurTime < earliest.occurTime) {
            earliest = col_UD;
        }

        for (int j=i+1; j<nParticles; j++) {
            Particle& p2 = this->getParticleAt(j);
            float px = p1.position[0] - p2.position[0];
            float py = p1.position[1] - p2.position[1];
            float vx = p1.velocity[0] - p2.velocity[0];
            float vy = p1.velocity[1] - p2.velocity[1];

            float vmag = std::hypot(vx, vy);

            float l = -(px * vx + py * vy) / vmag;
            if (l <= 0.f) {
                continue;
            }

            // distance from collision point to perpendicular foot, squared
            float c2f2 = 2.f * 2.f - (px * px + py * py - l * l);
            if (c2f2 < 0) continue;

            float d = l - std::sqrt(c2f2);
            if (d < 0) continue;

            float t = d / vmag;
            if (t < earliest.occurTime) {
                earliest.occurTime = t;
                earliest.object1 = i;
                earliest.object2 = j;
            }
        }
    }

    return earliest;
}

void Scene::collideAndUpdate(Collision colli)
{
    float t = colli.occurTime;
    for (int i=0; i<nParticles; i++) {
        Particle& p = particles[i];
        p.position[0] += p.velocity[0] * t;
        p.position[1] += p.velocity[1] * t;
    }

    int obj1 = colli.object1, obj2 = colli.object2;
    if (CollisionObject::againstWall(obj1)) {
        // obj2 should be the one at rest
        std::swap(obj1, obj2);
    }

    if (CollisionObject::againstWall(obj2)) {
        switch (obj2) {
            case CollisionObject::L_Wall:
            case CollisionObject::R_Wall:
                particles[obj1].velocity[0] = -particles[obj1].velocity[0];
                break;
            case CollisionObject::U_Wall:
            case CollisionObject::D_Wall:
                particles[obj1].velocity[1] = -particles[obj1].velocity[1];
                break;
            default:
                throw std::runtime_error("Unknown collision object");
        }
    } else {
        // two particles collide together
        Particle& p1 = particles[obj1];
        Particle& p2 = particles[obj2];
        float vx = p1.velocity[0] - p2.velocity[0];
        float vy = p1.velocity[1] - p2.velocity[1];

        // since positions have been updated
        float px = p1.position[0] - p2.position[0];
        float py = p1.position[1] - p2.position[1];
        float pdInv = 1.f / std::hypot(px, py);
        px *= pdInv, py *= pdInv;

        float vVertMag = -vx * px - vy * py;
        float impulse = 2.f * p1.mass * p2.mass * vVertMag / (p1.mass + p2.mass);
        float v1VertMag = impulse / p1.mass;
        float v2VertMag = impulse / p2.mass;
        p1.velocity[0] -= v1VertMag * px;
        p1.velocity[1] -= v1VertMag * py;
        p2.velocity[0] -= v2VertMag * px;
        p2.velocity[1] -= v2VertMag * py;
    }
}

Particle& Scene::getParticleAt(int index) const
{
    return particles[index];
}

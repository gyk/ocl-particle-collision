
#include <cstdio>
using std::printf;

#include "config.h"
#include "Particle.h"
#include "Scene.h"
#include "Collision.h"

int main(int argc, char const *argv[])
{
    Scene scene(SIZE_X, SIZE_Y, N_PARTICLES);
    scene.fillWithRandom();

    for (int i=0; i<N_PARTICLES; i++) {
        const Particle& p = scene.getParticleAt(i);
        printf("#%i:\tm = %.3f\tp = (%.3f, %.3f)\tv = (%.3f, %.3f)\n", 
            i, p.mass, 
            p.position[0], p.position[1], 
            p.velocity[0], p.velocity[1]);
    }

    for (int i=0; i<10; i++) {
        Collision colli = scene.nextCollisionTime();
        printf("%f: (%i, %i)\n", colli.occurTime, colli.object1, colli.object2);
        if (!CollisionObject::againstWall(colli.object1) &&
            !CollisionObject::againstWall(colli.object2)) {
            auto& p1 = scene.getParticleAt(colli.object1);
            auto& p2 = scene.getParticleAt(colli.object2);
            printf("    m1: %f    m2: %f\n", p1.mass, p2.mass);
            printf("    p1-p2: (%f, %f)    v1-v2: (%f, %f)\n", 
                p1.position[0] - p2.position[0], p1.position[1] - p2.position[1], 
                p1.velocity[0] - p2.velocity[0], p1.velocity[1] - p2.velocity[1]);
        }

        scene.collideAndUpdate(colli);
    }

	return 0;
}

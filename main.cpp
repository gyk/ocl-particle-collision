
#include <cstdio>

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
        std::printf("#%i:\tm = %.3f\tp = (%.3f, %.3f)\tv = (%.3f, %.3f)\n", 
            i, p.mass, 
            p.position[0], p.position[1], 
            p.velocity[0], p.velocity[1]);
    }

    Collision colli = scene.nextCollisionTime();
    std::printf("%f: (%i, %i)\n", colli.occurTime, colli.object1, colli.object2);
	return 0;
}

#include <stdio.h>
#include <nds.h>

#include "fluids.h"

#define BOX_START_X 0
#define BOX_END_X 255
#define BOX_START_Y 0
#define BOX_END_Y 191

#define PHYSICS_TIME_STEP 0.016

void fSInit(struct fluidSimulation* fS, u16 size)
{
    fS->size = size;
    fS->particles = malloc(size * sizeof(particle));

    for (size_t i = 0; i < size; i++)
    {
        fS->particles[i] = (particle){{i, 0}, {0, 0}, {0, -10}};
    }
}

void fSUpdateParticles(struct fluidSimulation* fS)
{
    for (size_t i = 0; i < fS->size; i++)
    {
        // update velocities
        fS->particles[i].velocity = vector2_add(fS->particles[i].velocity, fS->particles[i].acceleration);

        // update positions
        fS->particles[i].position.x += fS->particles[i].velocity.x * PHYSICS_TIME_STEP;
        fS->particles[i].position.y -= fS->particles[i].velocity.y * PHYSICS_TIME_STEP;

        // resolve collisions
        if (fS->particles[i].position.x < BOX_START_X)
        {
            fS->particles[i].position.x += fS->particles[i].position.x - BOX_START_X;
        }
        if (fS->particles[i].position.x > BOX_END_X)
        {
            fS->particles[i].position.x -= fS->particles[i].position.x - BOX_END_X;
        }
        if (fS->particles[i].position.y < BOX_START_Y)
        {
            fS->particles[i].position.y += fS->particles[i].position.y - BOX_START_Y;
        }
        if (fS->particles[i].position.y > BOX_END_Y)
        {
            fS->particles[i].position.y -= fS->particles[i].position.y - BOX_END_Y;
        }
    }
}
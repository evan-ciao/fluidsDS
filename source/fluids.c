#include <stdio.h>
#include <nds.h>
#include <math.h>
#include <gl2d.h>

#include "fluids.h"
#include "water.h"
glImage waterSprite;

#define BOX_START_X 0
#define BOX_END_X 255
#define BOX_START_Y 0
#define BOX_END_Y 191

#define PARTICLE_RADIUS 4
#define HALF_PARTICLE_RADIUS 2

#define PHYSICS_TIME_STEP 0.016
#define DAMPING 0.7

void fSInit(struct fluidSimulation* fS, u16 size)
{
    fS->size = size;
    fS->particles = malloc(size * sizeof(particle));

    // grid formation
    int patriclesPerRow = (int)sqrt(size);
    int particlesPerCol = (size - 1) / patriclesPerRow + 1;

    for (size_t i = 0; i < size; i++)
    {
        fS->particles[i] = (particle){
            {(i % patriclesPerRow - patriclesPerRow / 2.0 + 0.5) * 6 + (SCREEN_WIDTH - patriclesPerRow) / 2.0, (i / patriclesPerRow - particlesPerCol / 2.0 + 0.5) * 6 + 60},
            {0, 0}, {0, -10}};
    }

    // initialize water sprite
    
    // some sweet sweet memory
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankE(VRAM_E_TEX_PALETTE);

    int waterID = glLoadTileSet(
        &waterSprite, 
        8, 
        8, 
        8, 
        8, 
        GL_RGB256,
        8, 
        8, 
        TEXGEN_TEXCOORD | GL_TEXTURE_COLOR0_TRANSPARENT, 
        256, 
        waterPal, 
        waterBitmap);

    if (waterID < 0)
        printf("[fSInit] failed to load water sprite %d\n", waterID);
}

float calculateDensity(struct fluidSimulation* fS, vector2 point)
{
    float density = 0;
    const float mass = 3;

    // loop over all particles and apply other particles forces
    for (size_t i = 0; i < fS->size; i++)
    {
        float dst = vector2_magnitude(vector2_subtract(fS->particles[i].position, point));
        float influence = smoothingKernel(SMOOTHING_RADIUS, dst);

        density += mass * influence;
    }

    return density;
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
        if (fS->particles[i].position.x - PARTICLE_RADIUS < BOX_START_X)
        {
            fS->particles[i].position.x += fS->particles[i].position.x + PARTICLE_RADIUS - BOX_START_X;
            fS->particles[i].velocity.x = -(fS->particles[i].velocity.x) * DAMPING;
        }
        if (fS->particles[i].position.x + PARTICLE_RADIUS > BOX_END_X)
        {
            fS->particles[i].position.x -= fS->particles[i].position.x + PARTICLE_RADIUS - BOX_END_X;
            fS->particles[i].velocity.x = -(fS->particles[i].velocity.x) * DAMPING;
        }
        if (fS->particles[i].position.y - PARTICLE_RADIUS < BOX_START_Y)
        {
            fS->particles[i].position.y += fS->particles[i].position.y + PARTICLE_RADIUS - BOX_START_Y;
            fS->particles[i].velocity.y = -(fS->particles[i].velocity.y) * DAMPING;
        }
        if (fS->particles[i].position.y + PARTICLE_RADIUS > BOX_END_Y)
        {
            fS->particles[i].position.y -= fS->particles[i].position.y + PARTICLE_RADIUS - BOX_END_Y;
            fS->particles[i].velocity.y = -(fS->particles[i].velocity.y) * DAMPING;
        }
    }
}

void fSDraw(struct fluidSimulation* fS)
{
    for (size_t i = 0; i < fS->size; i++)
    {
        glSprite(fS->particles[i].position.x - HALF_PARTICLE_RADIUS, fS->particles[i].position.y - HALF_PARTICLE_RADIUS, GL_FLIP_NONE, &waterSprite);
    }

    // debug
    glBox(fS->particles[0].position.x - HALF_PARTICLE_RADIUS, fS->particles[0].position.y - HALF_PARTICLE_RADIUS, fS->particles[0].position.x + HALF_PARTICLE_RADIUS, fS->particles[0].position.y + HALF_PARTICLE_RADIUS, RGB15(16, 0, 0));
}
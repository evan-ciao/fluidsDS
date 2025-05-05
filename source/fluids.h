#include "math.h"

typedef struct
{
    vector2 position;
    vector2 velocity;
    vector2 acceleration;
} particle;

struct fluidSimulation
{
    u16 size;
    particle* particles;
};

void fSInit(struct fluidSimulation* fS, u16 size);
void fSUpdateParticles(struct fluidSimulation* fS);
void fSDraw(struct fluidSimulation* fS);
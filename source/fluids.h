#include "math.h"

typedef struct
{
    vector2 position;
    vector2_float velocity;
    vector2_float acceleration;
} particle;

struct fluidSimulation
{
    u8 size;
    particle* particles;
    float* densities;
};

void fSInit(struct fluidSimulation* fS, u8 size);
void fSUpdateParticles(struct fluidSimulation* fS);
void fSDraw(struct fluidSimulation* fS);

float calculateDensity(struct fluidSimulation* fS, vector2 point);
void fSUpdateDensities(struct fluidSimulation* fS);

#define SMOOTHING_RADIUS 16
#define SMOOTHING_RADIUS_SQUARED SMOOTHING_RADIUS * SMOOTHING_RADIUS

// trying to bypass the smoothing kernel to keep everything much simpler
static inline float smoothingKernel(u8 radius, u16 sqrdst)
{
    return (max(0, radius - sqrdst));
}

static inline float smoothingKernelDerivative(u8 radius, u16 sqrdst)
{
    if (sqrdst >= radius * radius)
        return 0;
    
    return -1;
}
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

float calculateDensity(struct fluidSimulation* fS, vector2 point);

#define SMOOTHING_RADIUS 32
static inline float smoothingKernel(float radius, float dst)
{
    // keep density constant for different radius by diving by the volume of the kernel function
    float volume = 3.14 * radius * radius;  // calculated with wolfram alpha in some obscure way
    return float_max(0, radius - dst) / volume;
}
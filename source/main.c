#include <stdio.h>
#include <gl2d.h>
#include <nds.h>

#include "fluids.h"

int main(int argc, char **argv)
{
    consoleDemoInit();

    videoSetMode(MODE_0_3D);
    glScreen2D();
    glClearColor(31, 31, 31, 31);

    struct fluidSimulation fluid;
    fSInit(&fluid, 100);

    vector2 p = {128, 128};

    while (1)
    {
        // update positions
        fSUpdateParticles(&fluid);

        consoleClear();
        printf("%.2f\n", calculateDensity(&fluid, p));
        printf("%.2f\n", vector2_magnitude(vector2_subtract(fluid.particles[0].position, p)));

        swiWaitForVBlank();
        scanKeys();
        
        uint16_t keys = keysHeld();

        if (keys & KEY_START)
            break;

        glBegin2D();
            fSDraw(&fluid);

            // debug
            glBoxFilled(p.x - 2, p.y - 2, p.x + 2, p.y + 2, RGB15(0, 16, 0));
            glBox(p.x - SMOOTHING_RADIUS / 2, p.y - SMOOTHING_RADIUS / 2, p.x + SMOOTHING_RADIUS / 2, p.y + SMOOTHING_RADIUS / 2, RGB15(0, 16, 0));
            glLine(p.x, p.y, fluid.particles[0].position.x, fluid.particles[0].position.y, RGB15(0, 16, 0));
        glEnd2D();

        glFlush(0);
    }
    
    return 0;
}

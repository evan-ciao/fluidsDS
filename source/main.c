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
    fSInit(&fluid, 200);

    int a = 0;

    while (1)
    {
        // update positions
        fSUpdateParticles(&fluid);
        
        swiWaitForVBlank();
        consoleClear();
        scanKeys();
        
        uint16_t keys = keysHeld();
        
        if (keys & KEY_START)
            break;

        for (size_t i = 0; i < 100; i++)
        {
            for (size_t j = 0; j < 100; j++)
            {
                a = j;
            }
        }
        

        glBegin2D();

        for (size_t i = 0; i < fluid.size; i++)
        {
            glLine(
                fluid.particles[i].position.x, fluid.particles[i].position.y,
                fluid.particles[i].position.x, fluid.particles[i].position.y,
                RGB15(8, 8, 31)
            );
        }
        
        glEnd2D();

        glFlush(0);
    }
    
    return 0;
}

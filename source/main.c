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

    while (1)
    {
        // update positions
        fSUpdateParticles(&fluid);
        
        swiWaitForVBlank();
        scanKeys();
        
        uint16_t keys = keysHeld();

        if (keys & KEY_START)
            break;

        glBegin2D();
            fSDraw(&fluid);
        glEnd2D();

        glFlush(0);
    }
    
    return 0;
}

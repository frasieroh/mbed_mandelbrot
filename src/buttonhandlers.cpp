#ifndef BUTTONHANDLERS_CPP
#define BUTTONHANDLERS_CPP

// For converting int to string: C++03 has no std::to_string
#include <string>
#include <sstream>
#include "kernels.h"
#include "buttonhandlers.h"
    
void changeMaxIters(Button *self, DmTftBase *screen)
{
    if (brot->maxiters < 4096) {
        brot->maxiters *= 2;
    } else {
        brot->maxiters = 256;
    }
    
    std::ostringstream stringStream;
    stringStream << brot->maxiters;
    self->text = stringStream.str();
        
    self->draw(screen);
}

void changeKernel(Button *self, DmTftBase *screen)
{
    if (brot->kernel == drawASM) {
        brot->kernel = drawCInt;
        self->text = "Integer";
    } else if (brot->kernel == drawCInt) {
        brot->kernel = drawCFlt;
        self->text = "Float";
    } else { // brot->kernel == drawCFlt
        brot->kernel = drawASM;
        self->text = "ASM";        
    }
    self->draw(screen);
}

void reDraw(Button *self, DmTftBase *screen)
{
    brot->draw(screen);
}

void resetView(Button *self, DmTftBase *screen)
{
    brot->centerX = 0.0f;
    brot->centerY = 0.0f;
    brot->zoom = 1;
    brot->draw(screen);
}

void zoomOut(Button *self, DmTftBase *screen)
{
    if (brot->zoom > 1) {
        brot->zoom /= 2;
    }
    brot->draw(screen);
}

#endif
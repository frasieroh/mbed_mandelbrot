#ifndef BUTTONHANDLERS_H
#define BUTTONHANDLERS_H

#include "ui.h"

extern Mandelbrot *brot;

void changeMaxIters(Button *self, DmTftBase *screen);

void changeKernel(Button *self, DmTftBase *screen);

void reDraw(Button *self, DmTftBase *screen);

void resetView(Button *self, DmTftBase *screen);

void zoomOut(Button *self, DmTftBase *screen);
    
#endif
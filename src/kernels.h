#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "ui.h"

extern "C" uint32_t escapeTime(int32_t cx, int32_t cy, uint32_t maxiters);

void drawASM(Mandelbrot*, DmTftBase*);

void drawCInt(Mandelbrot*, DmTftBase*);

void drawCFlt(Mandelbrot*, DmTftBase*);

#endif
#ifndef MANDELBROT_CPP
#define MANDELBROT_CPP

#include "kernels.h"

// Fixed point arithmetic in ASM
void drawASM(Mandelbrot* brot, DmTftBase* screen)
{   
    int32_t cx; // Original x-coord
    int32_t cy; // Original y-coord
    uint32_t n; // Iterations
    
    for (uint16_t i = 0; i < brot->width; ++i) {
        for (uint16_t j = 0; j < brot->height; ++j) {
            
            // = (([-wh/2 .. wh/2]) / ((wh/4)) = [-2 .. 2]  / zoom
            cx = ((i-brot->width/2) / ((float)brot->width/4 * brot->zoom)
            // then add center point and multiply
                + brot->centerX) * (1 << 28);
            cy = ((j-brot->height/2) / ((float)brot->height/4 * brot->zoom) 
                + brot->centerY) * (1 << 28);
                
            n = escapeTime(cx, cy, brot->maxiters);
            
            uint16_t color = brot->getColor(n);
            screen->setPixel(i + brot->x, j + brot->y, color);
        }
    }
}

// Fixed point arithmetic
void drawCInt(Mandelbrot* brot, DmTftBase* screen)
{   
    int32_t cx; // Original x-coord
    int32_t cy; // Original y-coord
    int32_t zx; // Current x-coord
    int32_t zy; // Current y-coord
    int64_t zxzx; // Squares
    int64_t zyzy;
    uint32_t n; // Iterations
    
    for (uint16_t i = 0; i < brot->width; ++i) {
        for (uint16_t j = 0; j < brot->height; ++j) {
            
            // = (([-wh/2 .. wh/2]) / ((wh/4)) = [-2 .. 2]  / zoom
            cx = ((i-brot->width/2) / ((float)brot->width/4 * brot->zoom)
            // then add center point and multiply
                + brot->centerX) * (1 << 28);
            cy = ((j-brot->height/2) / ((float)brot->height/4 * brot->zoom) 
                + brot->centerY) * (1 << 28);
            zx = cx;
            zy = cy;
            
            for (n = 0; n < brot->maxiters; ++n) {
                zxzx = (int64_t)zx*zx;
                zyzy = (int64_t)zy*zy;
                if (zxzx + zyzy >= (288230376151711744LL)) {
                    break;
                }
                zy = (2*(int64_t)zx*zy) >> 28;
                zy += cy;
                zx = (zxzx - zyzy) >> 28;
                zx += cx;
            }
            
            uint16_t color = brot->getColor(n);
            screen->setPixel(i + brot->x, j + brot->y, color);
        }
    }
}

// Floating point arithmetic
void drawCFlt(Mandelbrot* brot, DmTftBase* screen)
{
    float cx; // Original x-coord
    float cy; // Original y-coord
    float zx; // Current x-coord
    float zy; // Current y-coord
    float zxzx; // Squares
    float zyzy;
    uint32_t n; // Iterations
    
    for (uint16_t i = 0; i < brot->width; ++i) {
        for (uint16_t j = 0; j < brot->height; ++j) {
            
            cx = ((i-brot->width/2) / ((float)brot->width/4 * brot->zoom)
            // then add center point
                + brot->centerX);
            cy = ((j-brot->height/2) / ((float)brot->height/4 * brot->zoom) 
                + brot->centerY);
            zx = cx;
            zy = cy;
            
            for (n = 0; n < brot->maxiters; ++n) {
                zxzx = zx*zx;
                zyzy = zy*zy;
                if (zxzx + zyzy > 4) {
                    break;
                }
                zy = 2*zx*zy + cy;
                zx = zxzx - zyzy + cx;
            }
            
            uint16_t color = brot->getColor(n);
            screen->setPixel(i + brot->x, j + brot->y, color);
        }
    }
}

#endif
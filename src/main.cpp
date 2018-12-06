// Oscar Frasier, CS 335, Fall 2018
// Interactive mandelbrot set, ARM platform

// Copyright notice for drivers: DmTpFt6x06.h/cpp DmTftIli9341.h/cpp
/**********************************************************************************************
 Copyright (c) 2014 DisplayModule. All rights reserved.

 Redistribution and use of this source code, part of this source code or any compiled binary
 based on this source code is permitted as long as the above copyright notice and following
 disclaimer is retained.

 DISCLAIMER:
 THIS SOFTWARE IS SUPPLIED "AS IS" WITHOUT ANY WARRANTIES AND SUPPORT. DISPLAYMODULE ASSUMES
 NO RESPONSIBILITY OR LIABILITY FOR THE USE OF THE SOFTWARE.
 ********************************************************************************************/

#include <vector>
#include "DmTpFt6x06.h"
#include "DmTftIli9341.h"
#include "ui.h"
#include "kernels.h"
#include "buttonhandlers.h"

// Globals are bad. Here's one:
Mandelbrot *brot;

int main(int argc, char** argv)
{
    DmTftIli9341 *screen =  new DmTftIli9341(p26, p25, p5, p6, p7);
    screen->init();
    
    I2C touchI2c = I2C(p28, p27);  
    DmTpFt6x06 *touch = new DmTpFt6x06(DmTpFt6x06::DM_TFT28_116, touchI2c, false);
    touch->init();
    
    // User Interface
    brot =  new Mandelbrot(0, 80, 240, 240, drawASM);
    Label maxItersLabel = Label(0, 16, "MaxIters:");
    Label kernelLabel = Label(0, 48, "Kernel:");
    Button maxItersButton = Button(80, 0, 64, 40, "256", changeMaxIters);
    Button kernelButton = Button(80, 40, 64, 39, "ASM", changeKernel);
    Button drawButton = Button(144, 0, 48, 40, "Draw", reDraw);
    Button resetButton = Button(144, 40, 48, 39, "Reset", resetView);
    Button zoomOutButton = Button(192, 0, 48, 79, "Back", zoomOut);
    
    std::vector<UIElement*> elements;
    elements.insert(elements.end(), &maxItersLabel);
    elements.insert(elements.end(), &kernelLabel);
    elements.insert(elements.end(), &maxItersButton);
    elements.insert(elements.end(), &kernelButton);
    elements.insert(elements.end(), &drawButton);
    elements.insert(elements.end(), &resetButton);
    elements.insert(elements.end(), &zoomOutButton);
    elements.insert(elements.end(), brot);
    
    for (int i = 0; i < elements.size(); ++i) {
        elements[i]->draw(screen);
    }
    
    // Polling touchscreen
    uint16_t cursorX;
    uint16_t cursorY;
    bool touching;
    bool wasTouching;
    while (1) {
        touch->readTouchData(cursorX, cursorY, touching);
        if (touching) {
            if (!wasTouching) {
                for (int i = 0; i < elements.size(); ++i) {
                    if (cursorX > elements[i]->x && 
                        cursorX < (elements[i]->x + elements[i]->width) &&
                        cursorY > elements[i]->y && 
                        cursorY < (elements[i]->y + elements[i]->height)) {
                        // Is within bounding box of element
                        elements[i]->onClick(screen, cursorX, cursorY);
                    }
                }
                wasTouching = true;
            } 
        } else if (wasTouching) {
            wasTouching = false;
        }
        wait(0.04);
    }
    /*
    Unreachable:
    delete screen;
    delete brot;
    delete touch;
    */
}
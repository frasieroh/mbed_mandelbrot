#ifndef UI_CPP
#define UI_CPP

#include "ui.h"

void Button::draw(DmTftBase *screen)
{
    screen->fillRectangle(x, y, x + width, y + height, BLACK);
    screen->drawRectangle(x, y, x + width, y + height, WHITE);
    screen->drawString(x + width/2 - 4*text.length(), y + height/2 - 8, text.c_str());
}

void Button::onClick(DmTftBase *screen, uint16_t cursorX, uint16_t cursorY)
{
    buttonHandler(this, screen);
}

void Label::draw(DmTftBase *screen)
{
    screen->drawString(x, y, text.c_str());
}

void Label::onClick(DmTftBase *screen, uint16_t cursorX, uint16_t cursorY)
{
    return;
}

void Mandelbrot::draw(DmTftBase* screen)
{
    if (zoom == 0) {
        printf("Error: Mandelbrot.zoom == 0\n\r");
        exit(0);
    }
    screen->drawString(x + width - 56, y + height - 16, "DRAWING");
    kernel(this, screen);
}
    
void Mandelbrot::onClick(DmTftBase *screen, uint16_t cursorX, uint16_t cursorY)
{
    // Origin centered on image, mathematical orientation
    float xPos = (cursorX - x - width/2) / (float)(width/4);
    float yPos = (cursorY - y - height/2) / (float)(width/4);
    centerX += xPos/zoom;
    centerY += yPos/zoom;
    zoom *= 2;
    draw(screen);
}

#endif
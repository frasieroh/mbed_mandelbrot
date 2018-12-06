#ifndef UI_H
#define UI_H

#include <string>
#include "DmTftBase.h"

struct UIElement {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;

    UIElement (uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) : 
        x(_x), y(_y), width(_width), height(_height) {}
    virtual void draw(DmTftBase* screen) { return; }
    virtual void onClick(DmTftBase *screen, uint16_t cursorX,
        uint16_t cursorY) { return; }
};

struct Button : UIElement {
    std::string text;
    void (*buttonHandler)(Button*, DmTftBase*);
    
    Button(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, 
        char* _text, void (*_buttonHandler)(Button*, DmTftBase*)) : 
        UIElement(_x, _y, _width, _height), text(_text),
        buttonHandler(_buttonHandler) {}
    virtual void draw(DmTftBase* screen);
    virtual void onClick(DmTftBase *screen, uint16_t cursorX, uint16_t cursorY);
};

struct Label : UIElement {
    std::string text;
    
    Label(uint16_t _x, uint16_t _y, char* _text) : UIElement(_x, _y, 0, 0),
        text(_text) {}
    virtual void draw(DmTftBase* screen);
    virtual void onClick(DmTftBase *screen, uint16_t cursorX, uint16_t cursorY);
};

struct Mandelbrot : UIElement {
    float centerX;
    float centerY;
    uint32_t zoom;
    uint32_t maxiters;
    void (*kernel)(Mandelbrot*, DmTftBase*);
    
    Mandelbrot(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, 
        void (*_kernel)(Mandelbrot*, DmTftBase*), float _centerX = 0,
        float _centerY = 0, uint32_t _zoom = 1, uint32_t _maxiters = 256) : 
        UIElement(_x, _y, _width, _height), centerX(_centerX), 
        centerY(_centerY), zoom(_zoom), maxiters(_maxiters),
        kernel(_kernel) {}
    virtual void draw(DmTftBase* screen);
    virtual void onClick(DmTftBase *screen, uint16_t cursorX, uint16_t cursorY);
    // Coloring algorithm inlined for speed. Has to be in the header so it works
    // when #included into different compilation units (e.g. kernels.cpp)
    inline uint16_t getColor(uint16_t n) {
        if (n == maxiters) { return BLACK; }
        uint16_t color;
        color = n > 16 ? 16 : n; // r
        color <<= 6;
        color += n / 4 > 48 ? 48 : n / 4; // g
        color <<= 5;
        color += n / 32 > 31 ? 31 : n / 32; // b
        return color;
    }
};

#endif
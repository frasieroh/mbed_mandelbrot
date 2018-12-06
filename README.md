# Mbed Mandelbrot Viewer

Touch-based mandelbrot set viewer for the ARM Mbed platform. Designed with the NXP LPC1768 and the DisplayModule DM-TFT28-116. It should be easy to adapt for any DisplayModule product, especially if it has an I2C touch controller.

On screen options allow the user to switch between 256*(2^n) maxiters up to 4096, and three rendering kernels using floats, integers, and integers in ARMv7 ASM.

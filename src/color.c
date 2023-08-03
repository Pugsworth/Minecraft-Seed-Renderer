#include "color.h"

color_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    color_t c = {r, g, b, a};
    return c;
}

color_t color_from_rgba(uint32_t rgba)
{
    color_t c = {rgba & 0xFF, (rgba >> 8) & 0xFF, (rgba >> 16) & 0xFF, (rgba >> 24) & 0xFF};
    return c;
}

uint32_t color_to_rgba(color_t c)
{
    return c.r | (c.g << 8) | (c.b << 16) | (c.a << 24);
}
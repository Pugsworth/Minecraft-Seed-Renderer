#include "color.h"

Color32 color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    Color32 c = {r, g, b, a};
    return c;
}

Color32 color_from_rgba(uint32_t rgba)
{
    Color32 c = {rgba & 0xFF, (rgba >> 8) & 0xFF, (rgba >> 16) & 0xFF, (rgba >> 24) & 0xFF};
    return c;
}

uint32_t color_to_rgba(Color32 c)
{
    return c.rgba.r | (c.rgba.g << 8) | (c.rgba.b << 16) | (c.rgba.a << 24);
}

int color_rgb888_to_rgba32(
    const uint8_t* rgb888, uint32_t* rgba32,
    const unsigned int width, const unsigned int height
) {
    unsigned int i, j;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            unsigned int idx = 3 * (i + j * width);
            unsigned int r = rgb888[idx];
            unsigned int g = rgb888[idx + 1];
            unsigned int b = rgb888[idx + 2];
            unsigned int a = 255;
            rgba32[i + j * width] = (a << 24) | (b << 16) | (g << 8) | r;
        }
    }

    return 0;
}

int color_rgba32_to_rgb888(
    const uint32_t* rgb32, uint8_t* rgb888,
    const unsigned int width, const unsigned int height
) {
    unsigned int i, j;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            unsigned int idx = 3 * (i + j * width);
            uint32_t rgba = rgb32[i + j * width];
            rgb888[idx] = rgba & 0xFF;
            rgb888[idx + 1] = (rgba >> 8) & 0xFF;
            rgb888[idx + 2] = (rgba >> 16) & 0xFF;
        }
    }

    return 0;
}
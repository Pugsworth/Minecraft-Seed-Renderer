#pragma once

#include <stdint.h>


enum {
    COLOR_BLACK = 0x000000FF,
    COLOR_WHITE = 0xFFFFFFFF,

    COLOR_RED = 0xFF0000FF,
    COLOR_GREEN = 0x00FF00FF,
    COLOR_BLUE = 0x0000FFFF,

    COLOR_YELLOW = 0xFFFF00FF,
    COLOR_MAGENTA = 0xFF00FFFF,
    COLOR_CYAN = 0x00FFFFFF,

    COLOR_ORANGE = 0xFF8000FF,
    COLOR_PURPLE = 0x8000FFFF,
    COLOR_PINK = 0xFF0080FF,
    COLOR_LIME = 0x80FF00FF,
    COLOR_TEAL = 0x008080FF,
    COLOR_LAVENDER = 0x8000FF80,
    COLOR_BROWN = 0x804000FF,
    COLOR_BEIGE = 0xFF8040FF,
    COLOR_MAROON = 0x800000FF,
    COLOR_MINT = 0x00FF80FF,
    COLOR_OLIVE = 0x808000FF,
    COLOR_CORAL = 0xFF8080FF,
    COLOR_NAVY = 0x000080FF,
    COLOR_GREY = 0x808080FF,
    COLOR_WHITE_SMOKE = 0xF5F5F5FF,
    COLOR_LIGHT_GREY = 0xD3D3D3FF,
    COLOR_SILVER = 0xC0C0C0FF,
    COLOR_DARK_GREY = 0xA9A9A9FF,
    COLOR_GREY_SMOKE = 0x696969FF,
    COLOR_GUNMETAL = 0x2C3539FF,
    COLOR_RICH_BLACK = 0x070707FF,
    COLOR_BLACK_COFFEE = 0x3B2F2FFF,
    COLOR_DARK_JUNGLE_GREEN = 0x1A2421FF,
    COLOR_EERIE_BLACK = 0x1B1B1BFF,
    COLOR_JET = 0x343434FF,
    COLOR_ONYX = 0x353839FF,
    COLOR_CHARCOAL = 0x464646FF,
    COLOR_OUTER_SPACE = 0x414A4CFF,
    COLOR_DARK_SLATE_GREY = 0x2F4F4FFF,
};



typedef union {
    struct { uint8_t r, g, b, a; };
    uint32_t rgba;
} color_t;

/**
 * @brief Create a color union from the given RGBA values.
 *
 * @param r red channel.
 * @param g green channel.
 * @param b blue channel.
 * @param a alpha channel.
 * @return color_t
 */
color_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Create a color union from the given uint32 value in RGBA format.
 *
 * @param rgba
 * @return color_t
 */
color_t color_from_rgba(uint32_t rgba);

/**
 * @brief Convert the given color union to a uint32 value in RGBA format.
 *
 * @param c
 * @return uint32_t
 */
uint32_t color_to_rgba(color_t c);


/**
 * @brief Swaps the endianness of the given RGBA value. RGBA <-> ABGR
 *
 * @param rgba
 * @return uint32_t
 */
uint32_t color_swap(uint32_t rgba);
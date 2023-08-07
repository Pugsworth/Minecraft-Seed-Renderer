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

/**
 * My attempt to create a fairly minimal endianness agnostic color library.
 * There are a couple formats the color can be in:
 * |          | Little Endian | Big Endian |
 * | RGBA8888 | ABGR        | RGBA     |
 * | ABGR8888 | ABGR        | RGBA     |
 * | RGB888   | BGR         | RGB      |
 * | BGR888   | BGR         | RGB      |
 *
 *
 * by default, this library works with RGBA since it's how humans think about color.
 */

struct rgba_t {
    uint8_t r, g, b, a;
};

struct abgr_t {
    uint8_t a, b, g, r;
};


/**
 * @brief Hold all the information for a color.
 * Can be used in RGBA or ABGR format.
 */
typedef union {
    struct rgba_t rgba;
    struct abgr_t abgr;

    uint32_t value;
} Color32;

/**
 * @brief Create a color union from the given RGBA values.
 *
 * @param r red channel.
 * @param g green channel.
 * @param b blue channel.
 * @param a alpha channel.
 * @return Color32
 */
Color32 color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Create a color union from the given uint32 value in RGBA format.
 *
 * @param rgba
 * @return Color32
 */
Color32 color_from_rgba(uint32_t rgba);

/**
 * @brief Convert the given color union to a uint32 value in RGBA format.
 *
 * @param c
 * @return uint32_t
 */
uint32_t color_to_rgba(Color32 c);


/**
 * @brief Swaps the endianness of the given RGBA value. RGBA <-> ABGR
 *
 * @param rgba
 * @return uint32_t
 */
uint32_t color_swap(uint32_t rgba);

/**
 * @brief Packs every 3 bytes from [rgb888] into a single 32-bit integer in RGBA format.
 * e.g. [r, g, b, r, g, b, ...] -> [rgba, rgba, ...]
 * Requires rgb32 to be allocated with width * height bytes.
 *
 * @param rgb888
 * @param rgb32
 * @param width
 * @param height
 * @return int
 */
int color_rgb888_to_rgba32(const uint8_t* rgb888, uint32_t* rgb32, const unsigned int width, const unsigned int height);

/**
 * @brief Unpacks a 32-bit integer in RGBA format into 3 bytes in [rgb888].
 * e.g. [rgba, rgba, ...] -> [r, g, b, r, g, b, ...]
 * Requires rgb888 to be allocated with 3 * width * height bytes.
 *
 * @param rgb32
 * @param rgb888
 * @param width
 * @param height
 * @return int
 */
int color_rgba32_to_rgb888(const uint32_t* rgb32, uint8_t* rgb888, const unsigned int width, const unsigned int height);
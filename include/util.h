#pragma once

#include <stdint.h>

#define SPNG_STATIC
#include <spng.h>

#ifdef _MSC_VER
    #define inline __inline
#endif
#define force_inline __attribute__((always_inline)) inline


/**
 * @brief Draws a grid over the given pixel buffer.
 * @param pixels: pixel buffer
 * @param sx: pixel buffer width
 * @param sy: pixel buffer height
 * @param grid_scale: spacing of the grid
 * @return 0 if successful, or -1 if the grid could not be drawn
 */
int draw_grid(unsigned char *pixels, const unsigned int sx, const unsigned int sy, const unsigned int grid_scale);


/* @brief Draw an icon on the given pixel buffer at the given position.
 * @param icon: RGB icon data
 * @param pixels: pixel buffer
 * @param sx: pixel buffer width
 * @param sy: pixel buffer height
 * @param x: x position of the icon
 * @param y: y position of the icon
 * @param iw: icon width
 * @param ih: icon height
 * @return 0 if successful, or -1 if the icon could not be drawn
 */
int draw_icon(unsigned char *icon, unsigned char *pixels, const unsigned int pw, const unsigned int ph,
              const int x, const int y, const int iw, const int ih);


/**
 * @brief Save the pixel buffer (e.g. from biomesToImage) to the given path as an PNG
 *
 * @param path
 * @param pixels
 * @param width
 * @param height
 * @return int
 */
int savePNG(const char* path, const uint32_t* pixels,
        const unsigned int width, const unsigned int height);


/**
 * @brief Read a PNG file into a pixel buffer.
 *
 * @param path
 * @param pixels
 */
readPNG(const char* path, uint32_t** pixels);


/**
 * @brief Returns 1 if the result is a success, 0 otherwise.
 *
 * @param result standard C error codes of 0 for success, non-zero for failure.
 * @return int
 */
// I was trying to use the macro always_inline here to force inlining, but it's complaining about __attribute__. I don't fucking know...
extern inline int is_success(int result);

/**
 * @brief Make directories recursively. TODO: Make recursive!
 *
 * @param pathname
 * @return int Returns 0 if successful, or -1 if the directory could not be created.
 */
int make_dirs(const char *pathname);

/**
 * @brief Fills a char buffer with a progress bar that when printed will overwrite the previous line.
 *
 * @param buffer Buffer to fill with the progress bar.
 * @param msg Message to display before the progress bar.
 * @param current Current amount of progress.
 * @param total Total amount of progress.
 * @return int
 */
int progress_bar(char *buffer, const char *msg, int current, int total);


/**
 * @brief Generate a signed 64bit integer.
 *
 * @return int64_t
 */
int64_t rand_64();

/**
 * @brief Generate an unsigned 64bit integer.
 *
 * @return uint64_t
 */
uint64_t rand_u64();
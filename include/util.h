#pragma once

#include <stdint.h>

#define SPNG_STATIC
#include <spng.h>

#ifdef _MSC_VER
    #define inline __inline
#endif
#define force_inline __attribute__((always_inline)) inline

#define OLIVEC_AA_RES 1
#define OLIVEC_IMPLEMENTATION
#include <olive.c>


/**
 * @brief Some common structures that can be useful.
 */

// Captures a 2D vector with the most common uses
typedef union {
    // X/Y for Z axis coordinate systems.
    // X/Z for Y axis coordinate systems.
    struct {
        int x;
        union {
            int y, z;
        };
    };
    // Width/Height
    struct { int w, h; };
    struct { int width, height; };
    int v[2];
} Vec2;


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
int readPNG(const char* path, uint32_t** pixels,
    unsigned int* width, unsigned int* height);


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


/**
 * @brief Dumps a section of memory to console for inspection.
 * Dumps 8 bytes at a time.
 *
 * @param address Memory address to start dumping.
 * @param offsetBack Negative offset from address.
 * @param offsetForward Positive offset from address.
 */
void dump_memory(void* address, const int offsetBack, const unsigned int offsetForward);


void getHeightShading();


Olivec_Canvas* loadPNGToCanvas(const char* path);
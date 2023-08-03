#include <stdlib.h>
#include <errno.h>

// For mkdir
#include <sys/stat.h>
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <unistd.h>
#endif

#include "libattopng.h"
#include "util.h"

int draw_grid(unsigned char *pixels, const unsigned int sx, const unsigned int sy, const unsigned int grid_scale)
{
    /*
        pixels is a buffer of size 3*sx*sy in which each pixel is represented by 3 bytes row after row.
        The spacing of the grid is every 16 pixels.
    */

    unsigned int i, j;
    unsigned int pixscale = 1;
    unsigned int flip = 0;

    for (j = 0; j < sy; j++)
    {
        for (i = 0; i < sx; i++)
        {
            if ((i % grid_scale == 0) || (j % grid_scale == 0))
            {
                unsigned int m, n;
                for (m = 0; m < pixscale; m++) {
                    for (n = 0; n < pixscale; n++) {
                        int idx = pixscale * i + n;
                        if (flip)
                            idx += (sx * pixscale) * ((pixscale * j) + m);
                        else
                            idx += (sx * pixscale) * ((pixscale * (sy-1-j)) + m);

                        unsigned char *pix = pixels + 3*idx;
                        // Blend the grid with the underlying pixels using overlay blending
                        pix[0] = (unsigned char)((pix[0] * 0x80) >> 8);
                        pix[1] = (unsigned char)((pix[1] * 0x80) >> 8);
                        pix[2] = (unsigned char)((pix[2] * 0x80) >> 8);
                    }
                }
            }
        }
    }

    return 0;
}

int draw_icon(unsigned char* icon, unsigned char* pixels, const unsigned int pw, const unsigned int ph,
              const int x, const int y, const int iw, const int ih) {
    /*
        Draw icon of size iw, ih centered on x, y of pixels image of size pw, ph.

        icon is an unsigned RGBA buffer of size 4*iw*ih.
        pixels is an unsigned RGB buffer of size 3*pw*ph.
    */

    int startX = x - iw / 2;
    int startY = y - ih / 2;

    int i, j, k, l;

    for (j = 0; j < ih; j++) {
        for (i = 0; i < iw; i++) {
            int idx = 4 * (i + j * iw);
            unsigned char r = icon[idx];
            unsigned char g = icon[idx + 1];
            unsigned char b = icon[idx + 2];
            unsigned char a = icon[idx + 3];

            // Skip alpha pixels that are less than 128 translucent.
            if (a < 128)
                continue;

            int destX = startX + i;
            int destY = startY + j;

            if (destX >= 0 && destX < pw && destY >= 0 && destY < ph) {
                for (l = 0; l < 3; l++) {
                    int idx2 = 3 * (destX + destY * pw) + l;
                    unsigned char c = pixels[idx2];
                    unsigned char d = (unsigned char)((c * (255 - a) + (l == 0 ? r : (l == 1 ? g : b)) * a) >> 8);
                    pixels[idx2] = d;
                }
            }
        }
    }

    return 0;
}

#define RGBA(r,g,b,a) ((r) | ((g)<<8) | ((b)<<16) | ((a)<<24))

int savePNG(const char *path, const unsigned char *pixels, const unsigned int width, const unsigned int height)
{
    libattopng_t *png = libattopng_new(width, height, PNG_RGBA);

    for (unsigned int y = 0; y < height; y++)
    {
        unsigned int row = y * width * 3;
        for (unsigned int x = 0; x < width; x++)
        {
            unsigned int idx = row + x * 3;
            libattopng_set_pixel(png, x, y, RGBA(pixels[idx], pixels[idx+1], pixels[idx+2], 255));
        }
    }

    int result = libattopng_save(png, path);
    libattopng_destroy(png);

    return result != 0;
}


int make_dirs(const char *pathname)
{
    struct stat st = {0};
    int res = stat(pathname, &st);

    if (0 == res) {
#if defined(_WIN32)
        _mkdir(pathname);
#else
        mkdir(pathname, 0777);
#endif
        return 0;
    }

    switch(errno) {
        case 17: return 0; // directory already exists, and that's okay!
        default:
            fprintf(stderr, "Failed to make_dirs '%s': %#X\n", pathname, errno);
            return -1;
    }
}


inline int is_success(int result)
{
    return 0 == result;
}

int progress_bar(char *buffer, const char *msg, int current, int total)
{
    int bar_width = 80;
    int length = 0;
    float progress = (float)current / (float)total;

    length += sprintf(buffer+length, "%s [", msg);

    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i)
    {
        if (i < pos)
            length += sprintf(buffer+length, "=");
        else if (i == pos)
            length += sprintf(buffer+length, ">");
        else
            length += sprintf(buffer+length, " ");
    }

    length += sprintf(buffer+length, "] %d/%d (%d%%)\r", current, total, (int)(progress * 100.0));

    return 0;
}



int64_t rand_64()
{
    int64_t r = 0;
    for (int i = 0; i < 64; i++)
    {
        r |= (int64_t)(rand() & 1) << i;
    }
    return r;
}

uint64_t rand_u64()
{
    uint64_t r = 0;
    for (int i = 0; i < 64; i++)
    {
        r |= (uint64_t)(rand() & 1) << i;
    }
    return r;
}
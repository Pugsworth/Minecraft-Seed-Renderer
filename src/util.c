#include <stdlib.h>
#include <errno.h>

// For mkdir
#include <sys/stat.h>
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <unistd.h>
#endif

// #include "libattopng.h"
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

int savePNG(const char* path, const uint32_t* pixels, const unsigned int width, const unsigned int height)
{
    // Save the image.
    spng_ctx *ctx = spng_ctx_new(SPNG_CTX_ENCODER);
    spng_set_option(ctx, SPNG_ENCODE_TO_BUFFER, 1);

    struct spng_ihdr ihdr = {0};
    ihdr.bit_depth = 8;
    ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;
    ihdr.width = width;
    ihdr.height = height;
    spng_set_ihdr(ctx, &ihdr);

    spng_set_crc_action(ctx, SPNG_CRC_USE, SPNG_CRC_USE);

    // spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size);
    spng_set_option(ctx, SPNG_IMG_COMPRESSION_LEVEL, 1);
    int ret = spng_encode_image(ctx, pixels, sizeof(uint32_t) * width * height, SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
    if (ret) {
        printf("spng_encode_image() error: %s\n", spng_strerror(ret));
        spng_ctx_free(ctx);
        return -1;
    }

    size_t out_size;
    void* out_buffer = NULL;
    out_buffer = spng_get_png_buffer(ctx, &out_size, NULL);
    if (!out_buffer) {
        printf("spng_get_png_buffer() error: %s\n", spng_strerror(ret));
        spng_ctx_free(ctx);
        return -1;
    }

    FILE* png = fopen(path, "wb");
    if (!png) {
        fprintf(stderr, "Failed to open '%s' for writing: %#X\n", path, errno);
        return -1;
    }

    fwrite(out_buffer, 1, out_size, png);
    fclose(png);

    spng_ctx_free(ctx);

    return 0;
}

int readPNG(const char* path, uint32_t** pixels,
    unsigned int* width, unsigned int* height)
{
    FILE* png = fopen(path, "rb");
    if (!png) {
        fprintf(stderr, "Failed to open '%s' for reading: %#X\n", path, errno);
        return -1;
    }

    fseek(png, 0, SEEK_END);
    size_t png_size = ftell(png);
    rewind(png);

    uint8_t* png_buffer = (uint8_t*)calloc(png_size, 1);
    if (!png_buffer) {
        fprintf(stderr, "Failed to allocate %zu bytes for PNG buffer\n", png_size);
        return -1;
    }

    fread(png_buffer, png_size, 1, png);
    fclose(png);

    int ret = 0; // Return codes for error handling

    spng_ctx* ctx = spng_ctx_new(0);
    spng_set_crc_action(ctx, SPNG_CRC_USE, SPNG_CRC_USE);

    size_t limit = 1024 * 1024 * 100; // 100 MB
    spng_set_chunk_limits(ctx, limit, limit);

    if (SPNG_OK != (ret = spng_set_png_buffer(ctx, png_buffer, png_size))) {
        fprintf(stderr, "spng_set_png_buffer() error: %s\n", spng_strerror(ret));
        return -1;
    }

    struct spng_ihdr ihdr = {0};
    if (SPNG_OK != (ret = spng_get_ihdr(ctx, &ihdr))) {
        fprintf(stderr, "spng_get_ihdr() error: %s\n", spng_strerror(ret));
        return -1;
    }

    if (ihdr.bit_depth != 8) {
        fprintf(stderr, "Unsupported bit depth: %u\n", ihdr.bit_depth);
        return -1;
    }

    // if (ihdr.color_type != SPNG_COLOR_TYPE_TRUECOLOR_ALPHA) {
    //     fprintf(stderr, "Unsupported color type: %u\n", ihdr.color_type);
    //     return -1;
    // }

    *width = ihdr.width;
    *height = ihdr.height;

    size_t out_size;
    if (SPNG_OK != spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size)) {
        fprintf(stderr, "spng_decoded_image_size() error: %s\n", spng_strerror(ret));
        return -1;
    }

    if (out_size != sizeof(uint32_t) * ihdr.width * ihdr.height) {
        fprintf(stderr, "Image size mismatch\n");
        return -1;
    }

    // Create the buffer and set the pointer to pixels;
    *pixels = (uint32_t*)calloc(1, out_size);

    if (SPNG_OK != spng_decode_image(ctx, *pixels, out_size, SPNG_FMT_RGBA8, SPNG_DECODE_TRNS)) {
        fprintf(stderr, "spng_decode_image() error: %s\n", spng_strerror(ret));
        return -1;
    }

    spng_ctx_free(ctx);

    return 0;
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




uint8_t* readPPM(const char* filename);



int writeBiomesToBuffer(uint32_t* buffer,
    uint8_t biomesColors[256][3], const int* biomes,
    const unsigned int sx, const unsigned int sy,
    const unsigned int pixelScale, const int flip)
{
    unsigned int i, j;
    int containsInvalidBiomes = 0;

    for (j = 0; j < sy; j++) {
        for (i = 0; i < sx; i++) {
            int id = biomes[j*sx+i];
            unsigned int r, g, b;

            if (id < 0 || id >= 255) {
                containsInvalidBiomes = 1;
                r = biomesColors[id&0x7f][0]-40; r = (r>0xff) ? 0x00 : r&0xff;
                g = biomesColors[id&0x7f][1]-40; g = (g>0xff) ? 0x00 : g&0xff;
                b = biomesColors[id&0x7f][2]-40; b = (b>0xff) ? 0x00 : b&0xff;
            }
            else {
                r = biomesColors[id][0];
                g = biomesColors[id][1];
                b = biomesColors[id][2];
            }

            unsigned m, n;


        }
    }
}


int rgb888torgb32(const unsigned char* rgb888, uint32_t* rgb32, const unsigned int width, const unsigned int height)
{
    unsigned int i, j;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            unsigned int idx = 3 * (i + j * width);
            unsigned int r = rgb888[idx];
            unsigned int g = rgb888[idx + 1];
            unsigned int b = rgb888[idx + 2];
            unsigned int a = 255;
            rgb32[i + j * width] = (a << 24) | (b << 16) | (g << 8) | r;
        }
    }

    return 0;
}



void dump_memory(void* address, const int offsetBack, const unsigned int offsetForward)
{
    int from = offsetBack;
    int to = offsetForward;

    if (offsetBack > 0) {
        from = -from;
    }

    int c = 0;

    // Dump 8 bytes per line.
    for (int i = from; i < to; i++) {
        unsigned char b = *((unsigned char*)address + i);

        printf("%02X ", b);

        if (c++ == 7) {
            printf("\n");
            c = 0;
        }
    }

    printf("\n");
}

Olivec_Canvas* loadPNGToCanvas(const char* path)
{
    int width, height;
    uint32_t* data = NULL;

    if (0 != readPNG(path, &data, &width, &height)) {
        fprintf(stderr, "Failed to read PNG '%s'\n", path);
        return NULL;
    }

    Olivec_Canvas* canvas = (Olivec_Canvas*)calloc(1, sizeof(Olivec_Canvas));
    Olivec_Canvas temp = olivec_canvas(data, width, height, width);
    canvas->height  = temp.height;
    canvas->width   = temp.width;
    canvas->stride  = temp.stride;
    canvas->pixels  = temp.pixels;

    return canvas;
}
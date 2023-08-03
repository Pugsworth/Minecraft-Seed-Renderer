#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"
#include "args.h"
#include "icons.h"
#include "dynamicarray.h"
#include "color.h"
#include "libattopng.h"

#include "generator.h"
#include "finders.h"


#define OLIVEC_AA_RES 2
#define OLIVEC_IMPLEMENTATION
#include <olive.c>


#define VERSION "0.1.0"
#define MC_VERSION MC_1_19_2


// List of biomes that are valid for ocean biomes. The biome enums aren't flags, so we cannot use bitwise.
const int OCEAN_BIOMES[] = {
    ocean, deep_ocean, deep_frozen_ocean, warm_ocean, deep_warm_ocean,
    lukewarm_ocean, deep_lukewarm_ocean, cold_ocean, deep_cold_ocean
};
// Check if a biome is in a list of biomes.
int in_biomes(int biome, int *biomes)
{
    for (int i = 0; i < sizeof(biomes) / sizeof(int); i++)
    {
        if (biome == biomes[i])
        {
            printf("Found biome %i in list!\n", biome);
            return 1;
        }
    }

    return 0;
}

int generate_seed_image(uint64_t seed, int map_scale, int map_width, int map_height, int pix4cell)
{
    if (!seed)
    {
        printf("randomizing seed\n");
        fflush(stdout);
        seed = time(NULL);
    }

    int image_width = pix4cell * map_width, image_height = pix4cell * map_height;

    fprintf(stdout, "Generating image...\n");
    printf("%ix%i with scale %i; pixels per cell: %i\n", image_width, image_height, map_scale, pix4cell);

    Generator g;
    setupGenerator(&g, MC_VERSION, 0);

    applySeed(&g, DIM_OVERWORLD, seed);

    Pos spawn = getSpawn(&g);
    int spawn_biome = getBiomeAt(&g, 1, spawn.x, 255, spawn.z);
    printf("Found spawn biome in %i\n", spawn_biome);

    if (in_biomes(spawn_biome, OCEAN_BIOMES))
    {
        spawn.x = spawn.z = 0;
    }

    Range r;
    // 1:16, a.k.a. horizontal chunk scaling
    r.scale = map_scale;
    // Define the position and size for a horizontal area:
    r.x = spawn.x - map_width / 2, r.z = spawn.z - map_height / 2; // position (x,z)
    r.sx = map_width, r.sz = map_height;                           // size (width,height)
    // Set the vertical range as a plane near sea level at scale 1:4.
    r.y = 255, r.sy = 1;

    // Allocate the necessary cache for this range.
    int *biomeIds = allocCache(&g, r);

    // Generate the area inside biomeIds, indexed as:
    // biomeIds[i_y*r.sx*r.sz + i_z*r.sx + i_x]
    // where (i_x, i_y, i_z) is a position relative to the range cuboid.
    genBiomes(&g, biomeIds, r);

    unsigned char biomeColors[256][3];
    initBiomeColors(biomeColors);
    unsigned char *rgb = (unsigned char *)malloc(3 * image_width * image_height);
    biomesToImage(rgb, biomeColors, biomeIds, r.sx, r.sz, pix4cell, 2);
    // draw_grid(rgb, r.sx, r.sz, 16);
    // TODO: Draw various border sizes to determine the maximum size of the border.

    struct
    {
        int x, y;
    } center = {image_width / 2, image_height / 2};
    draw_icon(COMPASS_ICON, rgb, image_width, image_height, center.x, center.y, COMPASS_WIDTH, COMPASS_HEIGHT);

    char *map_name = (char *)malloc(64);
    sprintf(map_name, "renders/map_%lli.png", seed);

    int res = make_dirs("renders");
    if (is_success(res))
    {
        printf("Created renders directory!\n");
    }
    else
    {
        fprintf(stderr, "Failed to create renders directory, exiting!\n");
        return EXIT_FAILURE;
    }

    // Save the RGB buffer to a PPM image file.
    // savePPM("map.ppm", rgb, image_width, image_height);
    if (is_success(savePNG(map_name, rgb, image_width, image_height)))
    {
        fprintf(stdout, "Saved image to %s!\n", map_name);
    }
    else
    {
        fprintf(stderr, "Failed to save image!\n");
        return -1;
    }

    // Clean up.
    free(map_name);
    free(biomeIds);
    free(rgb);

    fprintf(stdout, "Done!\n");

    fflush(stderr);
    fflush(stdout);

    return 0;
}

struct Arguments
{
    uint64_t seed;
    int map_scale;
    int map_width;
    int map_height;
    int pix4cell;

    int dryrun;
};

int parse_cmd_test(char* cmd_name, ArgParser* parser)
{
    const int width = 512;
    const int height = 512;
    const int total_size = width * height;

    uint32_t* pixels = (uint32_t*)calloc(total_size, sizeof(uint32_t));

    Olivec_Canvas canvas = olivec_canvas(pixels, width, height, width);
    olivec_fill(canvas, 0xFF000000);
    olivec_frame(canvas, 0, 0, width, height, 4, 0xFF0000FF);
    for (int i = 6; i > 0; i--) {
        uint32_t color = 0xFFFF00FF;
        if (i % 2 == 0) {
            color = 0xFF00FF00;
        }
        int radi = 32 + i*16;
        olivec_circle(canvas, width/2, height/2, radi, color);
    }

    olivec_text(canvas, "hello, world!", 12, 12, olivec_default_font, 4, COLOR_WHITE_SMOKE);

    for (int i = 5; i > 0; i--) {
        int hh = 12 + (4-i)*6*4 + 12;
        olivec_text(canvas, "0123456789", 12, hh, olivec_default_font, i, COLOR_WHITE_SMOKE);
    }

    // Save the image.
    libattopng_t *png = libattopng_new(width, height, PNG_RGBA);

    for (uint32_t y = 0; y < height; y++) {
        int row = y * width;
        for (uint32_t x = 0; x < width; x++) {
            uint32_t idx = row + x;
            uint32_t color = canvas.pixels[idx];
            libattopng_set_pixel(png, x, y, color);
        }
    }

    libattopng_save(png, "renders/test.png");
    libattopng_destroy(png);

    free(pixels);

    puts("Done!");
}

int parse_cmd_search(char* cmd_name, ArgParser* parser)
{
}

int parse_cmd_render(char* cmd_name, ArgParser* parser)
{
    int64_t seed = 0;

    if (ap_found(parser, "seed")) {
        char *sseed = ap_get_str_value(parser, "seed");
        printf("Seed as string: %s\n", sseed);
        // Convert signed 64-bit integer to unsigned 64-bit integer
        char *end = NULL;

        seed = strtoull(sseed, &end, 10);
    }

    // Because these have fallback values, we don't care if they were found or not, always get the value!
    int map_scale  = ap_get_int_value(parser, "scale");
    int map_width  = ap_get_int_value(parser, "width");
    int map_height = ap_get_int_value(parser, "height");
    int pix4cell   = ap_get_int_value(parser, "cell");

    printf("Seed: %llu\n", seed);

    generate_seed_image(seed, map_scale, map_width, map_height, pix4cell);
}

int parse_arguments(struct Arguments* arguments, int argc, char** argv)
{
    ArgParser *parser = ap_new_parser();
    if (!parser)
    {
        fprintf(stderr, "Failed to allocate memory for parser!\n");
        return -1;
    }

    // default arguments
    ap_set_version(parser, VERSION);
    ap_set_helptext(parser, "Generate an image of the seed.");
    ap_add_flag(parser, "dryrun n");

    // General arguments
    ap_add_int_opt(parser, "threads", 1);

    ArgParser* search_parser = ap_new_cmd(parser, "search");
    if (!search_parser) {
        fprintf(stderr, "Failed to allocate memory for search_parser!\n");
        return -1;
    }
    ap_set_helptext(search_parser, "Search for seeds");
    ap_set_cmd_callback(search_parser, parse_cmd_search);

    ap_add_int_opt(search_parser, "max-seeds", 1000);


    ArgParser* render_parser = ap_new_cmd(parser, "render");
    if (!render_parser) {
        fprintf(stderr, "Failed to allocate memory for render_parser!\n");
        return -1;
    }
    ap_set_helptext(render_parser, "Render an image of the seed.");
    ap_set_cmd_callback(render_parser, parse_cmd_render);

    ap_add_str_opt(render_parser, "seed s", "0");
    ap_add_int_opt(render_parser, "scale", 16);
    ap_add_int_opt(render_parser, "width", 512);
    ap_add_int_opt(render_parser, "height", 512);
    ap_add_int_opt(render_parser, "cell", 1);

    ArgParser* test_parser = ap_new_cmd(parser, "test");
    if (!test_parser) {
        fprintf(stderr, "Failed to allocate memory for test_parser!\n");
        return -1;
    }
    ap_set_helptext(test_parser, "For testing purposes.");
    ap_set_cmd_callback(test_parser, parse_cmd_test);

    if (!ap_parse(parser, argc, argv))
    {
        fprintf(stderr, "Failed to parse arguments!\n");
        return -1;
    }

    // ap_print(parser);

    if (ap_found(parser, "dryrun"))
    {
        printf("Dry run!\n");
        arguments->dryrun = 1;
        return 0;
    }

    ap_free(parser);


    return 0;
}


int main(int argc, char *argv[])
{
    srand(time(NULL));

    struct Arguments args = {0};
    parse_arguments(&args, argc, argv);

    return 0;
}
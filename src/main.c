#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// olive.c must either be included before util.h
// or OLIVEC_IMPLEMENTATION must be undefined after util.h because that carries over.
#include <olive.c>
#include "util.h"

#include "args.h"
#include "icons.h"
#include "dynamicarray.h"
#include "color.h"
// #include "libattopng.h"

#include "generator.h"
#include "finders.h"


#include "audio.h"


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

// TODO: Should be able to specify the world width/height as well as the image width/height.
//     Right now, they are kinda tied together.
int generate_seed_image(uint64_t seed, int map_scale, int map_width, int map_height, int pix4cell)
{
    int error_code = 0;

    // Filename
    if (!seed) {
        printf("Randomizing seed...\n");
        seed = time(NULL);
        printf("New Seed: %llu\n", seed);
    }

    char* map_name = (char*)malloc(64);
    sprintf(map_name, "renders/map_%lli.png", seed);

    int res = make_dirs("renders");
    if (!is_success(res)) {
        fprintf(stderr, "Failed to create renders directory, exiting!\n");
        error_code = -1;
        goto CLEANUP;
    }

    int image_width = pix4cell * map_width;
    int image_height = pix4cell * map_height;

    fprintf(stdout, "Generating image...\n");
    printf("%ix%i with scale %i; pixels per cell: %i\n", image_width, image_height, map_scale, pix4cell);

    Generator g;
    setupGenerator(&g, MC_VERSION, 0);

    applySeed(&g, DIM_OVERWORLD, seed);

    // This isn't the best way to do this, but whatever...
    Pos spawn = getSpawn(&g);
    int spawn_biome = getBiomeAt(&g, 1, spawn.x, 255, spawn.z);

    if (isOceanic(spawn_biome)) {
    // if (in_biomes(spawn_biome, OCEAN_BIOMES)) {
        spawn.x = spawn.z = 0; // If spawn is in the ocean, set it to 0,0
    }

    Range r;
    r.scale = map_scale; // 1:16, a.k.a. horizontal chunk scaling
    // Define the position and size for a horizontal area:
    r.x = spawn.x - map_width / 2, r.z = spawn.z - map_height / 2; // position (x,z)
    r.sx = map_width, r.sz = map_height;                           // size (width,height)
    r.y = 255, r.sy = 1; // Set the vertical range as a plane near sea level at scale 1:4.

    // Allocate the necessary cache for this range.
    int* biomeIds = allocCache(&g, r);

    // Generate the area inside biomeIds, indexed as:
    // biomeIds[i_y*r.sx*r.sz + i_z*r.sx + i_x]
    // where (i_x, i_y, i_z) is a position relative to the range cuboid.
    genBiomes(&g, biomeIds, r);

    unsigned char biomeColors[256][3];
    initBiomeColors(biomeColors);
    // TODO: Make a new biomesToImage function for building a Color32 array instead.
    unsigned char* rgb = (unsigned char*)malloc(3 * image_width * image_height);
    biomesToImage(rgb, biomeColors, biomeIds, r.sx, r.sz, pix4cell, 2);


    /**
     * Build an image of the heights of the terrain.
     *
    int getSurfaceHeight(
        const double ncol00[], const double ncol01[],
        const double ncol10[], const double ncol11[],
        int colymin, int colymax, int blockspercell, double dx, double dz)
     */


    // draw_grid(rgb, r.sx, r.sz, 16);
    // TODO: Draw various border sizes to determine the maximum size of the border.

    uint32_t* icon_pixels = NULL;
    unsigned int icon_width = 0, icon_height = 0;
    if (readPNG("assets/icons/compass_16.png", &icon_pixels, &icon_width, &icon_height)) {
        fprintf(stderr, "Failed to read compass icon!\n");
        error_code = -1;
        goto CLEANUP;
    }

    uint32_t* pixels = (uint32_t*)calloc(image_width * image_height, sizeof(uint32_t));
    color_rgb888_to_rgba32(rgb, pixels, image_width, image_height);

    // Put the png into an olivec_sprite and draw it to the main display before saving.
    Olivec_Canvas icon_compass = olivec_canvas(icon_pixels, icon_width, icon_height, icon_width);
    Olivec_Canvas canvas = olivec_canvas(pixels, image_width, image_height, image_width);
    olivec_sprite_blend(
        canvas,                             // canvas
        (image_width/2) - (icon_width/2),   // x
        (image_height/2) - (icon_height/2), // y
        icon_width, icon_height,            // icon size
        icon_compass                       // icon canvas
    );

    if (is_success(savePNG(map_name, canvas.pixels, image_width, image_height))) {
        fprintf(stdout, "Saved image to %s!\n", map_name);
    }
    else {
        fprintf(stderr, "Failed to save image!\n");
        error_code = -1;
        goto CLEANUP;
    }

    fprintf(stdout, "Done!\n");

CLEANUP:

    // Clean up.
    free(map_name);
    free(biomeIds);
    free(rgb);
    free(pixels);

    fflush(stderr);
    fflush(stdout);

    return error_code;
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

    {
        int y = 12;
        for (int i = 5; i > 0; i--) {
            // Glyphs are 6 pixels tall. Set a y offset of i (glyph scale) * 6 + 2(padding) plus the previous y offset.
            y += (i+1) * 6 + 4;
            olivec_text(canvas, "0123456789", 12, y, olivec_default_font, i, COLOR_WHITE_SMOKE);
        }
    }

    savePNG("test.png", pixels, width, height);

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

    StructureConfig* conf = NULL;
    getStructureConfig(Ruined_Portal, MC_VERSION, &conf);
    Pos pos;
    getStructurePos(Ruined_Portal, MC_VERSION, seed, 0, 0, &pos);
    printf("Ruined Portal found at: %i, %i\n", pos.x, pos.z);

    audio_play(AUDIO_ALERT);
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
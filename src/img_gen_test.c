// generate an image of the world
#include "generator.h"
#include "finders.h"
#include "util.h"
#include <stdio.h>
#include <time.h>

// For mkdir
#include <sys/types.h>
#include <sys/stat.h>
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <unistd.h>
#endif

#include "args.h"
#include "icons.h"
#include "dynamicarray.h"


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
        return EXIT_SUCCESS;
    }

    switch(errno) {
        case 17: return EXIT_SUCCESS; // directory already exists, and that's okay!
        default:
            fprintf(stderr, "Failed to make_dirs '%s': %#X\n", pathname, errno);
            return EXIT_FAILURE;
    }
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


/**
 * @brief Returns 1 if the result is a success, 0 otherwise.
 *
 * @param result standard C error codes of 0 for success, non-zero for failure.
 * @return int
 */
int is_success(int result)
{
    return result == 0;
}

int64_t generateSeed()
{
    return (int64_t)rand() << 32 | rand();
}

typedef int (*seed_callback_t)(Generator *generator, int64_t seed);

int find_seeds(seed_callback_t callback, int max_seeds)
{
    max_seeds = max_seeds > 0 ? max_seeds : 1024;

    // DynamicArray *seed_list = dynarray_new(sizeof(int64_t));
    int64_t seed_list[500] = {0};
    int seed_count = 0;

    Generator g;
    setupGenerator(&g, MC_VERSION, 0);

    printf("Finding seeds...\n");

    char *buffer = (char *)malloc(128);

    for (int i = 0; i < max_seeds; i++)
    {
        int64_t seed = generateSeed();

        applySeed(&g, DIM_OVERWORLD, seed);

        progress_bar(buffer, "Finding seeds", i+1, max_seeds);
        // Pass the correctly formatted string to fputs so double percent signs work and no newlines are added.
        fputs(buffer, stdout);

        if (callback(&g, seed))
        {
            seed_list[seed_count++] = seed;
            printf("Found seed: %lli\n", seed);
        }
    }

    for (int i = 0; i < seed_count; i++)
    {
        printf("%i. %lli\n", i, seed_list[i]);
    }

    printf("\n");
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
    r.y = 15, r.sy = 1;

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
    draw_grid(rgb, r.sx, r.sz, pix4cell, 0);
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
        return EXIT_FAILURE;
    }

    // Clean up.
    free(map_name);
    free(biomeIds);
    free(rgb);

    fprintf(stdout, "Done!\n");

    fflush(stderr);
    fflush(stdout);

    return EXIT_SUCCESS;
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

int parse_arguments(struct Arguments *arguments, int argc, char **argv)
{
    ArgParser *parser = ap_new_parser();
    if (!parser)
    {
        fprintf(stderr, "Failed to allocate memory for parser!\n");
        return EXIT_FAILURE;
    }

    ap_set_version(parser, VERSION);
    ap_set_helptext(parser, "Generate an image of the seed.");

    ap_add_str_opt(parser, "seed s", "0");
    ap_add_flag(parser, "help h");

    // Sweet spot for checking spawn is scale 4, width 1024, height 1024, cell 4
    ap_add_int_opt(parser, "scale", 16);
    ap_add_int_opt(parser, "width", 512);
    ap_add_int_opt(parser, "height", 512);
    ap_add_int_opt(parser, "cell", 1);
    ap_add_flag(parser, "dryrun n");

    if (!ap_parse(parser, argc, argv))
    {
        fprintf(stderr, "Failed to parse arguments!\n");
        return EXIT_FAILURE;
    }

    if (ap_found(parser, "help"))
    {
        ap_print(parser);
        return 0;
    }

    if (ap_found(parser, "dryrun"))
    {
        printf("Dry run!\n");
        arguments->dryrun = 1;
        return 0;
    }


    if (ap_found(parser, "seed")) {
        char *sseed = ap_get_str_value(parser, "seed");
        printf("Seed as string: %s\n", sseed);
        // Convert signed 64-bit integer to unsigned 64-bit integer
        char *end = NULL;

        arguments->seed = strtoull(sseed, &end, 10);
    }

    // Because these have fallback values, we don't care if they were found or not, always get the value!
    arguments->map_scale  = ap_get_int_value(parser, "scale");
    arguments->map_width  = ap_get_int_value(parser, "width");
    arguments->map_height = ap_get_int_value(parser, "height");
    arguments->pix4cell   = ap_get_int_value(parser, "cell");

    ap_free(parser);

    return EXIT_SUCCESS;
}

int validSeed(Generator *gen, int64_t seed)
{
    Pos spawn = getSpawn(gen);
    int biomeId = getBiomeAt(gen, 1, spawn.x, 255, spawn.z);

    if (in_biomes(biomeId, OCEAN_BIOMES)) {
        return 1;
    }

    return 0;
}

#include <windows.h>
#include <stdio.h>

BOOL WINAPI consoleHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        printf("\nCtrl-C handled\n");
        exit(0);
    }

    return FALSE;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    SetConsoleCtrlHandler(consoleHandler, TRUE);

    struct Arguments options = {0};
    parse_arguments(&options, argc, argv);

    find_seeds(validSeed, 50000);

    /*
    uint64_t seed   = options.seed;        // 0
    int map_scale   = options.map_scale;   // 16
    int map_width   = options.map_width;   // 512
    int map_height  = options.map_height; // 512
    int pix4cell    = options.pix4cell;     // 1

    if (!is_success(generate_seed_image(seed, map_scale, map_width, map_height, pix4cell))) {
        fprintf(stderr, "Failed to generate seed image\n%#X!\n", errno);
        return EXIT_FAILURE;
    }
    */

    return EXIT_SUCCESS;
}
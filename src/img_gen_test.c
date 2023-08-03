// Disable this file from compilation
#if false

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



int validSeed(Generator *gen, int64_t seed)
{
    Pos spawn = getSpawn(gen);
    int biomeId = getBiomeAt(gen, 1, spawn.x, 255, spawn.z);

    if (in_biomes(biomeId, OCEAN_BIOMES)) {
        return 1;
    }

    return 0;
}

int mainOld(int argc, char **argv)
{
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

#endif
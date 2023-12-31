#pragma once

#define COMPASS_HEIGHT 30
#define COMPASS_WIDTH 30

// array size is 3600
static const unsigned char COMPASS_ICON[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 61, 61, 61, 25, 56, 56, 56, 104, 56, 56, 56, 104, 56, 56, 56, 104, 56, 56, 56, 104, 56, 56, 56, 104,
    56, 56, 56, 104, 56, 56, 56, 104, 56, 56, 56, 104, 56, 56, 56, 104, 58, 58, 58, 104, 56, 56, 56, 36, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 51, 51, 51, 54, 58, 58, 58, 255, 55, 55, 55, 255, 54, 54, 54, 255, 54, 54, 54, 255, 54, 54, 54, 255,
    54, 54, 54, 255, 54, 54, 54, 255, 54, 54, 54, 255, 54, 54, 54, 255, 58, 58, 58, 255, 51, 51, 51, 85, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 121, 57, 57,
    57, 163, 51, 51, 51, 163, 64, 64, 64, 186, 85, 85, 85, 255, 92, 92, 92, 255, 104, 104, 104, 255, 102, 102, 102, 255, 102, 102, 102, 255,
    102, 102, 102, 255, 102, 102, 102, 255, 102, 102, 102, 255, 102, 102, 102, 255, 107, 107, 107, 255, 77, 77, 77, 195, 48, 48, 48, 163, 54, 54,
    54, 163, 53, 53, 53, 137, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55, 55, 55, 204, 62, 62,
    62, 255, 56, 56, 56, 255, 70, 70, 70, 255, 102, 102, 102, 255, 116, 116, 116, 255, 134, 134, 134, 255, 132, 132, 132, 255, 132, 132, 132, 255,
    132, 132, 132, 255, 132, 132, 132, 255, 132, 132, 132, 255, 132, 132, 132, 255, 137, 137, 137, 255, 86, 86, 86, 255, 54, 54, 54, 255, 61, 61,
    61, 255, 56, 56, 56, 231, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 52, 52, 107, 55, 55, 55, 215, 85, 85, 85, 244, 98, 98,
    98, 255, 97, 97, 97, 255, 85, 85, 85, 255, 53, 53, 53, 255, 57, 57, 57, 255, 59, 59, 59, 255, 59, 59, 59, 255, 59, 59, 59, 255,
    59, 59, 59, 255, 59, 59, 59, 255, 60, 59, 59, 255, 56, 60, 60, 255, 46, 57, 57, 255, 89, 100, 100, 255, 115, 126, 126, 255, 173, 175,
    175, 255, 163, 162, 162, 248, 55, 55, 55, 215, 49, 49, 51, 134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 46, 46, 46, 11, 53, 53, 53, 38, 61, 61, 61, 157, 68, 68, 68, 255, 86, 86, 86, 255, 95, 95,
    95, 255, 96, 96, 96, 255, 81, 81, 81, 255, 43, 43, 43, 255, 44, 44, 44, 255, 44, 44, 44, 255, 44, 44, 44, 255, 44, 44, 44, 255,
    44, 44, 44, 255, 44, 44, 44, 255, 41, 44, 44, 255, 57, 41, 41, 255, 70, 31, 31, 255, 123, 84, 84, 255, 155, 116, 116, 255, 176, 170,
    170, 255, 161, 162, 162, 255, 73, 73, 73, 255, 60, 60, 59, 184, 26, 13, 0, 38, 34, 17, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 75, 55, 55, 55, 255, 81, 81, 81, 255, 109, 109, 109, 255, 61, 61, 61, 255, 44, 44,
    44, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255,
    48, 47, 47, 255, 44, 48, 48, 255, 13, 55, 55, 255, 123, 30, 30, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 77, 35,
    35, 255, 50, 62, 62, 255, 140, 141, 142, 255, 97, 94, 87, 255, 25, 14, 0, 255, 29, 19, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 53, 53, 53, 76, 57, 57, 57, 255, 70, 70, 70, 255, 85, 85, 85, 255, 55, 55, 55, 255, 44, 44,
    44, 255, 46, 46, 46, 255, 46, 46, 46, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255,
    43, 48, 48, 255, 62, 44, 44, 255, 110, 33, 33, 255, 177, 18, 18, 255, 255, 0, 0, 255, 209, 9, 9, 255, 177, 17, 17, 255, 64, 38,
    38, 255, 47, 55, 55, 255, 104, 105, 106, 255, 75, 72, 65, 255, 27, 16, 0, 255, 29, 19, 0, 105, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 75, 59, 59, 59, 255, 49, 49, 49, 255, 42, 42, 42, 255, 46, 46, 46, 255, 47, 47,
    47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 43, 42, 42, 255, 40, 41, 41, 255,
    19, 52, 52, 255, 78, 40, 40, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 117, 31, 31, 255, 14, 55, 55, 255, 45, 48,
    48, 255, 47, 46, 46, 255, 42, 43, 44, 255, 37, 33, 27, 255, 31, 20, 0, 255, 29, 19, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 75, 59, 59, 59, 255, 51, 51, 51, 255, 46, 46, 46, 255, 47, 47, 47, 255, 47, 47,
    47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 44, 44, 44, 255, 79, 82, 82, 255, 100, 95, 95, 255,
    158, 28, 28, 255, 188, 15, 15, 255, 255, 0, 0, 255, 206, 11, 11, 255, 123, 30, 30, 255, 77, 40, 40, 255, 40, 49, 49, 255, 47, 47,
    47, 255, 47, 47, 47, 255, 48, 49, 50, 255, 41, 37, 31, 255, 31, 20, 0, 255, 29, 19, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 75, 59, 59, 59, 255, 51, 51, 51, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47,
    47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 47, 47, 47, 255, 42, 42, 42, 255, 105, 111, 111, 255, 144, 134, 134, 255,
    255, 10, 10, 255, 255, 0, 0, 255, 255, 0, 0, 255, 166, 20, 20, 255, 13, 55, 55, 255, 41, 48, 48, 255, 48, 47, 47, 255, 47, 47,
    47, 255, 47, 47, 47, 255, 49, 50, 51, 255, 41, 37, 31, 255, 31, 20, 0, 255, 29, 19, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 75, 61, 61, 61, 255, 39, 39, 39, 255, 19, 19, 19, 255, 42, 42, 42, 255, 49, 49,
    49, 255, 48, 48, 48, 255, 48, 48, 48, 255, 47, 47, 47, 255, 47, 47, 47, 255, 42, 42, 42, 255, 106, 107, 107, 255, 134, 132, 132, 255,
    93, 48, 48, 255, 85, 35, 35, 255, 88, 38, 38, 255, 71, 42, 42, 255, 44, 48, 48, 255, 48, 48, 48, 255, 48, 48, 48, 255, 49, 49,
    49, 255, 44, 44, 44, 255, 23, 24, 26, 255, 26, 22, 16, 255, 33, 21, 0, 255, 29, 19, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 75, 60, 60, 60, 255, 43, 43, 43, 255, 29, 29, 29, 255, 41, 41, 41, 255, 45, 45,
    45, 255, 44, 44, 44, 255, 45, 45, 45, 255, 47, 47, 47, 255, 47, 47, 47, 255, 43, 43, 43, 255, 99, 99, 99, 255, 121, 121, 121, 255,
    46, 57, 57, 255, 34, 47, 47, 255, 36, 49, 49, 255, 41, 48, 48, 255, 48, 47, 47, 255, 45, 45, 45, 255, 44, 44, 44, 255, 45, 45,
    45, 255, 42, 42, 42, 255, 28, 29, 31, 255, 30, 26, 19, 255, 32, 21, 0, 255, 29, 19, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 75, 52, 52, 52, 255, 92, 92, 92, 255, 135, 135, 135, 255, 39, 39, 39, 255, 5, 5,
    5, 255, 14, 14, 14, 255, 24, 24, 24, 255, 50, 50, 50, 255, 49, 49, 49, 255, 49, 49, 49, 255, 51, 51, 51, 255, 51, 51, 51, 255,
    49, 49, 49, 255, 49, 49, 49, 255, 49, 49, 49, 255, 49, 49, 49, 255, 51, 51, 51, 255, 29, 29, 29, 255, 15, 15, 15, 255, 15, 15,
    15, 255, 30, 30, 30, 255, 101, 102, 103, 255, 73, 70, 63, 255, 27, 16, 0, 255, 29, 19, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 75, 52, 52, 52, 255, 95, 95, 95, 255, 138, 138, 138, 255, 87, 87, 87, 255, 68, 68,
    68, 255, 55, 55, 55, 255, 49, 49, 49, 255, 39, 39, 39, 255, 39, 39, 39, 255, 40, 40, 40, 255, 38, 38, 38, 255, 38, 38, 38, 255,
    39, 39, 39, 255, 40, 40, 40, 255, 40, 40, 40, 255, 40, 40, 40, 255, 39, 39, 39, 255, 43, 43, 43, 255, 45, 45, 45, 255, 42, 42,
    42, 255, 53, 53, 53, 255, 106, 107, 108, 255, 76, 73, 66, 255, 27, 16, 0, 255, 29, 19, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 53, 53, 53, 81, 56, 56, 56, 255, 99, 100, 101, 255, 138, 139, 140, 255, 187, 187, 187, 255, 202, 202,
    202, 255, 145, 145, 145, 255, 101, 101, 101, 255, 6, 6, 6, 255, 11, 11, 11, 255, 12, 12, 12, 255, 12, 12, 12, 255, 12, 12, 12, 255,
    12, 12, 12, 255, 12, 12, 12, 255, 12, 12, 12, 255, 13, 13, 13, 255, 7, 7, 7, 255, 71, 71, 71, 255, 111, 111, 111, 255, 104, 104,
    103, 255, 104, 104, 104, 255, 110, 112, 115, 255, 79, 76, 69, 255, 29, 17, 0, 255, 29, 20, 0, 113, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 58, 58, 58, 35, 53, 53, 53, 120, 69, 65, 58, 191, 75, 69, 61, 255, 165, 164, 162, 255, 196, 196,
    197, 255, 136, 136, 136, 255, 113, 113, 113, 255, 75, 75, 75, 255, 77, 77, 77, 255, 77, 77, 77, 255, 77, 77, 77, 255, 77, 77, 77, 255,
    77, 77, 77, 255, 77, 77, 77, 255, 78, 78, 78, 255, 72, 72, 72, 255, 59, 59, 59, 255, 86, 86, 86, 255, 102, 102, 103, 255, 101, 101,
    102, 255, 94, 93, 92, 255, 66, 61, 51, 255, 55, 49, 36, 207, 27, 17, 0, 120, 31, 20, 0, 49, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 7, 0, 129, 17, 5, 0, 255, 157, 155, 150, 255, 205, 206,
    208, 255, 136, 137, 137, 255, 130, 131, 131, 255, 136, 136, 136, 255, 136, 136, 136, 255, 136, 136, 136, 255, 136, 136, 136, 255, 136, 136, 136, 255,
    136, 136, 136, 255, 136, 136, 136, 255, 138, 138, 138, 255, 124, 124, 124, 255, 103, 103, 103, 255, 103, 104, 104, 255, 102, 102, 103, 255, 105, 106,
    108, 255, 90, 89, 86, 255, 27, 16, 0, 255, 21, 12, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 15, 0, 32, 24, 12, 0, 63, 67, 58, 44, 211, 74, 66,
    50, 255, 52, 44, 33, 255, 73, 67, 56, 255, 133, 134, 135, 255, 129, 131, 131, 255, 129, 130, 130, 255, 129, 130, 130, 255, 129, 130, 130, 255,
    129, 130, 130, 255, 129, 130, 130, 255, 132, 132, 132, 255, 118, 118, 119, 255, 103, 103, 105, 255, 67, 62, 53, 255, 44, 36, 25, 255, 49, 42,
    26, 255, 45, 38, 24, 230, 32, 20, 0, 63, 25, 19, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 7, 0, 174, 21, 8,
    0, 237, 17, 5, 0, 237, 49, 41, 25, 242, 125, 125, 125, 255, 121, 121, 120, 255, 121, 120, 119, 255, 121, 120, 119, 255, 121, 120, 119, 255,
    121, 120, 119, 255, 121, 120, 119, 255, 123, 122, 121, 255, 110, 110, 108, 255, 98, 97, 98, 255, 51, 43, 31, 243, 20, 8, 0, 237, 26, 16,
    0, 237, 25, 15, 0, 199, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 21, 0, 12, 30, 15,
    0, 17, 30, 15, 0, 17, 35, 25, 6, 80, 40, 30, 10, 255, 39, 29, 10, 255, 39, 29, 10, 255, 39, 29, 10, 255, 39, 29, 10, 255,
    39, 29, 10, 255, 39, 29, 10, 255, 39, 29, 10, 255, 38, 28, 9, 255, 39, 28, 8, 255, 35, 23, 7, 107, 30, 15, 0, 17, 30, 15,
    0, 17, 36, 18, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 24, 18, 0, 42, 28, 17, 0, 190, 26, 16, 0, 190, 26, 16, 0, 190, 26, 16, 0, 190, 26, 16, 0, 190,
    26, 16, 0, 190, 26, 16, 0, 190, 26, 16, 0, 190, 26, 16, 0, 190, 29, 18, 0, 190, 28, 16, 0, 63, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

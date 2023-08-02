cmake_minimum_required(VERSION 3.13)
project(mc_seed_renderer C)
set(CMAKE_C_STANDARD 11)

add_subdirectory(lib/libcubiomes)

FILE(GLOB SOURCE_FILES src/*.c)
FILE(GLOB HEADER_FILES include/*.h)

add_executable(mc_seed_renderer ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(mc_seed_renderer PUBLIC include)
target_include_directories(mc_seed_renderer PUBLIC lib/libcubiomes)

target_link_libraries(mc_seed_renderer libcubiomes)
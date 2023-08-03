cmake_minimum_required(VERSION 3.13)
project(mc_seed_renderer C)
set(CMAKE_C_STANDARD 11)

# add_custom_target(clean, COMMAND rm -rf ${CMAKE_BINARY_DIR}/*)

add_subdirectory(lib/libcubiomes)

FILE(GLOB SOURCE_FILES src/*.c)
FILE(GLOB HEADER_FILES include/*.h)
LIST(APPEND HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/olive.c/olive.c)
LIST(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/olive.c/olive.c)

add_executable(mc_seed_renderer ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(mc_seed_renderer PUBLIC include)
target_include_directories(mc_seed_renderer PUBLIC lib/libcubiomes)
target_include_directories(mc_seed_renderer PUBLIC lib/olive.c)

target_link_libraries(mc_seed_renderer libcubiomes)

# Run the executable with arguments
add_custom_target(
    run_test
    COMMAND mc_seed_renderer test
    DEPENDS mc_seed_renderer
    COMMENT "Run a test, but not unit testing"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)
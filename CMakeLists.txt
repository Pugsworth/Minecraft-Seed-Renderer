CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
PROJECT(mc_seed_renderer C)
SET(CMAKE_C_STANDARD 11)

# find zlib and add it as a dependency because apparently it cannot be found anywhere by anything
# find_package(ZLIB REQUIRED)

# if (ZLIB_FOUND)
#     include_directories(${ZLIB_INCLUDE_DIRS})
# else()
#     message(FATAL_ERROR "Could not find zlib")
# endif()


FILE(GLOB SOURCE_FILES src/*.c)
FILE(GLOB HEADER_FILES include/*.h)
LIST(APPEND HEADER_FILES ${libspng_SOURCE_DIR}/spng/spng.h)
LIST(APPEND SOURCE_FILES ${libspng_SOURCE_DIR}/spng/spng.c)
LIST(APPEND HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/olive.c/olive.c)
LIST(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/olive.c/olive.c)

message(DEBUG ${HEADER_FILES})
message(DEBUG ${SOURCE_FILES})

add_subdirectory(lib)


ADD_EXECUTABLE(mc_seed_renderer ${SOURCE_FILES} ${HEADER_FILES})
TARGET_INCLUDE_DIRECTORIES(mc_seed_renderer PRIVATE include)


#
# libspng
#
# Nothing?/


#
# olive.c
#
TARGET_INCLUDE_DIRECTORIES(mc_seed_renderer PUBLIC lib/olive.c)


#
# libcubiomes
#
ADD_SUBDIRECTORY(lib/libcubiomes)
TARGET_INCLUDE_DIRECTORIES(mc_seed_renderer PUBLIC lib/libcubiomes)


#
# Finally, linking
#
# !!! z REQUIRED to link zlib for libspng
TARGET_LINK_LIBRARIES(mc_seed_renderer libcubiomes z spng_static winmm)



# Run the executable with arguments
ADD_CUSTOM_TARGET(
    run_test
    COMMAND mc_seed_renderer test
    DEPENDS mc_seed_renderer
    COMMENT "Run a test, but not unit testing"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)
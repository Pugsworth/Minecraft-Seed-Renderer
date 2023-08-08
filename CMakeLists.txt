CMAKE_MINIMUM_REQUIRED(VERSION 3.22.6)
PROJECT(mc_seed_renderer C)
SET(CMAKE_C_STANDARD 11)

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# include("./vcpkg/scripts/buildsystems/vcpkg.cmake")


# find_package(PkgConfig REQUIRED)

# find zlib and add it as a dependency because apparently it cannot be found anywhere by anything
# find_package(ZLIB REQUIRED)

# if (ZLIB_FOUND)
#     include_directories(${ZLIB_INCLUDE_DIRS})
# else()
#     message(FATAL_ERROR "Could not find zlib")
# endif()


# If we add lib first, it will use the CMakeLists.txt and perform the library fetching and configuration before we can use it.
add_subdirectory(lib)




FILE(GLOB SOURCE_FILES src/*.c)
FILE(GLOB HEADER_FILES include/*.h)
LIST(APPEND HEADER_FILES ${libspng_SOURCE_DIR}/spng/spng.h)
LIST(APPEND SOURCE_FILES ${libspng_SOURCE_DIR}/spng/spng.c)
LIST(APPEND HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/olive.c/olive.c)
LIST(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/olive.c/olive.c)

message(DEBUG ${HEADER_FILES})
message(DEBUG ${SOURCE_FILES})


ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE include)


#
# Lua (luajit in this case)
#
# pkg_check_modules(LuaJIT REQUIRED IMPORTED_TARGET luajit)
if(LUA_USE_JIT)
    find_package(LuaJIT REQUIRED)
else()
    find_package(Lua REQUIRED)
endif()


#
# libspng
#
# Nothing?/


#
# olive.c
#
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC lib/olive.c)


#
# libcubiomes
#
ADD_SUBDIRECTORY(lib/libcubiomes)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC lib/libcubiomes)


#
# Finally, linking
#
# !!! z REQUIRED to link zlib for libspng
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE libcubiomes)
target_link_libraries(${PROJECT_NAME} PRIVATE z)
target_link_libraries(${PROJECT_NAME} PRIVATE spng_static)
target_link_libraries(${PROJECT_NAME} PRIVATE winmm)

# TODO: Start with just this using vcpkg, then transition to the rest of ^^^ as much is possible.
target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LUA_LIBRARIES})



# Run the executable with arguments
ADD_CUSTOM_TARGET(
    run_test
    COMMAND ${PROJECT_NAME} test
    DEPENDS ${PROJECT_NAME}
    COMMENT "Run a test, but not unit testing"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)
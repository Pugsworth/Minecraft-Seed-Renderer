IF(WIN32)
    SET(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
ELSE()
    SET(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
ENDIF()
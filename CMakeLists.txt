cmake_minimum_required(VERSION 3.25)
project(breakThrough)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# ===== ASSIMP =====
find_package(PkgConfig QUIET)
if (PkgConfig_FOUND)
    pkg_check_modules(ASSIMP assimp)
endif ()

if (NOT ASSIMP_FOUND)
    find_package(assimp QUIET)
    if (TARGET assimp::assimp)
        set(ASSIMP_LIBRARIES assimp::assimp)
        set(ASSIMP_FOUND TRUE)
        message(STATUS "Found Assimp via find_package")
    endif ()
endif ()

# Fallback: manual paths for Homebrew on macOS
if (NOT ASSIMP_FOUND AND APPLE)
    set(HOMEBREW_PREFIX "/opt/homebrew")
    if (EXISTS "${HOMEBREW_PREFIX}/include/assimp")
        set(ASSIMP_INCLUDE_DIRS "${HOMEBREW_PREFIX}/include")
        set(ASSIMP_LIBRARIES "${HOMEBREW_PREFIX}/lib/libassimp.dylib")
        set(ASSIMP_FOUND TRUE)
        message(STATUS "Found Assimp via Homebrew: ${ASSIMP_LIBRARIES}")
    endif ()
endif ()

if (NOT ASSIMP_FOUND)
    message(FATAL_ERROR "Assimp not found! Please install it via: brew install assimp")
endif ()

# ===== FREETYPE =====
find_package(Freetype QUIET)

if (NOT FREETYPE_FOUND AND APPLE)
    set(HOMEBREW_PREFIX "/opt/homebrew")
    if (EXISTS "${HOMEBREW_PREFIX}/include/freetype2")
        set(FREETYPE_INCLUDE_DIRS "${HOMEBREW_PREFIX}/include/freetype2")
        set(FREETYPE_LIBRARIES "${HOMEBREW_PREFIX}/lib/libfreetype.dylib")
        set(FREETYPE_FOUND TRUE)
        message(STATUS "Found FreeType via Homebrew: ${FREETYPE_LIBRARIES}")
    endif ()
endif ()

if (NOT FREETYPE_FOUND)
    message(FATAL_ERROR "FreeType not found! Please install it via: brew install freetype")
endif ()

# ===== GLAD =====
add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# ===== COPY RESOURCES =====
add_custom_target(copy_resources
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${CMAKE_BINARY_DIR}/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
        COMMENT "Copying entire 'resources' folder to build directory"
)

# ===== SOURCES =====
set(SOURCES
        main.cpp
        shader.cpp
        texture.cpp
        game.cpp
        resource_manager.cpp
        windowmanager.cpp
        spriteRenderer.cpp
        gameobject.cpp
        gamelevel.cpp
)

add_executable(breakThrough ${SOURCES})

# ===== LINK LIBRARIES =====
target_link_libraries(breakThrough
        PRIVATE
        glfw
        glad
        OpenGL::GL
        ${ASSIMP_LIBRARIES}
        ${FREETYPE_LIBRARIES}
)

# ===== DEPENDENCIES =====
add_dependencies(breakThrough copy_resources)

# ===== INCLUDE DIRECTORIES =====
target_include_directories(breakThrough
        PRIVATE
        glad/include
        ${ASSIMP_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
)

# C++ features
target_compile_features(breakThrough PRIVATE cxx_std_20)

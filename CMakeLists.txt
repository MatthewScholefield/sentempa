cmake_minimum_required(VERSION 3.12)
project(sentempa)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)
find_package(SDL2 REQUIRED)
pkg_search_module(SDL2GFX REQUIRED SDL2_gfx)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS})

add_executable(
        sentempa
        source/Camera.cpp
        source/Camera.hpp
        source/Enemy.cpp
        source/Enemy.hpp
        source/InputManager.cpp
        source/InputManager.hpp
        source/main.cpp
        source/Polygon.cpp
        source/Polygon.hpp
        source/Renderer.cpp
        source/Renderer.hpp
        source/SdlManager.cpp
        source/SdlManager.hpp
        source/StarField.cpp
        source/StarField.hpp
        source/Timer.cpp
        source/Timer.hpp
        source/types.hpp
        source/Utility.cpp
        source/Utility.hpp
        source/Vec.hpp
        source/Vec.inl
)

target_link_libraries(sentempa ${SDL2_LIBRARIES} ${SDL2GFX_LIBRARIES})
target_link_libraries(sentempa ${SDL2_GFX_LIBRARIES})

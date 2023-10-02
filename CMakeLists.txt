cmake_minimum_required(VERSION 3.25)
project(vigilante)

set(CMAKE_CXX_STANDARD 23)

set(LD_OPTIONS "")

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(LD_OPTIONS "${LD_OPTIONS}-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]' -s WASM=1 --preload-file assets")
endif ()

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable("Vigilante"
        src/main.cpp
        src/Game.cpp
        src/Scene/Scene.cpp
        src/AssetStore/AssetStore.cpp
        src/Systems/RenderSystem.cpp
        src/Systems/InputKeyboardSystem.cpp
        src/Systems/AnimationSystem.cpp
        src/Systems/CameraMovementSystem.cpp
        src/Systems/JumpSystem.cpp
        src/Systems/CollisionSystem.cpp
        src/Systems/MovementSystem.cpp
        src/Systems/Debug/DebugRenderCollisionSystem.h
        src/Systems/Debug/DebugRenderCollisionSystem.cpp
)

target_link_libraries("Vigilante"
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        Microsoft.GSL::GSL
        spdlog::spdlog spdlog::spdlog_header_only
        fmt::fmt
        EnTT::EnTT
        glm::glm
        "${LD_OPTIONS}"
)

file(COPY assets DESTINATION .)
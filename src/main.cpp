#include "Game.h"

#include <spdlog/spdlog.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

Game game{};

void runLoop() {
    game.ProcessInput();
    game.UpdateGame();
    game.GenerateOutput();
}

int main(int argc, char *argv[]) {
    GameConfig config = {
            .title = "Vigilante Clone",
            .screenWidth = 800,
            .screenHeight = 600,
            .windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL,
            .renderLogicalScaleX = 0.26f,
            .renderLogicalScaleY = 0.26f
    };

    if (!game.Initialize(config)) {
        spdlog::critical("error to initialize the game class");
        return 1;
    }

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(runLoop, 0, 1);
#else
    while (game.IsRunning()) {
        runLoop();
    }
#endif
    game.Shutdown();

    return 0;
}
#include "Game.h"

#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
    Game game;
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

    game.RunLoop();
    game.Shutdown();

    return 0;
}
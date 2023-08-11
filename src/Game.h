#ifndef VIGILANTE_GAME_H
#define VIGILANTE_GAME_H

#include "AssetStore/AssetStore.h"
#include "Scene/Scene.h"

#include <string>
#include <SDL.h>

typedef struct {
    std::string title;
    int screenWidth;
    int screenHeight;
    int windowFlags;
    float renderLogicalScaleX;
    float renderLogicalScaleY;
} GameConfig;

class Game {
public:
    Game() = default;

    bool Initialize(const GameConfig &config);

    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    bool IsRunning() const;

    void Shutdown();

private:
    bool m_isRunning{};
    uint32_t m_ticksCount{};

    GameConfig m_config;

    SDL_Window *m_window{};
    SDL_Renderer *m_renderer{};

    std::unique_ptr<Scene> m_currentScene;

    //void initializeOpenGL();
};


#endif //VIGILANTE_GAME_H

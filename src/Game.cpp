#include "Game.h"
#include "GameClock.h"

#include <gsl/gsl>
#include <SDL_image.h>
#include <spdlog/spdlog.h>

bool Game::Initialize(const GameConfig &cfg) {
    m_config = cfg;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        spdlog::error("initializing sdl: " + std::string(SDL_GetError()));
        return false;
    }

    m_window = SDL_CreateWindow(
            m_config.title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_config.screenWidth,
            m_config.screenHeight,
            m_config.windowFlags | SDL_WINDOW_RESIZABLE
    );

    if (!m_window) {
        spdlog::error("creating sdl window: " + std::string(SDL_GetError()));
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, 0, SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
        spdlog::error("creating sdl renderer: " + std::string(SDL_GetError()));
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        spdlog::error("initializing sdl image for png: " + std::string(IMG_GetError()));
        return false;
    }

    SDL_RenderSetLogicalSize(
            m_renderer,
            gsl::narrow_cast<int>(float(m_config.screenWidth) * m_config.renderLogicalScaleX),
            gsl::narrow_cast<int>(float(m_config.screenHeight) * m_config.renderLogicalScaleY)
    );

    m_currentScene = std::make_unique<Scene>(m_window, m_renderer);
    m_currentScene->Initialize();

    return true;
}

void Game::RunLoop() {
    m_isRunning = true;

    while (m_isRunning) {
        processInput();
        updateGame();
        generateOutput();
    }
}

void Game::processInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_isRunning = false;
                break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE]) {
        m_isRunning = false;
    }
}

void Game::updateGame() {
    auto frameTime = float(SDL_GetTicks() - m_ticksCount);
    if (frameTime < FRAME_TIME_MILLISECONDS) {
        SDL_Delay(FRAME_TIME_MILLISECONDS - frameTime);
    }

    float deltaTime = float(SDL_GetTicks() - m_ticksCount) / SECOND_IN_MILLISECONDS;
    if (deltaTime > MAX_DELTA_TIME_MILLISECONDS) {
        deltaTime = MAX_DELTA_TIME_MILLISECONDS;
    }

    m_ticksCount = SDL_GetTicks();

    m_currentScene->Update(deltaTime);
}

void Game::generateOutput() {
    m_currentScene->Render();
}

void Game::Shutdown() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    IMG_Quit();
    SDL_Quit();
}
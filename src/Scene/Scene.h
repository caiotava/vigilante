#ifndef VIGILANTE_SCENE_H
#define VIGILANTE_SCENE_H

#include "AssetStore/AssetStore.h"
#include "Systems/System.h"

#include <SDL.h>
#include <entt/entt.hpp>

class Scene {
public:
    Scene(SDL_Window *window, SDL_Renderer *renderer);

    bool Initialize();
    bool Update(float deltaTime);
    bool Render();

private:
    entt::registry m_registry{};
    std::shared_ptr<entt::dispatcher> m_dispatcher;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    std::shared_ptr<AssetStore> m_assetStore;

    std::vector<std::unique_ptr<System>> m_systemsUpdate;
    std::vector<std::unique_ptr<System>> m_systemsRender;

    int rendererWidth = {0};
    int rendererHeight = {0};

    void initializeSystems();
    void initializeContext();
    void initializeCamera();
    void createPlayerEntity();
    void createEnemyEntity();
    void createBackgroundEntity();
    void createLevelBoundaries();
};


#endif //VIGILANTE_SCENE_H

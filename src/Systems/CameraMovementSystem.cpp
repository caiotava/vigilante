#include "CameraMovementSystem.h"

#include "Components/Components.h"

void CameraMovementSystem::Update(entt::registry &registry, float deltaTime) {
    auto view = registry.view<TransformComponent, CameraFollowComponent>();
    auto &camera = registry.ctx().get<CameraComponent>();
    auto renderer = registry.ctx().get<SDL_Renderer *>();

    int rendererWidth, rendererHeight{};
    SDL_RenderGetLogicalSize(renderer, &rendererWidth, &rendererHeight);

    for (auto entity: view) {
        auto transform = view.get<TransformComponent>(entity);

        if (transform.Transform.x + (camera.Rect.w / 2.0f) < camera.Bounds.x) {
            camera.Rect.x = transform.Transform.x - (float(rendererWidth) / 2.0f);
        }

        if (transform.Transform.y + (camera.Rect.h / 2.0f) < camera.Bounds.y) {
            camera.Rect.y = transform.Transform.y - (float(rendererHeight) / 2.0f);
        }

        // Keep camera rectangle view inside the screen limits
        camera.Rect.x = camera.Rect.x < 0 ? 0 : camera.Rect.x;
        camera.Rect.y = camera.Rect.y < 0 ? 0 : camera.Rect.y;
        camera.Rect.x = camera.Rect.x > camera.Bounds.x ? camera.Bounds.x : camera.Rect.x;
        camera.Rect.y = camera.Rect.y > camera.Rect.h ? camera.Rect.h : camera.Rect.y;
    }
}
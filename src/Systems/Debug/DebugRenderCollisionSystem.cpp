#include "DebugRenderCollisionSystem.h"

#include "Components/Components.h"

#include <SDL.h>

void DebugRenderCollisionSystem::Update(entt::registry &registry, float deltaTime) {
    auto view = registry.view<TransformComponent, CollisionComponent>();
    auto renderer = registry.ctx().get<SDL_Renderer *>();
    auto camera = registry.ctx().get<CameraComponent>();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

    for (auto entity : view) {
        auto &transform = view.get<TransformComponent>(entity);
        auto &collision = view.get<CollisionComponent>(entity);

        SDL_FRect rect = {
                .x = std::floor(transform.Transform.x )- camera.Rect.x,
                .y = std::floor(transform.Transform.y) - camera.Rect.y,
                .w = collision.Rect.w,
                .h = collision.Rect.h
        };

        SDL_RenderDrawRectF(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}
#include "RenderSystem.h"

#include "AssetStore/AssetStore.h"
#include "Components/Components.h"

#include <SDL.h>

void RenderSystem::Update(entt::registry &registry, const float deltaTime) {
    auto renderer = registry.ctx().get<SDL_Renderer *>();
    auto assetStore = registry.ctx().get<std::shared_ptr<AssetStore>>();
    auto camera = registry.ctx().get<CameraComponent>();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    auto group = registry.group<TransformComponent>(entt::get<SpriteComponent>);

    for (auto entity: group) {
        auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

        SDL_FRect dstRect = {
                .x = transform.Transform.x - (sprite.IsFixed ? 0.0f : camera.Rect.x),
                .y = transform.Transform.y - (sprite.IsFixed ? 0.0f : camera.Rect.y),
                .w = float(sprite.RectSource.w),
                .h = float(sprite.RectSource.h)
        };

        SDL_RenderCopyExF(
                renderer,
                assetStore->GetTexture(sprite.AssertID),
                &sprite.RectSource,
                &dstRect,
                0,
                nullptr,
                sprite.Flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        );
    }

    SDL_RenderPresent(renderer);
}
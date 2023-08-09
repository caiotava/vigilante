#include "CollisionSystem.h"

#include "Components/Components.h"
#include "Events/EventCollision.h"

#include <SDL.h>
#include <spdlog/spdlog.h>

void CollisionSystem::Update(entt::registry &registry, float deltaTime) {
    auto view = registry.view<TransformComponent, CollisionComponent, RigidBodyComponent>();

    for (auto itA = view.begin(); itA != view.end(); itA++) {
        auto entityA = *itA;
        auto &transformA = view.get<TransformComponent>(entityA);
        auto &collisionA = view.get<CollisionComponent>(entityA);
        auto rigidBodyA = view.get<RigidBodyComponent>(entityA);

        SDL_FRect rectA = {
                .x = std::floor(transformA.Transform.x),
                .y = std::floor(transformA.Transform.y),
                .w = collisionA.Rect.w,
                .h = collisionA.Rect.h
        };

        for (auto itB = std::next(itA); itB != view.end(); itB++) {
            auto entityB = *itB;
            if (entityA == entityB) {
                continue;
            }

            auto &transformB = view.get<TransformComponent>(entityB);
            auto &collisionB = view.get<CollisionComponent>(entityB);
            auto &rigidBodyB = view.get<RigidBodyComponent>(entityB);

            SDL_FRect rectB = {
                    .x = std::floor(transformB.Transform.x),
                    .y = std::floor(transformB.Transform.y),
                    .w = collisionB.Rect.w,
                    .h = collisionB.Rect.h
            };

            // if there isn't collision we should not do anything.
            if (!SDL_HasIntersectionF(&rectA, &rectB)) {
                continue;
            }

            if (!rigidBodyA.NeedCollisionFix(rigidBodyB)) {
                auto dispatcher = registry.ctx().get<std::shared_ptr<entt::dispatcher>>();

                EventCollision event = {
                        .registry = &registry,
                        .entityCollisionA = entityA,
                        .entityCollisionB = entityB
                };

                dispatcher->trigger(event);
                continue;
            }

            SDL_FRect intersectionCollisionRect{};
            SDL_IntersectFRect(&rectA, &rectB, &intersectionCollisionRect);

            if (!rigidBodyA.IsStatic) {
                auto fixRect = fixCollisionPosition(intersectionCollisionRect, rectA);

                transformA.Transform.x = fixRect.x;
                transformA.Transform.y = fixRect.y;
            } else if (!rigidBodyB.IsStatic) {
                auto fixRect = fixCollisionPosition(intersectionCollisionRect, rectB);

                transformB.Transform.x = fixRect.x;
                transformB.Transform.y = fixRect.y;
            }
        }
    }
}

SDL_FRect CollisionSystem::fixCollisionPosition(const SDL_FRect &rectIntersection, const SDL_FRect pos) {
    SDL_FRect result = pos;

    if (rectIntersection.w != result.w) {
        result.x -= rectIntersection.w;
    }

    if (rectIntersection.h != result.h) {
        result.y = result.y - rectIntersection.h;
    }

    return result;
}

void CollisionSystem::OnCollision(const EventCollision &event) {
    spdlog::info("collision between to entities: {} and {} ", static_cast<std::uint32_t>(event.entityCollisionA),  static_cast<std::uint32_t>(event.entityCollisionB));
}
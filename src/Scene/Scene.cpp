#include "Scene.h"

#include "Components/Components.h"
#include "Systems/Systems.h"
#include "Events/EventCollision.h"

const int maxBackgroundX = 2040;
const int maxBackgroundY = 160;

Scene::Scene(SDL_Window *window, SDL_Renderer *renderer) {
    m_window = window;
    m_renderer = renderer;
    m_assetStore = std::make_shared<AssetStore>(m_renderer);
    m_dispatcher = std::make_shared<entt::dispatcher>();
}

bool Scene::Initialize() {
    using namespace entt::literals;
    m_systemsUpdate.push_back(std::make_shared<InputKeyboardSystem>());
    m_systemsUpdate.push_back(std::make_shared<AnimationSystem>());
    m_systemsUpdate.push_back(std::make_shared<CameraMovementSystem>());
    m_systemsUpdate.push_back(std::make_shared<JumpSystem>());
    m_systemsUpdate.push_back(std::make_shared<MovementSystem>());
    m_systemsUpdate.push_back(std::make_shared<CollisionSystem>());

    m_systemsRender.push_back(std::make_shared<RenderSystem>());

    m_dispatcher->sink<EventCollision>().connect<&CollisionSystem::OnCollision>();

    m_registry.ctx().emplace<SDL_Window *>(m_window);
    m_registry.ctx().emplace<SDL_Renderer *>(m_renderer);
    m_registry.ctx().emplace<std::shared_ptr<AssetStore>>(m_assetStore);
    m_registry.ctx().emplace<std::shared_ptr<entt::dispatcher>>(m_dispatcher);

    int rendererWidth, rendererHeight{};
    SDL_RenderGetLogicalSize(m_renderer, &rendererWidth, &rendererHeight);

    entt::entity camera = m_registry.create();
    SDL_FRect cameraRect = {.x = 0, .y = 0, .w = float(rendererWidth), .h = float(rendererHeight * 2)};
    m_registry.emplace<TransformComponent>(camera, glm::vec2{0, 0});
    auto &cameraComponent = m_registry.emplace<CameraComponent>(camera, cameraRect, glm::vec2(maxBackgroundX, maxBackgroundY));

    m_registry.ctx().emplace<CameraComponent &>(cameraComponent);

    entt::entity player = m_registry.create();
    m_assetStore->AddTexture("player", "./assets/gfx/chars/vigilante.png");
    AnimationPlayerComponent animationPlayer = {"idle", true};
    animationPlayer.AddAnimation({"idle", 0, 0, 0, 0}).
            AddAnimation({"walk", 1, 0, 4, 130}).
            AddAnimation({"punch", 5, 0,  2, 200, "idle", true}).
            AddAnimation({"kick", 9, 0, 2, 200, "idle", true}).
            AddAnimation({"jump", 6, 1, 3, 200, "idle", true}).
            AddAnimation({"crouch", 4, 1, 0, 0}).
            AddAnimation({"crouch-punch", 0, 1,  2, 100, "crouch", true}).
            AddAnimation({"crouch-kick", 5, 1, 1, 200, "crouch", true});
    m_registry.emplace<AnimationPlayerComponent>(player, animationPlayer);
    m_registry.emplace<TransformComponent>(player, glm::vec2{rendererWidth / 2, 85.0f});
    m_registry.emplace<JumpComponent>(player, 300.0f, 1000.0f);
    m_registry.emplace<RigidBodyComponent>(player);
    m_registry.emplace<CameraFollowComponent>(player);
    SDL_Rect rectSrcPlayer = {.x = 11, .y = 0, .w = 40, .h = 47};
    SDL_FRect rectFSrcPlayer = {.x = 0, .y = 0, .w = 40, .h = 47};
    m_registry.emplace<CollisionComponent>(player, rectFSrcPlayer);
    m_registry.emplace<SpriteComponent>(player, "player", rectSrcPlayer);
    m_registry.emplace<TagComponent>(player, "player");
    m_registry.emplace<entt::tag<"enemy"_hs>>(player);
    m_registry.emplace<InputKeyboardComponent>(player);

    entt::entity enemy = m_registry.create();
    m_assetStore->AddTexture("enemy", "./assets/gfx/chars/rogues.png");
    AnimationPlayerComponent animationPlayerEnemy = {"walk", true};
    animationPlayerEnemy.AddAnimation({"walk", 6, 0, 2, 130});
    m_registry.emplace<AnimationPlayerComponent>(enemy, animationPlayerEnemy);
    m_registry.emplace<TransformComponent>(enemy, glm::vec2{rendererWidth, 85.0f});
    m_registry.emplace<RigidBodyComponent>(enemy, glm::vec2{-70.0f, 0.0f}, false, true, true);
    SDL_Rect rectSrcEnemy = {.x = 0, .y = 0, .w = 41, .h = 49};
    SDL_FRect rectFSrcEnemy = {.x = 0, .y = 0, .w = 41, .h = 49};
    m_registry.emplace<SpriteComponent>(enemy, "enemy", rectSrcEnemy);
    m_registry.emplace<CollisionComponent>(enemy, rectFSrcEnemy);

    entt::entity ground = m_registry.create();
    m_registry.emplace<RigidBodyComponent>(ground, glm::vec2{0, 0}, true);
    SDL_FRect rectGround = {.x = 0, .y = 0, .w = maxBackgroundX, .h = maxBackgroundY};
    m_registry.emplace<CollisionComponent>(ground, rectGround);
    m_registry.emplace<TransformComponent>(ground, glm::vec2{-30.0f, 132.0f});

    entt::entity background = m_registry.create();
    m_assetStore->AddTexture("background", "./assets/gfx/stages/stage1.png");

    m_registry.emplace<TransformComponent>(background, glm::vec2{0.0f, 0.0f});
    SDL_Rect rectSrcBackground = {.x = 0, .y = 0, .w = maxBackgroundX, .h = maxBackgroundY};
    m_registry.emplace<SpriteComponent>(background, "background", rectSrcBackground);

    return true;
}

bool Scene::Update(float deltaTime) {
    for (const auto &system: m_systemsUpdate) {
        system->Update(m_registry, deltaTime);
    }

    return true;
}

bool Scene::Render() {
    for (const auto &system: m_systemsRender) {
        system->Update(m_registry, 0);
    }

    return true;
}
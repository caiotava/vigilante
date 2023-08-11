#include "AssetStore.h"

#include <SDL.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>

AssetStore::AssetStore(SDL_Renderer *renderer) : AssetStore() {
    m_renderer = renderer;
}

SDL_Texture *AssetStore::AddTexture(const std::string &assetID, const std::string &filePath) {
    auto texture = IMG_LoadTexture(m_renderer, filePath.c_str());

    if (texture == nullptr) {
        spdlog::error("error add texture - " + filePath + " :" + std::string(IMG_GetError()));
        return nullptr;
    }

    m_textures[assetID] = texture;
    return texture;
}

SDL_Texture *AssetStore::GetTexture(const std::string &assetID) {
    return m_textures[assetID];
}

bool AssetStore::Clear() {
    for (auto &[_, texture] : m_textures) {
        SDL_DestroyTexture(texture);
    }

    m_textures.clear();
    return true;
}
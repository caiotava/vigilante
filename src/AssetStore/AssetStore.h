#ifndef VIGILANTE_ASSETSTORE_H
#define VIGILANTE_ASSETSTORE_H

#include <map>
#include <string>

#include <SDL.h>

class AssetStore {
public:
    AssetStore() = default;
    AssetStore(SDL_Renderer *renderer);

    SDL_Texture *AddTexture(const std::string &assetID, const std::string &filePath);
    SDL_Texture *GetTexture(const std::string &assetID);

    bool Clear();

private:
    SDL_Renderer *m_renderer;

    std::map<std::string, SDL_Texture*> m_textures;
};

#endif //VIGILANTE_ASSETSTORE_H

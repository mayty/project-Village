#include "texture_manager.h"

std::unordered_map<std::string, SDL_Texture*> mns::texture_manager::textures;

SDL_Texture* mns::texture_manager::get_texture(const std::string& name)
{
    if (textures.find(name) == textures.end())
    {
        throw std::exception{};
    }
    return textures.at(name);
}

void mns::texture_manager::add_texture(const std::string& name, SDL_Texture* texture)
{
    if (textures.find(name) != textures.end())
    {
        throw std::exception{};
    }
    textures.insert_or_assign(name, texture);
}

void mns::texture_manager::remove_texture(const std::string& name)
{
    if (textures.find(name) == textures.end())
    {
        return;
    }
    SDL_DestroyTexture(textures.at(name));
    textures.erase(name);
}

void mns::texture_manager::clear()
{
    for (auto& i : textures)
    {
        SDL_DestroyTexture(i.second);
    }
    textures.clear();
}

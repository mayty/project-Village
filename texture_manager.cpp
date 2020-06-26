#include "texture_manager.h"
#include <SDL_image.h>

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

void mns::texture_manager::add_texture(const std::string& name, const std::string& filename, mns::window& window, mns::logger& logger)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface)
    {
        logger.log(mns::log_types::texture_loading, IMG_GetError());
        throw std::exception{};
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window.get_renderer(), surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        throw std::exception{};
    }
    add_texture(name, texture);
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

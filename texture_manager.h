#pragma once
#include <unordered_map>
#include <string>
#include <SDL.h>

namespace mns
{
	class texture_manager
	{
		static std::unordered_map<std::string, SDL_Texture*> textures;
	public:
		SDL_Texture* get_texture(const std::string& name);
		void add_texture(const std::string& name, SDL_Texture* texture);
		void remove_texture(const std::string& name);
		void clear();
	};
}


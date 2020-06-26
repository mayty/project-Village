#pragma once
#include <unordered_map>
#include <string>
#include <SDL.h>
#include "window.h"
#include "logger.h"

namespace mns
{
	class texture_manager
	{
		static std::unordered_map<std::string, SDL_Texture*> textures;
	public:
		static SDL_Texture* get_texture(const std::string& name);
		static void add_texture(const std::string& name, SDL_Texture* texture);
		static void add_texture(const std::string& name, const std::string& filename, mns::window& window, mns::logger& logger);
		static void remove_texture(const std::string& name);
		static void clear();
	};
}


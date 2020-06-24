#pragma once
#include <SDL.h>
#include <string>

namespace mns
{
	class window
	{
	private:
		SDL_Window* sdl_window;
		SDL_Renderer* sdl_renderer;
	public:
		window(const std::string& name, size_t w, size_t h);
		window(const window& other) = delete;
		window(window&& other);
		window& operator=(const window& other) = delete;
		window& operator=(window&& other);
		void update();
		void clear();
		void fill(uint8_t r, uint8_t g, uint8_t b);
		SDL_Window* get_window();
		SDL_Renderer* get_renderer();
		~window();
	private:
		void destroy();
	};
}

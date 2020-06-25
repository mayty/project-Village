#pragma once
#include <SDL.h>
#include <string>

namespace mns
{
	enum class events
	{
		other, none, quit, keyboard, mouse
	};
	class window
	{
	private:
		SDL_Scancode last_pressed;
		SDL_Window* sdl_window;
		SDL_Renderer* sdl_renderer;
	public:
		window(const std::string& name, size_t w, size_t h);
		window(const window& other) = delete;
		window(window&& other) noexcept;
		window& operator=(const window& other) = delete;
		window& operator=(window&& other) noexcept;
		void update();
		void clear();
		void fill(uint8_t r, uint8_t g, uint8_t b);
		SDL_Scancode get_last_press();
		SDL_Window* get_window();
		SDL_Renderer* get_renderer();
		events get_event();
		~window();
	private:
		void destroy();
	};
}

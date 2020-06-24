#include "window.h"

mns::window::window(const std::string& name, size_t w, size_t h)
{
	last_pressed = SDL_SCANCODE_ESCAPE;
	sdl_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
	if (!sdl_window)
	{
		throw std::exception{};
	}
	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (!sdl_renderer)
	{
		SDL_DestroyWindow(sdl_window);
		throw std::exception{};
	}
}

mns::window::window(window&& other)
{
	sdl_window = other.sdl_window;
	sdl_renderer = other.sdl_renderer;
	other.sdl_renderer = nullptr;
	other.sdl_window = nullptr;
}

mns::window& mns::window::operator=(window&& other)
{
	destroy();
	sdl_window = other.sdl_window;
	sdl_renderer = other.sdl_renderer;
	other.sdl_renderer = nullptr;
	other.sdl_window = nullptr;
	return *this;
}

void mns::window::update()
{
	SDL_RenderPresent(sdl_renderer);
}

void mns::window::clear()
{
	fill(0, 0, 0);
}

void mns::window::fill(uint8_t r, uint8_t g, uint8_t b)
{
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, 255);
	SDL_RenderClear(sdl_renderer);
}

SDL_Scancode mns::window::get_last_press()
{
	return last_pressed;
}

SDL_Window* mns::window::get_window()
{
	return sdl_window;
}

SDL_Renderer* mns::window::get_renderer()
{
	return sdl_renderer;
}

mns::events mns::window::get_event()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return events::quit;
		}
		if (event.type == SDL_KEYDOWN)
		{
			last_pressed = event.key.keysym.scancode;
			return events::keyboard;
		}
		return events::other;
	}
	return events::none;
}

mns::window::~window()
{
	destroy();
}

void mns::window::destroy()
{
	if (sdl_renderer)
	{
		SDL_DestroyRenderer(sdl_renderer);
		sdl_renderer = nullptr;
	}
	if (sdl_window)
	{
		SDL_DestroyWindow(sdl_window);
		sdl_window = nullptr;
	}
}

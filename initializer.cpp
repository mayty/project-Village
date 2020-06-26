#include "initializer.h"
#include <SDL_image.h>
#include <exception>

mns::initializer::initializer()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		throw std::exception{};
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Quit();
		throw std::exception{};
	}
}

mns::initializer::~initializer()
{
	IMG_Quit();
	SDL_Quit();	
}

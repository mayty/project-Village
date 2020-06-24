#include "initializer.h"
#include <exception>

mns::initializer::initializer()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		throw std::exception{};
	}
}

mns::initializer::initializer(uint32_t flags)
{
	if (SDL_Init(flags) < 0)
	{
		throw std::exception{};
	}
}

mns::initializer::~initializer()
{
	SDL_Quit();
}

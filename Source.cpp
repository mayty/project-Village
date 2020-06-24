#include <SDL.h>
#include <iostream>
#include "logger.h"
#include "window.h"
#include "initializer.h"

int main(int argC, char** argV)
{
	mns::logger logger{};

	try
	{
		logger.log("Initializing SDL2");
		mns::initializer initter{};
		logger.log("Success");

		logger.log("Creating window");
		mns::window window{ "test", 800, 600 };
		logger.log("Success");

		window.fill(255, 0, 0);
		window.update();

		SDL_Delay(5000);

	}
	catch (...)
	{
		logger.log("Unexpected error");
	}

	logger.log("Terminating");

	return 0;
}
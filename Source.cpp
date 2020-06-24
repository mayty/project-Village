#include <SDL.h>
#include <iostream>
#include "logger.h"
#include "window.h"
#include "initializer.h"
#include "field.h"

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

		mns::field field{ 160, 120, mns::generation_type::lakes };

		window.clear();
		field.draw(window);
		window.update();

		bool to_exit = false;
		while (!to_exit)
		{
			switch (window.get_event())
			{
			case mns::events::quit:
				to_exit = true;
				break;
			case mns::events::keyboard:
				switch (window.get_last_press())
				{
				case SDL_SCANCODE_1:
					field.generate_new(mns::generation_type::ground);
					break;
				case SDL_SCANCODE_2:
					field.generate_new(mns::generation_type::random);
					break;
				case SDL_SCANCODE_3:
					field.generate_new(mns::generation_type::small_lakes);
					break; 
				case SDL_SCANCODE_4:
					field.generate_new(mns::generation_type::lakes);
					break;
				case SDL_SCANCODE_5:
					field.generate_new(mns::generation_type::islands);
					break;
				case SDL_SCANCODE_ESCAPE:
					to_exit = true;
					break;
				}
				window.clear();
				field.draw(window);
				window.update();
				break;
			default:
				SDL_Delay(33);
			}
		}

	}
	catch (...)
	{
		logger.log("Unexpected error");
	}

	logger.log("Terminating");

	return 0;
}
#include <SDL.h>
#include <iostream>
#include "logger.h"
#include "window.h"
#include "initializer.h"
#include "field.h"
#include "entity.h"

int main(int argC, char** argV)
{
	mns::logger logger{mns::log_types::none};
	logger.set_mask_flag(mns::log_types::high);

	try
	{
		logger.log(mns::log_types::high, "Initializing SDL2");
		mns::initializer initter{};
		logger.log(mns::log_types::high, "Success");

		logger.log(mns::log_types::high, "Creating window");
		mns::window window{ "test", 800, 600 };
		logger.log(mns::log_types::high, "Success");

		mns::field field{ 160, 120, mns::generation_type::ground };

		window.clear();
		field.draw(window);
		window.update();

		bool to_exit = false;
		bool to_continue = false;
		while (!to_exit && !to_continue)
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
					logger.log("Generation world of ground");
					field.generate_new(mns::generation_type::ground);
					logger.log("Complete");
					break;
				case SDL_SCANCODE_2:
					logger.log("Generation world of random");
					field.generate_new(mns::generation_type::random);
					logger.log("Complete");
					break;
				case SDL_SCANCODE_3:
					logger.log("Generation world of small lakes");
					field.generate_new(mns::generation_type::small_lakes);
					logger.log("Complete");
					break; 
				case SDL_SCANCODE_4:
					logger.log("Generation world of islands type 1");
					field.generate_new(mns::generation_type::lakes);
					logger.log("Complete");
					break;
				case SDL_SCANCODE_5:
					logger.log("Generation world of islands type 2");
					field.generate_new(mns::generation_type::islands);
					logger.log("Complete");
					break;
				case SDL_SCANCODE_ESCAPE:
					to_exit = true;
					break;
				case SDL_SCANCODE_RETURN:
					to_continue = true;
					break;
				}
				window.clear();
				field.draw(window);
				window.update();
				{
					bool empty_queue = false;
					while (!empty_queue)
					{
						switch (window.get_event())
						{
						case mns::events::quit:
							to_exit = true;
							empty_queue = true;
							break;
						case mns::events::keyboard:
							if (window.get_last_press() == SDL_SCANCODE_RETURN)
							{
								to_continue = true;
								empty_queue = true;
							}
							break;
						case mns::events::none:
							empty_queue = true;
							break;
						}
					}
				}
				break;
			default:
				SDL_Delay(33);
			}
		}

		mns::entity test;

		while (!to_exit)
		{
			bool no_events = false;
			while (!no_events)
			{
				switch (window.get_event())
				{
				case mns::events::quit:
					to_exit = true;
					no_events = true;
					break;
				case mns::events::keyboard:
					if (window.get_last_press() == SDL_SCANCODE_ESCAPE)
					{
						to_exit = true;
						no_events = true;
					}
					break;
				case mns::events::none:
					no_events = true;
				}
			}
			test.update(field, logger);
			window.clear();
			field.draw(window);
			test.draw(window);
			window.update();
			logger.log(mns::log_types::low, "water: " + std::to_string(test.get_water()));
			logger.log(mns::log_types::low, "health: " + std::to_string(test.get_health()));
			//SDL_Delay(100);
		}

	}
	catch (...)
	{
		logger.log("Unexpected error");
	}

	logger.log("Terminating");

	return 0;
}
#include <SDL.h>
#include <iostream>
#include "logger.h"
#include "window.h"
#include "initializer.h"
#include "field.h"
#include "entity.h"
#include "texture_manager.h"

int main(int argC, char** argV)
{
	mns::logger logger{};
	//logger.set_mask_flag(mns::log_types::world_generation);
	//logger.set_mask_flag(mns::log_types::tile_modification);
	logger.set_mask_flag(mns::log_types::initialization);
	logger.set_mask_flag(mns::log_types::texture_loading);	
	//logger.set_mask_flag(mns::log_types::population_change);

	try
	{
		logger.log(mns::log_types::initialization, "Initializing SDL2");
		mns::initializer initializer{};
		logger.log(mns::log_types::initialization, "Done");


		logger.log(mns::log_types::initialization, "Creating window");
		mns::window window{ "test", 800, 600 };
		logger.log(mns::log_types::initialization, "Done");

		logger.log(mns::log_types::texture_loading, "loading \"entity_alive.png\" texture");
		mns::texture_manager::add_texture("entity_alive", "entity_alive.png", window, logger);
		logger.log(mns::log_types::texture_loading, "Done");


		logger.log(mns::log_types::texture_loading, "loading \"entity_dead.png\" texture");
		mns::texture_manager::add_texture("entity_dead", "entity_dead.png", window, logger);
		logger.log(mns::log_types::texture_loading, "Done");


		logger.log(mns::log_types::texture_loading, "loading \"default.png\" texture");
		mns::texture_manager::add_texture("default", "default.png", window, logger);
		logger.log(mns::log_types::texture_loading, "Done");


		mns::field field{ logger, 160, 120, mns::generation_type::ground };

		window.clear();
		field.draw(window);
		window.update();

		std::list<mns::entity> entities;

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
					logger.log(mns::log_types::population_change, "removing all entities");
					entities.clear();
					logger.log(mns::log_types::world_generation, "Generation world of ground");
					field.generate_new(mns::generation_type::ground);
					logger.log(mns::log_types::world_generation, "Done");
					break;
				case SDL_SCANCODE_2:
					logger.log(mns::log_types::population_change, "removing all entities");
					entities.clear();
					logger.log(mns::log_types::world_generation, "Generation world of random");
					field.generate_new(mns::generation_type::random);
					logger.log(mns::log_types::world_generation, "Done");
					break;
				case SDL_SCANCODE_3:
					logger.log(mns::log_types::population_change, "removing all entities");
					entities.clear();
					logger.log(mns::log_types::world_generation, "Generation world of small lakes");
					field.generate_new(mns::generation_type::small_lakes);
					logger.log(mns::log_types::world_generation, "Done");
					break;
				case SDL_SCANCODE_4:
					logger.log(mns::log_types::population_change, "removing all entities");
					entities.clear();
					logger.log(mns::log_types::world_generation, "Generation world of islands type 1");
					field.generate_new(mns::generation_type::lakes);
					logger.log(mns::log_types::world_generation, "Done");
					break;
				case SDL_SCANCODE_5:
					logger.log(mns::log_types::population_change, "removing all entities");
					entities.clear();
					logger.log(mns::log_types::world_generation, "Generation world of islands type 2");
					field.generate_new(mns::generation_type::islands);
					logger.log(mns::log_types::world_generation, "Done");
					break;
				case SDL_SCANCODE_ESCAPE:
					to_exit = true;
					break;
				}
				break;
			case mns::events::mouse:
			{
				auto pos = window.get_last_pos();
				logger.log(mns::log_types::population_change, "got mouse input " + std::to_string(pos.first) + ':' + std::to_string(pos.second));
				if (pos.first < 0 || pos.second < 0)
					break;
				if (pos.first >= window.width() || pos.second >= window.height())
					break;
				logger.log(mns::log_types::population_change, "adding entity");
				entities.push_back(mns::entity{ (double)pos.first, (double)pos.second });
				break;
			}
			case mns::events::none:
				window.clear();
				field.draw(window);
				for (auto& i : entities)
				{
					i.update(field, logger);
					i.draw(window);
				}
				window.update();
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
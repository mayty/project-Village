#pragma once
#include "drawable.h"
#include "logger.h"

namespace mns
{
	const int tile_quant = 25;
	enum class tile_types
	{
		ground, water, tree
	};
	class tile : public drawable
	{
		SDL_Rect base;
		tile_types type;
		int value;

		

	public:
		tile();
		void set_type(tile_types type);
		void set_pos(int x, int y);
		void set_size(int h, int w);
		void set_value(int value);
		tile_types get_type();
		int get_value();
		int dec_value(mns::logger& logger, int val);
		void draw(mns::window& window) override;
		~tile() override;
	private:
		void draw_tree(mns::window& window);
		void draw_ground(mns::window& window);
		void draw_water(mns::window& window);
	};
}


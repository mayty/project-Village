#pragma once
#include "drawable.h"

namespace mns
{
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
		tile_types get_type();
		void draw(mns::window& window) override;
		~tile() override;
	};
}


#include "tile.h"

mns::tile::tile()
{
	value = 0;
	type = tile_types::ground;
	base.x = 0;
	base.y = 0;
	base.h = 0;
	base.w = 0;
}

void mns::tile::set_type(tile_types type)
{
	this->type = type;
}

void mns::tile::set_pos(int x, int y)
{
	base.x = x;
	base.y = y;
}

void mns::tile::set_size(int h, int w)
{
	base.h = h;
	base.w = w;
}

void mns::tile::set_value(int value)
{
	this->value = value;
}

mns::tile_types mns::tile::get_type()
{
	return type;
}

int mns::tile::get_value()
{
	return value;
}

int mns::tile::dec_value(mns::logger& logger, int val)
{
	if (value >= val)
	{
		value -= val;
	}
	else
	{
		val = value;
		value = 0;
		type = mns::tile_types::ground;
		logger.log(mns::log_types::tile_modification, "turned tile to ground");
	}
	return val;
}

void mns::tile::draw(mns::window& window)
{
	switch (type)
	{
	case tile_types::ground:
		draw_ground(window);
		break;
	case tile_types::tree:
		draw_tree(window);
		break;
	case tile_types::water:
		draw_water(window);
		break;
	default:
		SDL_SetRenderDrawColor(window.get_renderer(), 255, 255, 255, 255);
		SDL_RenderFillRect(window.get_renderer(), &base);
	}
}

mns::tile::~tile()
{
}

static const int ground_r = 128;
static const int ground_g = 128;
static const int ground_b = 0;

void mns::tile::draw_tree(mns::window& window)
{
	double k = value / (9.0 * tile_quant);

	SDL_SetRenderDrawColor(window.get_renderer(), 0 * k + (1 - k) * ground_r, 200 * k + (1 - k) * ground_g, 0 * k + (1 - k) * ground_b, 255);
	SDL_RenderFillRect(window.get_renderer(), &base);
}

void mns::tile::draw_ground(mns::window& window)
{
	SDL_SetRenderDrawColor(window.get_renderer(), ground_r, ground_g, ground_b, 255);
	SDL_RenderFillRect(window.get_renderer(), &base);
}

void mns::tile::draw_water(mns::window& window)
{

	double k = value / (9.0 * tile_quant);
	SDL_SetRenderDrawColor(window.get_renderer(), 30 * k + (1 - k) * ground_r, 30 * k + (1 - k) * ground_g, 255 * k + (1 - k) * ground_b, 255);
	SDL_RenderFillRect(window.get_renderer(), &base);
}

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

mns::tile_types mns::tile::get_type()
{
	return type;
}

void mns::tile::draw(mns::window& window)
{
	switch (type)
	{
	case tile_types::ground:
		SDL_SetRenderDrawColor(window.get_renderer(), 128, 128, 0, 255);
		SDL_RenderFillRect(window.get_renderer(), &base);
		break;
	case tile_types::tree:
		SDL_SetRenderDrawColor(window.get_renderer(), 0, 200, 0, 255);
		SDL_RenderFillRect(window.get_renderer(), &base);
		break;
	case tile_types::water:
		SDL_SetRenderDrawColor(window.get_renderer(), 30, 30, 255, 255);
		SDL_RenderFillRect(window.get_renderer(), &base);
		break;
	default:
		SDL_SetRenderDrawColor(window.get_renderer(), 255, 255, 255, 255);
		SDL_RenderFillRect(window.get_renderer(), &base);
	}
}

mns::tile::~tile()
{
}

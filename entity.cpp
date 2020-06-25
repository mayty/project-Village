#include "entity.h"
#include <queue>
#include <unordered_set>

mns::entity::entity()
{
	speed = 0.5;
	x = 0;
	y = 0;
	water = 1.0;
	health = 1.0;
	is_dead = false;
}

void mns::entity::draw(mns::window& window)
{
	int entity_size = 5;
	SDL_Rect pos;
	pos.x = (int)x;
	pos.y = (int)y;
	pos.x -= entity_size / 2;
	pos.y -= entity_size / 2;
	pos.h = entity_size;
	pos.w = entity_size;
	if (!is_dead)
	{
		SDL_SetRenderDrawColor(window.get_renderer(), 255, 255, 255, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(window.get_renderer(), 0, 0, 0, 255);
	}
	SDL_RenderFillRect(window.get_renderer(), &pos);
}

void mns::entity::update(mns::field& field)
{
	/*if (is_dead)
	{
		return;
	}
	int p_x;
	int p_y;
	p_x = x / tile_size;
	p_y = y / tile_size;
	std::pair<int, int> dest;
	try
	{
		if (water < 0.5)
		{
			dest = get_closest_to(p_x, p_y, mns::tile_types::water, field);
			if (dest.X == p_x && dest.Y == p_y)
			{
				add(field.dec_value(p_x, p_y, 1));
				return;
			}
		}
		else
		{
			dest = get_closest_to(p_x, p_y, mns::tile_types::tree, field);
			if (dest.X == p_x && dest.Y == p_y)
			{
				field.dec_value(p_x, p_y, 1);
				return;
			}
		}
	}
	catch (...)
	{
		daily_toll();
		return;
	}

	if (dest.X > p_x)
	{
		x += tile_size * speed;
	}
	else if (dest.X < p_x)
	{
		x -= tile_size * speed;
	}

	if (dest.Y > p_y)
	{
		y += tile_size * speed;
	}
	else if (dest.Y < p_y)
	{
		y -= tile_size * speed;
	}
	daily_toll();*/
}

std::pair<int, int> mns::entity::get_closest_to(int x, int y, tile_types type, mns::field& field)
{
	/*std::queue<std::pair<int, int>> points;
	std::unordered_set<std::pair<int, int>> uniqie_points;
	points.push(std::make_pair(x, y));
	uniqie_points.insert(std::make_pair(x, y));
	while (!points.empty())
	{
		if (field.get_tile_type(points.front().X, points.front().Y) == type)
		{
			return points.front();
		}
		if (uniqie_points.find(std::make_pair(points.front().X + 1, points.front().Y)) != uniqie_points.end())
		{
			uniqie_points.insert(std::make_pair(points.front().X + 1, points.front().Y));
			points.push(std::make_pair(points.front().X + 1, points.front().Y));
		}
		if (uniqie_points.find(std::make_pair(points.front().X - 1, points.front().Y)) != uniqie_points.end())
		{
			uniqie_points.insert(std::make_pair(points.front().X - 1, points.front().Y));
			points.push(std::make_pair(points.front().X - 1, points.front().Y));
		}
		if (uniqie_points.find(std::make_pair(points.front().X, points.front().Y + 1)) != uniqie_points.end())
		{
			uniqie_points.insert(std::make_pair(points.front().X, points.front().Y + 1));
			points.push(std::make_pair(points.front().X, points.front().Y + 1));
		}
		if (uniqie_points.find(std::make_pair(points.front().X, points.front().Y - 1)) != uniqie_points.end())
		{
			uniqie_points.insert(std::make_pair(points.front().X, points.front().Y - 1));
			points.push(std::make_pair(points.front().X, points.front().Y - 1));
		}
		points.pop();
	}
	throw std::exception{};*/
	return std::make_pair(0, 0);
}

void mns::entity::daily_toll()
{
	if (water > 0)
	{
		water -= 0.01;
	}
	else if (health > 0)
	{
		health -= 0.01;
	}
	else
	{
		is_dead = true;
	}
}

void mns::entity::add(int val)
{
	if (water < 1)
	{
		water += val * 0.5;
	}
	if (water > 1)
	{
		water = 1;
	}
}

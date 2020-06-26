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

double mns::entity::get_water()
{
	return water;
}

double mns::entity::get_health()
{
	return health;
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

void mns::entity::update(mns::field& field, mns::logger& logger)
{
	if (is_dead)
	{
		logger.log(mns::log_types::entity_debug, "entity is dead");
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
			logger.log(mns::log_types::entity_debug, "looking for water");
			dest = get_closest_to(p_x, p_y, mns::tile_types::water, field);
			logger.log(mns::log_types::entity_debug, "found water: " + std::to_string(dest.first) + ':' + std::to_string(dest.second));
			if (dest.X == p_x && dest.Y == p_y)
			{
				logger.log(mns::log_types::entity_debug, "location matches current");
				add(field.dec_value(p_x, p_y, 1));
				daily_toll();
				return;
			}
		}
		else
		{
			logger.log(mns::log_types::entity_debug, "looking for trees");
			dest = get_closest_to(p_x, p_y, mns::tile_types::tree, field);
			logger.log(mns::log_types::entity_debug, "found trees: " + std::to_string(dest.first) + ':' + std::to_string(dest.second));
			if (dest.X == p_x && dest.Y == p_y)
			{
				logger.log(mns::log_types::entity_debug, "location matches current");
				field.dec_value(p_x, p_y, 1);
				daily_toll();
				return;
			}
		}
	}
	catch (...)
	{
		logger.log(mns::log_types::entity_debug, "failed to find destination");
		logger.log(mns::log_types::entity_debug, "decreasing stats");
		daily_toll();
		return;
	}

	if (dest.X > p_x)
	{
		logger.log(mns::log_types::entity_debug, "increasing x");
		x += tile_size * speed;
	}
	else if (dest.X < p_x)
	{
		logger.log(mns::log_types::entity_debug, "decreasing x");
		x -= tile_size * speed;
	}
	else
	{
		logger.log(mns::log_types::entity_debug, "x is fine");
	}

	if (dest.Y > p_y)
	{
		logger.log(mns::log_types::entity_debug, "increasing y");
		y += tile_size * speed;
	}
	else if (dest.Y < p_y)
	{
		logger.log(mns::log_types::entity_debug, "decreasing y");
		y -= tile_size * speed;
	}
	else
	{
		logger.log(mns::log_types::entity_debug, "y is fine");
	}
	logger.log(mns::log_types::entity_debug, "decreasing stats");
	daily_toll();
}

namespace std// inject std::hash specialization for std::pair<int, int>
{
	template<>
	struct hash<std::pair<int, int>>
	{
		size_t operator () (std::pair<int, int> const& p) const
		{
			return std::hash<long>()(((long)(p.first) << 16) | (long)(p.second));
		}
	};
}

std::pair<int, int> mns::entity::get_closest_to(int x, int y, tile_types type, mns::field& field)
{
#define X first
#define Y second
#define POINT first
#define ORIGIN second
	std::queue<std::pair<std::pair<int, int>, std::pair<int, int>>> points;
	std::unordered_set<std::pair<int, int>> uniqie_points;
	points.push(std::make_pair(std::make_pair(x, y), std::make_pair(x, y)));
	points.push(std::make_pair(std::make_pair(x + 1, y), std::make_pair(x + 1, y)));
	points.push(std::make_pair(std::make_pair(x - 1, y), std::make_pair(x - 1, y)));
	points.push(std::make_pair(std::make_pair(x, y + 1), std::make_pair(x, y + 1)));
	points.push(std::make_pair(std::make_pair(x, y - 1), std::make_pair(x, y - 1)));

	points.push(std::make_pair(std::make_pair(x + 1, y + 1), std::make_pair(x + 1, y + 1)));
	points.push(std::make_pair(std::make_pair(x + 1, y - 1), std::make_pair(x + 1, y - 1)));
	points.push(std::make_pair(std::make_pair(x - 1, y + 1), std::make_pair(x - 1, y + 1)));
	points.push(std::make_pair(std::make_pair(x - 1, y - 1), std::make_pair(x - 1, y - 1)));

	uniqie_points.insert(std::make_pair(x, y));
	uniqie_points.insert(std::make_pair(x + 1, y));
	uniqie_points.insert(std::make_pair(x - 1, y));
	uniqie_points.insert(std::make_pair(x, y + 1));
	uniqie_points.insert(std::make_pair(x, y - 1));
	uniqie_points.insert(std::make_pair(x + 1, y + 1));
	uniqie_points.insert(std::make_pair(x + 1, y - 1));
	uniqie_points.insert(std::make_pair(x - 1, y + 1));
	uniqie_points.insert(std::make_pair(x - 1, y - 1));
	while (!points.empty())
	{
		try
		{
			if (field.get_tile_type(points.front().POINT.X, points.front().POINT.Y) == type)
			{
				return points.front().ORIGIN;
			}
		}
		catch (...)
		{
			points.pop();
			continue;
		}
		if (field.get_tile_type(points.front().POINT.X, points.front().POINT.Y) == mns::tile_types::water)
		{
			points.pop();
			continue;
		}
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				if (uniqie_points.find(std::make_pair(points.front().POINT.X + i, points.front().POINT.Y + j)) == uniqie_points.end())
				{
					uniqie_points.insert(std::make_pair(points.front().POINT.X + i, points.front().POINT.Y + j));
					points.push(std::make_pair(std::make_pair(points.front().POINT.X + i, points.front().POINT.Y + j), points.front().ORIGIN));
				}
			}
		}
		points.pop();
	}
	throw std::exception{};
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

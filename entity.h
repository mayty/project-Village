#pragma once
#include "field.h"
#include "drawable.h"
#include "logger.h"

namespace mns
{
	class entity : public drawable
	{
	private:
		double x, y;
		double speed;
		double health;
		double water;
		bool is_dead;
	public:
		entity();
		entity(double x, double y);
		double get_water();
		double get_health();
		void draw(mns::window& window) override;
		void update(mns::field& field, mns::logger& logger);
	private:
#define X first
#define Y second
		std::pair<int, int> get_closest_to(int x, int y, tile_types type, mns::field& field);
		void daily_toll();
		void add(int val);
	};
}


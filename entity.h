#pragma once
#include "field.h"
#include "drawable.h"

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
		void draw(mns::window& window) override;
		void update(mns::field& field);
	private:
#define X first
#define Y second
		std::pair<int, int> get_closest_to(int x, int y, tile_types type, mns::field& field);
		void daily_toll();
		void add(int val);
	};
}


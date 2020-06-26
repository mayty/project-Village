#pragma once
#include "drawable.h"
#include "tile.h"
#include "logger.h"
#include <vector>

namespace mns
{
	enum class generation_type
	{
		ground, random, small_lakes, lakes, islands
	};

	const int tile_size = 5;

	class field : public drawable
	{
	private:
		template<class T>
		using matrix = std::vector<std::vector<T>>;
		
		mns::logger& logger;
		matrix<tile> tiles;

	public:
		field(mns::logger& logger, size_t w, size_t h, mns::generation_type generation_type);
		void generate_new(mns::generation_type generation_type);
		void draw(mns::window& window) override;
		int get_height();
		int get_widht();
		tile_types get_tile_type(int x, int y);
		int get_tile_value(int x, int y);
		int dec_value(int x, int y, int val);
		~field() override;
	private:
		void generate_ground();
		void generate_random();
		void generate_small_lakes();
		void generate_lakes();
		void generate_islands();
		void change_tile(matrix<tile>& matrix, int x, int y, tile_types type);
		void make_dry(matrix<tile>& matrix, int x, int y);
		tile_types get_tile(matrix<tile>& matrix, int x, int y, tile_types default_type);
		void group_tiles(matrix<tile>& matrix, tile_types to_group, tile_types to_replace, size_t inc_iters, size_t dec_iters, size_t threshold);
		void change_from_to(matrix<tile>& matrix, int x, int y, tile_types from, tile_types to);
		void normilize(tile_types type);
	};
}


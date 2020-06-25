#include "field.h"
#include <random>
#include <unordered_map>

static std::vector<mns::tile_types> get_probability_vector(const std::unordered_map<mns::tile_types, int>& probabilities_map);

mns::field::field(size_t w, size_t h, mns::generation_type generation_type)
{
	tiles.resize(h);
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i].resize(w);
		for (int j = 0; j < tiles[i].size(); ++j)
		{
			tiles[i][j].set_pos(j * tile_size, i * tile_size);
			tiles[i][j].set_size(tile_size, tile_size);
		}
	}
	switch (generation_type)
	{
	case generation_type::ground:
		generate_ground();
		break;
	case generation_type::random:
		generate_random();
		break;
	case generation_type::small_lakes:
		generate_small_lakes();
		break;
	case generation_type::lakes:
		generate_lakes();
		break;
	}
	normilize(mns::tile_types::tree);
	normilize(mns::tile_types::water);
}

void mns::field::generate_new(mns::generation_type generation_type)
{
	switch (generation_type)
	{
	case generation_type::ground:
		generate_ground();
		break;
	case generation_type::random:
		generate_random();
		break;
	case generation_type::small_lakes:
		generate_small_lakes();
		break;
	case generation_type::lakes:
		generate_lakes();
		break;
	case generation_type::islands:
		generate_islands();
		break;
	}
	normilize(mns::tile_types::tree);
	normilize(mns::tile_types::water);
}

void mns::field::draw(mns::window& window)
{
	for (auto& i : tiles)
	{
		for (auto& j : i)
		{
			j.draw(window);
		}
	}
}

int mns::field::get_height()
{
	return tiles.size();
}

int mns::field::get_widht()
{
	return tiles[0].size();
}

mns::tile_types mns::field::get_tile_type(int x, int y)
{
	if (x < 0 || y < 0)
	{
		throw std::exception{};
	}
	if (y >= tiles.size())
	{
		throw std::exception{};
	}
	if (x >= tiles[y].size())
	{
		throw std::exception{};
	}
	return tiles[y][x].get_type();
}

int mns::field::get_tile_value(int x, int y)
{
	if (x < 0 || y < 0)
	{
		throw std::exception{};
	}
	if (y >= tiles.size())
	{
		throw std::exception{};
	}
	if (x >= tiles[y].size())
	{
		throw std::exception{};
	}
	return tiles[y][x].get_value();
}

int mns::field::dec_value(int x, int y, int val)
{
	if (x < 0 || y < 0)
	{
		throw std::exception{};
	}
	if (y >= tiles.size())
	{
		throw std::exception{};
	}
	if (x >= tiles[y].size())
	{
		throw std::exception{};
	}
	return tiles[y][x].dec_value(val);
}

mns::field::~field()
{
}

void mns::field::generate_ground()
{
	for (auto& i : tiles)
	{
		for (auto& j : i)
		{
			j.set_type(tile_types::ground);
		}
	}
}

void mns::field::generate_random()
{
	std::random_device rd{};
	std::mt19937 random{ rd() };
	std::unordered_map<mns::tile_types, int> probabilities_map;
	probabilities_map.insert_or_assign(mns::tile_types::water, 1);
	probabilities_map.insert_or_assign(mns::tile_types::ground, 3);
	probabilities_map.insert_or_assign(mns::tile_types::tree, 2);
	std::vector<tile_types> probabilities = get_probability_vector(probabilities_map);
	for (auto& i : tiles)
	{
		for (auto& j : i)
		{
			j.set_type(probabilities[random() % probabilities.size()]);
		}
	}
}

void mns::field::generate_small_lakes()
{
	generate_random();

	group_tiles(tiles, mns::tile_types::water, mns::tile_types::ground, 3, 6, 7);
	group_tiles(tiles, mns::tile_types::tree, mns::tile_types::ground, 3, 3, 8);
}

void mns::field::generate_lakes()
{
	generate_random();

	group_tiles(tiles, mns::tile_types::water, mns::tile_types::ground, 3, 8, 7);
	group_tiles(tiles, mns::tile_types::water, mns::tile_types::ground, 7, 5, 7);
	group_tiles(tiles, mns::tile_types::tree, mns::tile_types::ground, 4, 3, 9);
}

void mns::field::generate_islands()
{
	generate_random();

	group_tiles(tiles, mns::tile_types::tree, mns::tile_types::ground, 2, 3, 8);
	group_tiles(tiles, mns::tile_types::water, mns::tile_types::ground, 3, 6, 7);
	group_tiles(tiles, mns::tile_types::water, mns::tile_types::ground, 7, 4, 7);

	//group_tiles(tiles, mns::tile_types::tree, mns::tile_types::ground, 2, 3, 8);
	//group_tiles(tiles, mns::tile_types::water, mns::tile_types::ground, 3, 8, 6);
}

void mns::field::change_tile(matrix<tile>& matrix, int x, int y, tile_types type)
{
	if (x < 0 || y < 0)
	{
		return;
	}
	if (y >= matrix.size())
	{
		return;
	}
	if (x >= matrix[y].size())
	{
		return;
	}
	matrix[y][x].set_type(type);
}

void mns::field::make_dry(matrix<tile>& matrix, int x, int y)
{
	if (x < 0 || y < 0)
	{
		return;
	}
	if (y >= matrix.size())
	{
		return;
	}
	if (x >= matrix[y].size())
	{
		return;
	}
	if (matrix[y][x].get_type() == mns::tile_types::water)
	{
		matrix[y][x].set_type(mns::tile_types::ground);
	}
}

mns::tile_types mns::field::get_tile(matrix<tile>& matrix, int x, int y, tile_types default_type)
{
	if (x < 0 || y < 0)
	{
		return default_type;
	}
	if (y >= matrix.size())
	{
		return default_type;
	}
	if (x >= matrix[y].size())
	{
		return default_type;
	}
	return matrix[y][x].get_type();
}

void mns::field::group_tiles(matrix<tile>& matrix, tile_types to_group, tile_types to_replace, size_t inc_iters, size_t dec_iters, size_t threshold)
{
	field::matrix<tile> a = matrix;
	field::matrix<tile> b = matrix;


	for (int k = 0; k < inc_iters; ++k)
	{
		a = b;
		for (int i = 0; i < a.size(); ++i)
		{
			for (int j = 0; j < a[i].size(); ++j)
			{
				if (a[i][j].get_type() == to_group)
				{
					change_tile(b, j - 1, i, to_group);
					change_tile(b, j, i - 1, to_group);
					change_tile(b, j + 1, i, to_group);
					change_tile(b, j, i + 1, to_group);
				}
			}
		}
	}

	b = a;

	for (int k = 0; k < dec_iters; ++k)
	{
		b = a;
		for (int i = 0; i < a.size(); ++i)
		{
			for (int j = 0; j < a[i].size(); ++j)
			{
				if (get_tile(b, j, i, to_group) != to_group)
				{
					continue;
				}

				int counter = 0;
				for (int y = -1; y <= 1; ++y)
				{
					for (int x = -1; x <= 1; ++x)
					{
						if (get_tile(b, j + x, i + y, to_group) == to_group)
						{
							++counter;
						}
					}
				}

				if (counter >= threshold)
				{
					change_tile(a, j, i, to_group);
				}
				else
				{
					change_from_to(a, j, i, to_group, to_replace);
				}
			}
		}
	}

	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = 0; j < a[i].size(); ++j)
		{
			if (a[i][j].get_type() == to_group)
			{
				change_tile(matrix, j, i, to_group);
			}
			else
			{
				change_from_to(matrix, j, i, to_group, to_replace);
			}
		}
	}
}

void mns::field::change_from_to(matrix<tile>& matrix, int x, int y, tile_types from, tile_types to)
{
	if (x < 0 || y < 0)
	{
		return;
	}
	if (y >= matrix.size())
	{
		return;
	}
	if (x >= matrix[y].size())
	{
		return;
	}
	if (matrix[y][x].get_type() == from)
	{
		matrix[y][x].set_type(to);
	}
}

void mns::field::normilize(tile_types type)
{
	for (int i = 0; i < tiles.size(); ++i)
	{
		for (int j = 0; j < tiles[i].size(); ++j)
		{
			if (get_tile(tiles, j, i, type) != type)
			{
				continue;
			}
			int counter = 0;
			for (int y = -1; y <= 1; ++y)
			{
				for (int x = -1; x <= 1; ++x)
				{
					if (get_tile(tiles, j + x, i + y, type) == type)
					{
						++counter;
					}
				}
			}
			tiles[i][j].set_value(tile_quant * counter);
		}
	}
}

std::vector<mns::tile_types> get_probability_vector(const std::unordered_map<mns::tile_types, int>& probabilities_map)
{
	std::vector<mns::tile_types> result;
	for (auto& i : probabilities_map)
	{
		for (int j = 0; j < i.second; ++j)
		{
			result.push_back(i.first);
		}
	}
	return result;
}

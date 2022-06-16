// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "house.h"
#include "world.h"

House::House() : _floor(Cube::type::plank, 136, 180.5, 9, 9, 10, 0.2)
{
	_pillars[0] = std::make_unique<Cube>(Cube::type::wood, 132, 176, 12, 0.4, 0.4, 8);
	_pillars[1] = std::make_unique<Cube>(Cube::type::wood, 140, 185, 12, 0.4, 0.4, 8);
	_pillars[2] = std::make_unique<Cube>(Cube::type::wood, 132, 185, 12, 0.4, 0.4, 8);
	_pillars[3] = std::make_unique<Cube>(Cube::type::wood, 140, 176, 12, 0.4, 0.4, 8);

	_walls[0] = std::make_unique<Cube>(Cube::type::plank2, 140, 180.5, 12, 0.2, 9, 6);
	_walls[1] = std::make_unique<Cube>(Cube::type::plank2, 135.9, 185, 12, 7.9, 0.2, 6);
}

void House::create(World& world)
{
	for(int i = 0; i < _pillars.size(); i++)
		_pillars[i]->create(world);
	for(int i = 0; i < _walls.size(); i++)
		_walls[i]->create(world);
	_floor.create(world);

	for(int x = 132; x < 141; x++)
		for(int y = 176; y < 186; y++)
			world.set_block(x, y, 9, 1);
}

void House::render()
{
	for(int i = 0; i < _pillars.size(); i++)
		_pillars[i]->render();
	for(int i = 0; i < _walls.size(); i++)
		_walls[i]->render();
	_floor.render();
}

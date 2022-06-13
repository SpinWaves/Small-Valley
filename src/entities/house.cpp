// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "house.h"

House::House()
{
	_pillars[0] = std::make_unique<Cube>(Cube::type::wood, 130, 150, 25, 0.4, 0.4, 8);
	_pillars[1] = std::make_unique<Cube>(Cube::type::wood, 137, 157, 25, 0.4, 0.4, 8);
	_pillars[2] = std::make_unique<Cube>(Cube::type::wood, 130, 157, 25, 0.4, 0.4, 8);
	_pillars[3] = std::make_unique<Cube>(Cube::type::wood, 137, 150, 25, 0.4, 0.4, 8);
}

void House::create(class World& world)
{
	for(int i = 0; i < _pillars.size(); i++)
		_pillars[i]->create(world);
}

void House::render()
{
	for(int i = 0; i < _pillars.size(); i++)
		_pillars[i]->render();
}

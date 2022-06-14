// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __HOUSE__
#define __HOUSE__

#include <pch.h>
#include "cube.h"

class House
{
	public:
		House();

		void create(class World& world);
		void render();

		~House() = default;

	private:
		std::array<std::unique_ptr<Cube>, 4> _pillars;
		std::array<std::unique_ptr<Cube>, 2> _walls;
		Cube _floor;
};

#endif // __HOUSE__

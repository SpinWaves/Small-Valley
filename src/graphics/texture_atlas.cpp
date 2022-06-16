// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "texture_atlas.h"

static const char* paths[] = {
	RES_DIR"assets/grass.jpg",
	RES_DIR"assets/wood_plank.jpg",
	RES_DIR"assets/wood.png",
	RES_DIR"assets/plank2.jpg",
};

void TextureAtlas::init()
{
	for(size_t i = 0; i < ARRAY_SIZE(paths); i++)
		_atlas.emplace_back(new Texture(paths[i]));
}

void TextureAtlas::free()
{
	for(auto texture : _atlas)
		texture->free_texture();
}

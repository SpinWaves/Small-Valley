// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __TEXTURE_ATLAS__
#define __TEXTURE_ATLAS__

#include "textures.h"

#define GRASS_TEXTURE 		0
#define WOOD_PLANK_TEXTURE  1
#define WOOD_PLANK_TEXTURE2 3
#define WOOD_TEXTURE 		2

class TextureAtlas
{
	public:
		TextureAtlas() = delete;

		static void init();
		static void free();

		inline static void bind(size_t index) noexcept { _atlas[index]->bind_texture(); }

		~TextureAtlas() = delete;

	private:
		inline static std::vector<std::shared_ptr<Texture>> _atlas;
};

#endif // __TEXTURE_ATLAS__

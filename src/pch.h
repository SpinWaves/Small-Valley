// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __PCH__
#define __PCH__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <GL/glew.h>

#include <Kernel/sysout.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <array>
#include <thread>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include <initializer_list>

#include <cmath>
#include <ctime>
#include <cstddef>
#include <cstdint>

#ifndef M_PI
    #define M_PI 3.141592653589793
#endif

#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])

#endif // __PCH__

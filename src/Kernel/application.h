// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __APPLICATION__
#define __APPLICATION__

#include <pch.h>
#include <io/inputs.h>
#include <graphics/shaders.h>
#include <graphics/camera.h>
#include <entities/world.h>
#include <entities/cube.h>
#include <graphics/textures.h>

class Application
{
    public:
        Application();

        void init(const char* name);
        void update(const Input& in);
        void destroy();

        ~Application();

    private:
        SDL_Window* _win = nullptr;
        SDL_GLContext _context;

        bool _wireline = false;

        Shader _shader;
        Camera3D _camera;
        std::shared_ptr<World> _world;
        Cube _cube;
};

#endif // __APPLICATION__

// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "application.h"
#include <graphics/matrixes.h>

Application::Application() : _shader(), _camera(), _cube() {}

void Application::init(const char* name)
{
    _win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!_win)
    {
        SDL_Quit();
        log::report(log_type::fatal_error, "unable to create the window");
    }

    _context = SDL_GL_CreateContext(_win);
    if(!_context)
    {
        SDL_DestroyWindow(_win);
        SDL_Quit();
        log::report(log_type::fatal_error, "unable to create OpenGL context");
    }
    SDL_GL_MakeCurrent(_win, _context);

    GLuint GLEWerr = glewInit();
    if(GLEW_OK != GLEWerr)
    {
        SDL_DestroyWindow(_win);
        SDL_Quit();
        log::report(log_type::fatal_error, "unable to init GLEW");
    }

    _shader.create(MAIN_DIR"src/graphics/shaders/main_3D.vert", MAIN_DIR"src/graphics/shaders/main_3D.frag");
    _shader.bindShader();

    _camera.setPosition(-2, -2, 2);

    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

    _world = World::create();
    _cube.create(0, 0, 0);
}

void Application::update(const Input& in)
{
    SDL_GL_SetSwapInterval(1);

    _camera.onEvent(in);
    _camera.look();

    Matrixes::matrix_mode(matrix::proj);
    Matrixes::perspective(90, (float)1280/720, 0.01, 100);

    Matrixes::matrix_mode(matrix::model);
    Matrixes::load_identity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.49f, 0.66f, 0.85f, 1.0f);

    _world->render();
    
    SDL_GL_SwapWindow(_win);
}

void Application::destroy()
{
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_win);
    _win = nullptr;
}

Application::~Application()
{
    if(_win != nullptr)
        destroy();
}

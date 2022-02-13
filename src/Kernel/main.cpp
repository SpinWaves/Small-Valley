// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <pch.h>
#include "application.h"
#include <io/inputs.h>

int main(int argc, char** argv)
{
    srand(time(NULL)); // init randomizer system

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    Input in;

    log::report(log_type::message, "Loading...");
    
    Application app;
    app.init("Small Valley");

    log::report(log_type::message, "Loading finished !");

    while(!in.isEnded())
    {
        in.update();
        if(in.getInKey(SDL_SCANCODE_ESCAPE))
            in.finish();
        app.update(in);
    }

    app.destroy();
    SDL_Quit();

    log::report(log_type::message, "End of program");

    return 0;
}

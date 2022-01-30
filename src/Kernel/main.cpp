#include <pch.h>
#include "application.h"
#include <io/inputs.h>

int main(int argc, char** argv)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    Input in;

    Application app;
    app.init("World");

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

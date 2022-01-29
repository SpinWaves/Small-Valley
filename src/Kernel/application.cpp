#include "application.h"
#include <graphics/matrixes.h>

void Application::init(const char* name)
{
    _win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!_win)
    {
        SDL_Quit();
        log::report(log_type::fatal_error, "Unable to create the window");
    }

    _context = SDL_GL_CreateContext(_win);
    if(!_context)
    {
        SDL_DestroyWindow(_win);
        SDL_Quit();
        log::report(log_type::fatal_error, "Unable to create OpenGL context");
    }
    SDL_GL_MakeCurrent(_win, _context);

    GLuint GLEWerr = glewInit();
    if(GLEW_OK != GLEWerr)
    {
        SDL_DestroyWindow(_win);
        SDL_Quit();
        log::report(log_type::fatal_error, "Unable to init GLEW");
    }
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    _shader = new Shader(MAIN_DIR"src/graphics/shaders/main_3D.vert", MAIN_DIR"src/graphics/shaders/main_3D.frag");
    _camera = new Camera3D();
    _camera->setPosition(1, 1, 1);
}

void Application::update(const Input& in)
{
    SDL_GL_SetSwapInterval(0);

    _camera->update();
    _camera->onEvent(in);
    _camera->look();

    Matrixes::matrix_mode(matrix::proj);
    Matrixes::perspective(90, (float)1280/720, 0.01, 100);

    Matrixes::matrix_mode(matrix::model);
    Matrixes::load_identity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.49f, 0.66f, 0.85f, 1.0f);

    _shader->bindShader();
    _shader->setMat4("view", Matrixes::get_matrix(matrix::view));
    _shader->setMat4("proj", Matrixes::get_matrix(matrix::proj));
    _shader->setMat4("model", Matrixes::get_matrix(matrix::model));

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    SDL_GL_SwapWindow(_win);

    _shader->unbindShader();
}

void Application::destroy()
{
    if(glIsBuffer(VBO))
        glDeleteBuffers(1, &VBO);
    
    delete _shader;
    delete _camera;
    
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_win);
    _win = nullptr;
}

Application::~Application()
{
    if(_win != nullptr)
        destroy();
}

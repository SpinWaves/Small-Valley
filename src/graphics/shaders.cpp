// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "shaders.h"

void Shader::create(const char* vertexFile, const char* fragmentFile)
{
    log::report(log_type::message, "Loading shader...");

    program = glCreateProgram();

    if(!program)
        log::report(log_type::fatal_error, "Unable to create a shader's program");

    createShader(LoadSourceShader(vertexFile), GL_VERTEX_SHADER);
    createShader(LoadSourceShader(fragmentFile), GL_FRAGMENT_SHADER);

    glLinkProgram(program);
    glValidateProgram(program);

    log::report(log_type::message, "Shader loaded");
}

void Shader::bindShader()
{
    glUseProgram(program);
}

void Shader::unbindShader()
{
    glUseProgram(0);
}

bool Shader::isBinded()
{
    int current = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current);
    return current == program ? true : false;
} 

void Shader::setFloat(const std::string &name, float v)
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), v);
}

void Shader::setVec3(const std::string &name, Vec3<float> v)
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), v.X, v.Y, v.Z);
}

void Shader::setVec2(const std::string &name, Vec2<float> v)
{
    glUniform2f(glGetUniformLocation(program, name.c_str()), v.X, v.Y);
}

void Shader::setVec3(const std::string &name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
}

void Shader::setVec2(const std::string &name, float x, float y)
{
    glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
}

void Shader::setInt(const std::string &name, int v)
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), v);
}

void Shader::setBool(const std::string &name, bool v)
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), v);
}

void Shader::setVec4(const std::string &name, Vec4<float> v)
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), v.X, v.Y, v.Z, v.W);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float t)
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, t);
}
void Shader::setMat4(const std::string &name, glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}


char* Shader::LoadSourceShader(const char* filename)
{
    char *src = NULL;
    FILE *fp = NULL;
    long long SIZE;
    long i;
    _filename = filename;

    log::report(log_type::message, "Loading shader's code...");

    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        log::report(log_type::error, "Unable to open a shader's code");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    SIZE = ftell(fp);

    rewind(fp);

    src = new char[SIZE + 1];
    if(src == NULL)
    {
        fclose(fp);
        log::report(log_type::error, "memory allocation error while creating a shader");
        return NULL;
    }

    for(i = 0; i < SIZE; i++)
        src[i] = fgetc(fp);

    src[SIZE] = '\0';

    fclose(fp);
    log::report(log_type::message, "Shader's code loaded");
    return src;
}

void Shader::createShader(const char* source, int type)
{
    shader = glCreateShader(type);

    if(!shader)
    {
        log::report(log_type::error, "Unable to create a shader");
        return;
    }

    if(type == 35633 && shader)
        log::report(log_type::message, "Compiling vertex shader...");
    if(type == 35632 && shader)
        log::report(log_type::message, "Compiling fragment shader...");

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint shader_compiled = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);

    if(shader_compiled == GL_FALSE)
    {
        GLsizei logsize = 0;
        char *log = NULL;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);

        log = new char[logsize + 1];
        if(!log)
        {
            log::report(log_type::error, "memory allocation error for a shader error");
            glDeleteShader(shader);
            return;
        }

        memset(log, '\0', logsize + 1);

        glGetShaderInfoLog(shader, logsize, &logsize, log);

        std::cout << std::endl;
        log::report(log_type::error, "something went wrong while compiling the shader : %s", _filename);
        log::report(log_type::error, log);

        delete[] log;

        glDeleteShader(shader);

        return;
    }

    log::report(log_type::message, "Shader compiled");

    glAttachShader(program, shader);
}

Shader::~Shader()
{
    if(shader)
        glDeleteShader(shader);
    if(program)
        glDeleteProgram(program);

    unbindShader();
}

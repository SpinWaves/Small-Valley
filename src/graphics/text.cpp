// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "text.h"
/*
Text::Text(TTF_Font* font, color_text color)
{
    if(!TTF_WasInit() && TTF_Init() == -1)
        sdl::MessageBox::reportMessage(ERROR, "Problème lors de l'initialisation de la librairie textuelle", SDL_GetError());

    _font = font;

    if(!_font)
        sdl::MessageBox::reportMessage(ERROR, "Problème lors de l'initialisation d'une police d'écriture", SDL_GetError());

    _noir = {0, 0, 0};
    _blanc = {255, 255, 255};

    switch(color)
    {
        case color_text::black: _color = {0, 0, 0}; break;
        case color_text::white: _color = {255, 255, 255}; break;

        default: break;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Text::Text(const char* path, size_t size, color_text color)
{
    _font = TTF_OpenFont(chemin, size);

    if(!_font)
        sdl::MessageBox::reportMessage(ERROR, "Problème lors de la passation d'une police d'écriture", SDL_GetError());

    switch(color)
    {
        case color_text::black: _color = {0, 0, 0}; break;
        case color_text::white: _color = {255, 255, 255}; break;

        default: break;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Text::init(std::string text)
{
    free_texture();

    std::string save = text;
    size_t found = text.find("\n");

    _lines.clear();
    _surf_hei.clear();
    _surf_wid.clear();

    int count = 0;

    if(found == std::string::npos)
        _lines.push_back(generateTexture(text.c_str()));
    else
    {
        while(found != std::string::npos)
        {
            count++;
            found = text.find("\n", found + 1);
        }
        found = text.find("\n");
        text.erase(found, text.size());
        _lines.push_back(generateTexture(text.c_str()));
        for(int i = 0; i < count; i++)
        {
            text.clear();
            if(i < count-1)
                text.append(save.begin() + found + newline.length(), save.begin() + save.find("\n", found + 1));
            else
                text.append(save.begin() + found + newline.length(), save.end());
            found = save.find("\n", found + 1);
            add_line(text.c_str());
        }
    }
    float coords_texture[8] = {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };

    //  v1-------v2
    //  |        |
    //  |        |
    //  |        |
    //  |        |
    //  v4-------v3

    std::vector<float> mesh;

    for(int i = 0; i < _lines.size(); i++)
    {
        switch(alignment)
        {
            case align::right:
                if(i > 0)
                    x += _surf_wid[i - 1] - _surf_wid[i];
            break;
            case align::center:
                if(i > 0)
                    x += (_surf_wid[i - 1] - _surf_wid[i])/2;
            break;
            case align::left: break;

            default: break;
        }

        if(_lines.size() > 1)
            y += TTF_FontLineSkip(_font);

        mesh.push_back(x);
        mesh.push_back(y + _surf_hei[i]);

        mesh.push_back(x);
        mesh.push_back(y);

        mesh.push_back(x + _surf_wid[i]);
        mesh.push_back(y);


        mesh.push_back(x);
        mesh.push_back(y + _surf_hei[i]);

        mesh.push_back(x + _surf_wid[i]);
        mesh.push_back(y);

        mesh.push_back(x + _surf_wid[i]);
        mesh.push_back(y + _surf_hei[i]);
    }
    _vertex_count = mesh.size();

    glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1, &_vbo);

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords_texture) + _vertex_count, * sizeof(float) 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, _vertex_count * sizeof(float), &mesh[0]);
    glBufferSubData(GL_ARRAY_BUFFER, _vertex_count * sizeof(float), sizeof(coords_texture), coords_texture);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(_vertex_count * sizeof(float)));

	glEnableVertexAttribArray(0); // vertices
    glEnableVertexAttribArray(1); // texture coords

    if(glIsBuffer(_vbo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Buffer Object (VBO) for a text");
    if(glIsVertexArray(_vao) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Array Object (VAO) for a text");
    
    glBindVertexArray(0);
}

void Text::add_line(const char* text)
{
    SDL_Surface* text_surf = TTF_RenderUTF8_Blended(_font, text, _color);

    if(!text_surf)
    {   
        log::report(log_type::error, "Text: unable to generate a surface");
        return 0;
    }

    GLuint texture;

    // Use texture array

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf_wid.back(), surf_hei.back(), 0, GL_RGBA, GL_UNSIGNED_BYTE, text_surf->pixels);

    SDL_FreeSurface(text_surf);

    if(!_texture)
    {
        log::report(log_type::error, "Text: unable to generate a texture");
        return 0;
    }
    return texture;
}

void Text::free_texture()
{
    if(!_lines.empty())
    {
        for(int i = 0; i < _lines.size(); i++)
            glDeleteTextures(1, &_lines[i]);
    }
}

void Text::render(int x, int y, align alignment)
{
    glBindTexture(GL_TEXTURE_2D, _lines[i]);

    glBindVertexArray(_vao);

    glDrawArrays(GL_TRIANGLES, 0, _vertex_count);
    
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Text::~Text()
{
    free_texture();
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    
    if(!TTF_WasInit()) return;

    if(_font && _is_local_font)
        TTF_CloseFont(_font);
    _font = nullptr;
}
*/
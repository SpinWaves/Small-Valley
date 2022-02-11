// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "matrixes.h"

void Matrixes::perspective(float FOV, float aspect, float near, float far)
{
    _proj = glm::perspective<float>(glm::radians(FOV), aspect, near, far);
}

void Matrixes::ortho(float left, float right, float top, float bottom)
{
    _proj = glm::ortho<float>(left, right, bottom, top);
}

void Matrixes::matrix_mode(matrix type)
{
    active_matrix = type;
}

glm::mat4 Matrixes::get_matrix(matrix type)
{
    switch(type)
    {
        case matrix::proj:  return _proj;
        case matrix::model: return _model;
        case matrix::view:  return _view;

        default: break;
    }
    return glm::mat4(0.0f);
}

glm::mat4 Matrixes::get_current_matrix()
{
    switch(active_matrix)
    {
        case matrix::proj:  return _proj;
        case matrix::model: return _model;
        case matrix::view:  return _view;

        default: break;
    }
    return glm::mat4(0.0f);
}

void Matrixes::lookAt(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z)
{
    _view = glm::lookAt(glm::vec3(pos_x, pos_y, pos_z), glm::vec3(target_x, target_y, target_z), glm::vec3(up_x, up_y, up_z));
}

void Matrixes::load_identity()
{
    switch(active_matrix)
    {
        case matrix::proj:  _proj  = glm::mat4(1.0f); break;
        case matrix::model: _model = glm::mat4(1.0f); break;
        case matrix::view:  _view  = glm::mat4(1.0f); break;

        default: break;
    }
}

void Matrixes::translate3D(double x, double y, double z)
{
    _model = glm::translate(_model, glm::vec3(x, y, z));
}

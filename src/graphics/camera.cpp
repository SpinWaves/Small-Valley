// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "matrixes.h"
#include "camera.h"
#include <maths/maths.h>

Camera3D::Camera3D() : _up(0, 0, 1)
{
	_position.SET(0, 0, 0);
	update_view();
}

void Camera3D::onEvent(const Input& input, World& world)
{
	if(_isMouseGrabed)
	{
		_theta -= input.getXRel() * _sensivity;
		_phi -= input.getYRel() * _sensivity;
		update_view();
	}

	if(input.getInKey(SDL_SCANCODE_F1, action::up))
	{
		_isMouseGrabed = _isMouseGrabed ? false : true;
		SDL_SetRelativeMouseMode(_isMouseGrabed ? SDL_TRUE : SDL_FALSE);
	}
	if(!_isMouseGrabed && input.getInMouse(1))
	{
		_isMouseGrabed = true;
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	
	_mov.SET(0.0, 0.0, 0.0);

	if(input.getInKey(SDL_SCANCODE_F, action::up))
		_free = _free ? false : true;

	_speed = _free ? 0.3f : 0.1f;

	if(input.getInKey(SDL_SCANCODE_Q))
		_speed = _free ? 0.5f : 0.15f;
	if(input.getInKey(SDL_SCANCODE_W) || input.getInKey(SDL_SCANCODE_UP))
		_mov -= _forward;
	if(input.getInKey(SDL_SCANCODE_S) || input.getInKey(SDL_SCANCODE_DOWN))
		_mov += _forward;
	if(input.getInKey(SDL_SCANCODE_A) || input.getInKey(SDL_SCANCODE_LEFT))
		_mov += _left;
	if(input.getInKey(SDL_SCANCODE_D) || input.getInKey(SDL_SCANCODE_RIGHT))
		_mov -= _left;
	if((input.getInKey(SDL_SCANCODE_LSHIFT) || input.getInKey(SDL_SCANCODE_RSHIFT)) && _free)
		_mov -= _up;
	if(input.getInKey(SDL_SCANCODE_SPACE))
	{
		if(!_free && _grounded)	
			_gravity -= 0.08;
		else if(_free)
			_mov += _up;
	}

	move(world);
}

void Camera3D::move(World& world)
{
	if(!_free)
	{
		_gravity += 0.01;

		int gStep = __abs((int)(_gravity * 100));
		for(int i = 0; i < gStep; i++)
		{
			if(!isColliding(0, 0, _mov.Z - (_gravity / gStep), world))
				_position.Z -= _gravity / gStep;
			else
				_gravity = 0.0;
		}

		if(_position.Z < -60)
		{
			_position.SET(5, 5, 5);
			_gravity = 0.0;
		}
	}

	int xStep = __abs((int)(_mov.X * 100));
	for(int i = 0; i < xStep; i++)
	{
		if(!isColliding(_mov.X / xStep, 0, 0, world))
			_position.X += (_mov.X * _speed) / xStep;
		else
			_mov.X = 0;
	}
	int yStep = __abs((int)(_mov.Y * 100));
	for(int i = 0; i < yStep; i++)
	{
		if(!isColliding(0, _mov.Y / yStep, 0, world))
			_position.Y += (_mov.Y * _speed) / yStep;
		else
			_mov.Y = 0;
	}
	int zStep = __abs((int)(_mov.Z * 100));
	for(int i = 0; i < zStep; i++)
	{
		if(!isColliding(0, 0, _mov.Z / zStep, world))
			_position.Z += (_mov.Z * _speed) / zStep;
		else
			_mov.Z = 0;
	}
}

bool Camera3D::isColliding(double x, double y, double z, World& world)
{
	int x0 = (int)(_position.X + x + 0.2f);
	int x1 = (int)(_position.X + x + 0.8f);

	int y0 = (int)(_position.Y + y + 0.2f);
	int y1 = (int)(_position.Y + y + 0.8f);

	int z0 = (int)(_position.Z + z - 1.4f);
	int z1 = (int)(_position.Z + z + 0.8f);

	int zGrounded = (int)(_position.Z + z - 1.4f - 0.1f);
	if(world.get_block(x0, y0, zGrounded) || world.get_block(x1, y0, zGrounded) || world.get_block(x1, y1, zGrounded) || world.get_block(x0, y1, zGrounded))
		_grounded = true;
	else
		_grounded = false;

	if(world.get_block(x0, y0, z0)) return true;
	if(world.get_block(x1, y0, z0)) return true;
	if(world.get_block(x1, y1, z0)) return true;
	if(world.get_block(x0, y1, z0)) return true;

	if(world.get_block(x0, y0, z1)) return true;
	if(world.get_block(x1, y0, z1)) return true;
	if(world.get_block(x1, y1, z1)) return true;
	if(world.get_block(x0, y1, z1)) return true;

	return false;
}

void Camera3D::update_view()
{
	_phi = _phi > 89 ? 89 : _phi;
	_phi = _phi < -89 ? -89 : _phi;

	_direction.X = cos(_phi * M_PI / 180) * cos(_theta * M_PI / 180);
	_direction.Y = cos(_phi * M_PI / 180) * sin(_theta * M_PI / 180);	// Spherical coordinate system
	_direction.Z = sin(_phi * M_PI / 180);

	_left = _up.crossProduct(_direction);
	_left.normalize();

	_forward = _up.crossProduct(_left);
	_forward.normalize();
}

void Camera3D::look()
{
	_target = _position + _direction;
    Matrixes::matrix_mode(matrix::view);
    Matrixes::lookAt(_position.X, _position.Y, _position.Z, _target.X, _target.Y, _target.Z, 0, 0, 1);
}

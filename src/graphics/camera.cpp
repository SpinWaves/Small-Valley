#include "matrixes.h"
#include "camera.h"

Camera3D::Camera3D()
{
	_position.SET(0, 0, 0);
	_up.SET(0, 0, 1);
	VectorsFromAngles();
}

void Camera3D::onEvent(const Input& input)
{
	if(_grabMouse)
	{
		_theta -= input.getXRel() * _sensivity;
		_phi -= input.getYRel() * _sensivity;
		VectorsFromAngles();
	}

	if(input.getInKey(SDL_SCANCODE_F1, action::up))
	{
		_grabMouse = _grabMouse ? SDL_FALSE : SDL_TRUE;
		SDL_SetRelativeMouseMode(_grabMouse);
	}
	if(!_grabMouse && input.getInMouse(1))
	{
		_grabMouse = SDL_TRUE;
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	_movement.SET(0, 0, 0);

	realspeed = (input.getInKey(SDL_SCANCODE_Q)) ? 10 * _speed : _speed;

	if(input.getInKey(SDL_SCANCODE_W) || input.getInKey(SDL_SCANCODE_UP))
		_movement -= _forward;
	if(input.getInKey(SDL_SCANCODE_S) || input.getInKey(SDL_SCANCODE_DOWN))
		_movement += _forward;
	if(input.getInKey(SDL_SCANCODE_A) || input.getInKey(SDL_SCANCODE_LEFT))
		_movement += _left;
	if(input.getInKey(SDL_SCANCODE_D) || input.getInKey(SDL_SCANCODE_RIGHT))
		_movement -= _left;
	if(input.getInKey(SDL_SCANCODE_LSHIFT) || input.getInKey(SDL_SCANCODE_RSHIFT))
		_movement -= _up;
	if(input.getInKey(SDL_SCANCODE_SPACE))
		_movement += _up;

	_position += _movement * realspeed;
}

void Camera3D::VectorsFromAngles()
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

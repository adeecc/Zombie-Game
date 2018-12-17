#include "Camera2D.h"
#include <algorithm>

namespace Bengine {

Camera2D::Camera2D()  {
	//Empty	
}


Camera2D::~Camera2D() {
	//Empty	
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera2D::update() {
	if (_needsMatrixUpdate) {

		//Camera Translation
		glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);

		//Camera Scale
		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		_needsMatrixUpdate = false;
	}
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
	//Invert y-direction
	screenCoords.y = _screenHeight - screenCoords.y;

	//Make origin the center
	screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);

	//SCale the Coordinates
	screenCoords /= _scale;

	//Translate Camera Position
	screenCoords += _position;

	return screenCoords;

}

// Simple AABB test to see if a box is int the camera view
bool Camera2D::isBoxInView(const glm::vec2 & position, const glm::vec2 dimensions) {

	glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / (_scale);

	// The minimum destance before a collision occurs
	const float MIN_DIST_X = (dimensions.x + scaledScreenDimensions.x) / 2.0f;
	const float MIN_DIST_Y = (dimensions.y + scaledScreenDimensions.y) / 2.0f;

	// Center position of the parameters
	glm::vec2 centerPos = position + (dimensions / 2.0f);
	// Center position of the camera
	glm::vec2 centerCameraPos = _position;
	// Vector from camera to input
	glm::vec2 distVec = centerPos - centerCameraPos;

	float xDepth = MIN_DIST_X - abs(distVec.x);
	float yDepth = MIN_DIST_Y - abs(distVec.y);

	// If this is true, we are colliding
	if (xDepth > 0 && yDepth > 0) {
		// THere was a collision
		return true;
	}

	return false;
}

}

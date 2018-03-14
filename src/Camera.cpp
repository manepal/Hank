#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>


const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const float FOV = 45.0f;

Camera::Camera() :
	mPosition(glm::vec3(0.0f, 0.0f, 10.0f)),
	mTarget(glm::vec3(0.0f)),
	mUp(WORLD_UP),
	mFOV(FOV)
{
}

Camera::~Camera()
{
}

float Camera::getFOV() const
{
	return mFOV;
}

glm::vec3 Camera::getPosition() const
{
	return mPosition;
}

glm::vec3 Camera::getTarget() const
{
	return mTarget;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(mPosition, mTarget, mUp);
}

glm::mat4 Camera::getPerspective(float width, float height) const
{
	return glm::perspective(mFOV, width / height, 0.1f, 100.0f);
}

void Camera::move(float x, float y)
{
	mPosition.x += x;
	mPosition.y += y;

	updateCameraVectors();
}

void Camera::setPosition(const glm::vec3 & position)
{
	mPosition = position;
	// update the camera vector to calculate new target
	updateCameraVectors();
}

void Camera::setFOV(float fov)
{
	mFOV = fov;
}

void Camera::updateCameraVectors()
{
	mTarget = glm::vec3(mPosition.x, mPosition.y, 0.0f);
}

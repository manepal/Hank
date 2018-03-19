#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>

#include "Window.h"

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

const glm::vec3& Camera::getPosition() const
{
	return mPosition;
}

const glm::vec3& Camera::getTarget() const
{
	return mTarget;
}

const glm::mat4& Camera::getViewMatrix() const
{
	return glm::lookAt(mPosition, mTarget, mUp);
}

const glm::mat4& Camera::getPerspective() const
{
	return glm::perspective(mFOV, Window::getInstance()->getWidth() / (float)Window::getInstance()->getHeight(), 0.1f, 100.0f);
}

const glm::mat4 & Camera::getOrtho()
{
	static float x = Window::getInstance()->getWidth() / 2.0f;
	static float y = Window::getInstance()->getHeight() / 2.0f;

	float zoom = mFOV / FOV;

	return glm::ortho(-x * zoom, x * zoom, -y * zoom, y * zoom, 0.1f, 100.0f);
}



void Camera::move(float x, float y)
{
	mPosition.x += x;
	mPosition.y += y;

	updateCameraVectors();
}

void Camera::zoom(float zoom)
{
	mFOV += zoom;
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

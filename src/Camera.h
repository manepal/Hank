#ifndef CAMERA_H
#define CAMERA_H


#include <glm\glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getPerspective() const;
	const glm::mat4& getOrtho();

	void move(float x, float y);
	void zoom(float zoom);

	// getters
	const glm::vec3& getPosition() const;
	const glm::vec3& getTarget() const;

	// setters
	void setPosition(const glm::vec3& position);
	void setFOV(float fov);

private:
	glm::vec3 mPosition;
	glm::vec3 mTarget;
	glm::vec3 mUp;

	float mFOV;

	void updateCameraVectors();
};


#endif // CAMERA_H
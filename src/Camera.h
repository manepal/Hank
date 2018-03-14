#ifndef CAMERA_H
#define CAMERA_H


#include <glm\glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 getViewMatrix() const;
	glm::mat4 getPerspective(float width, float height) const;

	void move(float x, float y);

	// getters
	float getFOV() const;
	glm::vec3 getPosition() const;
	glm::vec3 getTarget() const;

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
#include "Camera.h"

void Camera::update()
{
	target = glm::vec3(0);
	position = glm::vec3(0, 0, speed);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(target, position, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjectionMatrix()
{
	if (orthographic)
	{
		//ortho
		return ortho(-1.f, 1.f, .01f, 100.f);
	}
	else
	{
		//perspective
		return perspective(fov, 1.f, .01f, 100.f);
	}
}

glm::mat4 Camera::perspective(float fov, float aspetRatio, float nearPlane, float farPlane)
{
	return glm::perspective(fov, 1.f, .01f, 100.f);
}

glm::mat4 Camera::ortho(float height, float aspectRatio, float nearPlane, float farPlane)
{
	return glm::ortho(-1.f, 1.f, -1.f, 1.f, .01f, 100.f);
}
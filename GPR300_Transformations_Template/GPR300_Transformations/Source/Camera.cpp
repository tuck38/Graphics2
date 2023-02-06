#include "Camera.h"

void Camera::update()
{
	target = glm::vec3(0);

	glm::vec3 newPos = position;
	newPos.x = position.x * cos(speed) - position.y * sin(speed);
	newPos.y = position.y * cos(speed) + position.x * sin(speed);
	position = newPos;



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
		return ortho(0.0f, 1080 / 720, .01f, 100.f);
	}
	else
	{
		//perspective
		return perspective(fov, 1080 / 720, .01f, 100.f);
	}
}

glm::mat4 Camera::perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{ 




	return glm::perspective(fov, aspectRatio, .01f, 100.f);
}

glm::mat4 Camera::ortho(float height, float aspectRatio, float nearPlane, float farPlane)
{
	return glm::ortho(1.f, -1.f, -1.f, 1.f, .01f, 100.f);
}
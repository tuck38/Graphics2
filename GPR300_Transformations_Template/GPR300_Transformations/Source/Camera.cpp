#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
	return glm::mat4();
}

glm::mat4 Camera::getProjectionMatrix(float fov, float height, float aspectRatio, float nearPlane, float farPlane)
{
	if (orthographic)
	{
		//ortho
		return glm::mat4();
	}
	else
	{
		//perspective
		return glm::mat4();
	}
}
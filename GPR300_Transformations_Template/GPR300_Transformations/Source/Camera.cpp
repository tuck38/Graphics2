#include "Camera.h"

void Camera::update()
{
	target = glm::vec3(0);


	glm::vec3 newPos = position;
	newPos.x = position.x * cos(speed) - position.z * sin(speed);
	newPos.z = position.z * cos(speed) + position.x * sin(speed);
	position = newPos;

	//position.y = radius;

}

glm::mat4 Camera::getViewMatrix()
{
	glm::vec3 f = glm::normalize(target - position);

	glm::vec3 r = glm::normalize(glm::cross(f, up));

	glm::vec3 u = glm::normalize(glm::cross(r, f));

	//inverse rotation matrix

	glm::mat4 rotInv = glm::mat4(1);

	rotInv[0][0] = r.x;
	rotInv[1][0] = r.y;
	rotInv[2][0] = r.z;

	rotInv[0][1] = u.x;
	rotInv[1][1] = u.y;
	rotInv[2][1] = u.z;

	rotInv[0][2] = -f.x;
	rotInv[1][2] = -f.y;
	rotInv[2][2] = -f.z;

	//inverse translation

	glm::mat4 transInv = glm::mat4(1);

	transInv[3][0] = -position.x;
	transInv[3][1] = -position.y;
	transInv[3][2] = -position.z;

	return rotInv * transInv;
}

glm::mat4 Camera::getProjectionMatrix()
{
	if (orthographic)
	{
		//ortho
		return ortho(orthographicSize, 1080.f / 720.f, .01f, 100.f);
	}
	else
	{
		//perspective
		return perspective(fov, 1080.f / 720.f, .01f, 100.f);
	}
}

glm::mat4 Camera::perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{ 
	return glm::perspective(glm::radians(fov), aspectRatio, .01f, 100.f);
}

glm::mat4 Camera::ortho(float height, float aspectRatio, float nearPlane, float farPlane)
{
	return glm::ortho(-1.f, 1.f, -1.f, 1.f, .01f, 100.f);
}
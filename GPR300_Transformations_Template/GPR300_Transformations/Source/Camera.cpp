#include "Camera.h"

void Camera::update()
{
	target = glm::vec3(0);

	position = glm::vec3(radius);

	glm::vec3 newPos = position;
	newPos.x = position.x * cos(speed) - position.z * sin(speed);
	newPos.z = position.z * cos(speed) + position.x * sin(speed);
	position = newPos;

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
		return ortho(orthographicSize, aspectRatio, 0.1f, 100.f);
	}
	else
	{
		//perspective
		return perspective(fov, aspectRatio, 0.1f, 100.f);
	}
}

glm::mat4 Camera::perspective(float fov, float aspectRatio, float n, float f)
{ 
	float fovy = glm::radians(fov);

	float a = aspectRatio;

	float c = tan(fovy / 2);

	glm::mat4 prespec = glm::mat4(1);

	prespec[0][0] = 1 / (a * c);
	prespec[1][1] = 1 / c;
	prespec[2][2] = -((f + n) / (f - n));
	prespec[3][2] = -((2 * f * n) / (f - n));
	prespec[2][3] = -1;

	return prespec;
}

glm::mat4 Camera::ortho(float height, float aspectRatio, float n, float f)
{
	float width = aspectRatio * height;

	float r = width / 2;
	float t = height / 2;
	float b = -t;
	float l = -r;

	glm::mat4 ortho = glm::mat4(1);

	ortho[0][0] = 2 / (r - l);
	ortho[1][1] = 2 / (t - b);
	ortho[2][2] = -2 / (f - n);

	ortho[3][0] = -(r + l) / (r - l);
	ortho[3][1] = -(t + b) / (t - b);
	ortho[3][2] = -(f + n) / (f - n);


	//return glm::ortho(-100, 100, -100, 100);
	return ortho;
}
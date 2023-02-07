#pragma once
#include "Transform.h"

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 target;

	float height;
	float aspectRatio;

	const glm::vec3 up = glm::vec3(0, 1, 0);
	
	float fov;
	float orthographicSize;

	float speed;
	float radius;

	bool orthographic;

	Camera()
	{
		position = glm::vec3(3);
		target = glm::vec3(0);


		height = 720;
		fov = 2;
		radius = 2;
		speed = 0;
		orthographicSize = 10;
		aspectRatio = 1080 / 720;

		orthographic = false;
	}

	void update();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 ortho(float height, float aspectRatio, float nearPlane, float farPlane);
	glm::mat4 perspective(float fov, float aspetRatio, float nearPlane, float farPlane);

};
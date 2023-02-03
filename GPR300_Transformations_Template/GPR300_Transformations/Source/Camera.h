#pragma once
#include "Transform.h"

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 target;
	
	float fov;
	float orthographicSize;

	bool orthographic;

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(float fov, float height, float aspectRatio, float nearPlane, float farPlane);

};
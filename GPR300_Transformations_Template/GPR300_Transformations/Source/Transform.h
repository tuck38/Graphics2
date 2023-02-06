#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
public:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s)
	{
		position = p;
		rotation = r;
		scale = s;
	}

	glm::mat4 getModelMatrix();

};
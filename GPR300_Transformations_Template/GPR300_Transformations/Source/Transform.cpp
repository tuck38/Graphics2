#include "Transform.h"

glm::mat4 Transform::getModelMatrix()
{
	//Scale

	glm::mat4 scaleMat(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1
		);

	//Rotation

	glm::mat4 rotMatX(
	1, 0, 0, 0,
	0, cos(rotation), -sin(rotation), 0,
	0, sin(rotation), cos(rotation), 0,
	0, 0, 0, 1
	);
	
	glm::mat4 rotMatY(
	cos(rotation), 0, sin(rotation), 0,
	0, 1, 0, 0,
	-sin(rotation), 0, cos(rotation), 0,
	0, 0, 0, 1
	);

	glm::mat4 rotMatZ(
	cos(rotation), -sin(rotation), 0, 0,
	sin(rotation), cos(rotation), 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	);

	glm::mat4 rotMat = rotMatX * rotMatY * rotMatZ;

	//Translation



	return glm::mat4();
}
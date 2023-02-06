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
	0, cos(rotation.x), sin(rotation.x), 0,
	0, -sin(rotation.x), cos(rotation.x), 0,
	0, 0, 0, 1
	);
	
	glm::mat4 rotMatY(
	cos(rotation.y), 0, -sin(rotation.y), 0,
	0, 1, 0, 0,
	sin(rotation.y), 0, cos(rotation.y), 0,
	0, 0, 0, 1
	);

	glm::mat4 rotMatZ(
	cos(rotation.z), sin(rotation.z), 0, 0,
	-sin(rotation.z), cos(rotation.z), 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	);

	glm::mat4 rotMat = rotMatX * rotMatY * rotMatZ;

	//Translation

	glm::mat4 transMat(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	position.x, position.y, position.z, 1
	);

	return transMat * rotMat * scaleMat;
}
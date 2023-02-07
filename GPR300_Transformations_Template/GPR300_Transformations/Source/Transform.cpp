#include "Transform.h"

glm::mat4 Transform::getModelMatrix()
{
	//Scale

	glm::mat4 scaleMat = glm::mat4(1);
	scaleMat[0][0] = scale.x;
	scaleMat[1][1] = scale.y;
	scaleMat[2][2] = scale.z;

	//Rotation

	glm::mat4 rotMatX = glm::mat4(1);

	rotMatX[1][1] = cos(rotation.x);
	rotMatX[2][1] = -sin(rotation.x);
	rotMatX[1][2] = sin(rotation.x);
	rotMatX[2][2] = cos(rotation.x);
	
	glm::mat4 rotMatY = glm::mat4(1);

	rotMatY[0][0] = cos(rotation.y);
	rotMatY[2][0] = sin(rotation.y);
	rotMatY[0][2] = -sin(rotation.y);
	rotMatY[2][2] = cos(rotation.y);



	glm::mat4 rotMatZ = glm::mat4(1);

	rotMatZ[0][0] = cos(rotation.z);
	rotMatZ[1][0] = -sin(rotation.z);
	rotMatZ[0][1] = sin(rotation.z);
	rotMatZ[1][1] = cos(rotation.z);

	glm::mat4 rotMat = glm::mat4(1);

	rotMat = rotMatX * rotMatY * rotMatZ;

	//Translation

	glm::mat4 transMat = glm::mat4(1);

	transMat[3][0] = position.x;
	transMat[3][1] = position.y;
	transMat[3][2] = position.z;

	return  transMat * rotMat * scaleMat;
}
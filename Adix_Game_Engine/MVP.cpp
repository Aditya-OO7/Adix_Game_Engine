#include "MVP.h"

MVP::MVP()
{
}

MVP::MVP(Shader ourShader)
{
	shader = ourShader;
}

void MVP::Projection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	shader.setMatrixFV(4, "projection", 1, GL_FALSE, glm::value_ptr(projection));
}

void MVP::View(glm::mat4 viewMatrix)
{
	view = viewMatrix;
	shader.setMatrixFV(4, "view", 1, GL_FALSE, glm::value_ptr(view));
}

void MVP::Model(glm::vec3 translation, float angle, glm::vec3 axis)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, translation);
	model = glm::rotate(model, glm::radians(angle), axis);
	shader.setMatrixFV(4, "model", 1, GL_FALSE, glm::value_ptr(model));
}

void MVP::Model(glm::vec3 translation, glm::vec3 scale)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, translation);
	model = glm::scale(model, scale);
	shader.setMatrixFV(4, "model", 1, GL_FALSE, glm::value_ptr(model));
}

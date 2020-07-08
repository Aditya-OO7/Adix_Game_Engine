#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Shader.h"

class MVP
{
public :
	MVP();
	MVP(Shader ourShader);
	
	void Projection(float fov, float aspectRatio, float nearPlane, float farPlane);
	void View(glm::mat4 viewMatrix);
	void Model(glm::vec3 translation, float angle, glm::vec3 axis);

	void Model(glm::vec3 translation, glm::vec3 scale);

private :
	Shader shader;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;

};
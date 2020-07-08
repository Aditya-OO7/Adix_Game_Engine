#pragma once
#ifndef MESH
#define MESH

#include<glad/glad.h>
#include<glm/glm.hpp>

#include"Shader.h"

#include<string>
#include<vector>

using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Textures
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public :
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Textures> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Textures> textures);
	void Draw(Shader &shader);

private :
	unsigned int VBO, EBO;

	void setupMesh();
};

#endif // !MESH
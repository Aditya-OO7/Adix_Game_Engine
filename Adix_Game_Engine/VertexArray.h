#pragma once
#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include<glad/glad.h>
#include<vector>

enum class Buffer
{
	VERTEX_BUFFER, ELEMENT_BUFFER
};

class VertexArray
{
	unsigned int ID;
public :
	static unsigned int vboID;
	static unsigned int eboID;

	VertexArray();

	void Bind();
	void BindBuffer(Buffer bufferType, unsigned int id);
	static void UnBind();
	unsigned int AddVertexBufferObject(unsigned int size, const void* data, GLenum usage);
	unsigned int AddElementBufferObject(unsigned int size, const void* data, GLenum usage);
};

#endif // !VERTEX_ARRAY
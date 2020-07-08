#include "VertexArray.h"

unsigned int VertexArray::vboID;
unsigned int VertexArray::eboID;

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}

void VertexArray::Bind()
{
	glBindVertexArray(ID);
}

void VertexArray::BindBuffer(Buffer bufferType, unsigned int id)
{
	glBindVertexArray(ID);
	if (bufferType == Buffer::VERTEX_BUFFER)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	if (bufferType == Buffer::ELEMENT_BUFFER)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

unsigned int VertexArray::AddVertexBufferObject(unsigned int size, const void* data, GLenum usage)
{
	Bind();
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);

	return vboID;
}

unsigned int VertexArray::AddElementBufferObject(unsigned int size, const void* data, GLenum usage)
{
	Bind();
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);

	return eboID;
}
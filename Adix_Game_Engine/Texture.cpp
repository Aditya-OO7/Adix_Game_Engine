#include "Texture.h"

Texture::Texture()
{
	ID = NULL;
	width = NULL;
	height = NULL;
	nrChannels = NULL;
	data = NULL;
}

Texture::Texture(const char* path, unsigned int wrapper, unsigned int filter)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapper);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapper);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (nrChannels == 3 ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::assignTex(Shader shader, int nTex)
{
	shader.setInt("nTex", nTex);
}

void Texture::removeTex(Shader shader)
{
	shader.setInt("nTex", 99);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
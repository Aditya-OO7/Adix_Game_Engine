#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<iostream>
#include"stb_image.h"
#include"Shader.h"

class Texture
{
private :
	int width;
	int height;
	int nrChannels;
	unsigned char* data;
	unsigned int ID;
public :
	
	Texture();
	Texture(const char* path, unsigned int wrapper, unsigned int filter);

	void Bind(unsigned int slot);
	void assignTex(Shader shader, int nTex);
	static void removeTex(Shader shader);
	static void UnBind();

};

#endif // !TEXTURE_H
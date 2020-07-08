#pragma once

#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<glm/glm.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader
{
public :
	unsigned int ID;

	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	
	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value1) const;
	void setInt(const std::string& name, int value1, int value2) const;
	void setInt(const std::string& name, int value1, int value2, int value3) const;
	void setInt(const std::string& name, int value1, int value2, int value3, int value4) const;
	void setVInt(unsigned int nInt, const std::string& name, unsigned int count, const int* value) const;

	void setFloat(const std::string& name, float value1) const;
	void setFloat(const std::string& name, float value1, float value2) const;
	void setFloat(const std::string& name, float value1, float value2, float value3) const;
	void setFloat(const std::string& name, float value1, float value2, float value3, float value4) const;
	void setVFloat(unsigned int nFloat, const std::string& name, unsigned int count, const float* value) const;

	void setUnsignedInt(const std::string& name, unsigned int value1) const;
	void setUnsignedInt(const std::string& name, unsigned int value1, unsigned int value2) const;
	void setUnsignedInt(const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3) const;
	void setUnsignedInt(const std::string& name,
		unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) const;
	void setVUnsignedInt(unsigned int nUInt, const std::string& name, unsigned int count, const unsigned int* value) const;

	void setMatrixFV(unsigned int row_col_Mat, const std::string& name, unsigned int count, bool transpose, const float* value) const;

	void setVec(const std::string& name, float value1, float value2) const;
	void setVec(const std::string& name, float value1, float value2, float value3) const;
	void setVec(const std::string& name, float value1, float value2, float value3, float value4) const;

	void setVec(const std::string& name, glm::vec4 vector) const;
	void setVec(const std::string& name, glm::vec3 vector) const;
	void setVec(const std::string& name, glm::vec2 vector) const;
};

#endif // !SHADER_H
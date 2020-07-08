#include "Shader.h"

Shader::Shader()
{
	ID = NULL;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//create vertex shader.
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	//give openGL source code of vertex shader.
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	//compile vertex shader code.
	glCompileShader(vertex);

	//check if vertex shader code compiled successfully.
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	//give openGL source code of fragment shader.
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	//compile fragment shader.
	glCompileShader(fragment);

	//check if fragment shader code compiled successfully.
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	//check if shader program is linked successfully.
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
	}
	
	//after linking of shader program vertex and fragment shaders are not needed, so, delete them.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	//use shader program.
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value1) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value1);
}

void Shader::setInt(const std::string& name, int value1, int value2) const
{
	glUniform2i(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void Shader::setInt(const std::string& name, int value1, int value2, int value3) const
{
	glUniform3i(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setInt(const std::string& name, int value1, int value2, int value3, int value4) const
{
	glUniform4i(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setVInt(unsigned int nInt, const std::string& name, unsigned int count, const int* value) const
{
	switch (nInt)
	{
	case 1:
		glUniform1iv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 2:
		glUniform2iv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 3:
		glUniform3iv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 4:
		glUniform4iv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	default:
		break;
	}
}

void Shader::setFloat(const std::string& name,
	float value1) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value1);
}

void Shader::setFloat(const std::string& name,
	float value1, float value2) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void Shader::setFloat(const std::string& name,
	float value1, float value2, float value3) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setFloat(const std::string& name,
	float value1, float value2, float value3, float value4) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setVFloat(unsigned int nFloat, const std::string& name, unsigned int count, const float* value) const
{
	switch (nFloat)
	{
	case 1 :
		glUniform1fv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 2 :
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 3 :
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 4 :
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	default:
		break;
	}
}


void Shader::setUnsignedInt(const std::string& name,
	unsigned int value1) const
{
	glUniform1ui(glGetUniformLocation(ID, name.c_str()), value1);
}

void Shader::setUnsignedInt(const std::string& name,
	unsigned int value1, unsigned int value2) const
{
	glUniform2ui(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void Shader::setUnsignedInt(const std::string& name,
	unsigned int value1, unsigned int value2, unsigned int value3) const
{
	glUniform3ui(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setUnsignedInt(const std::string& name,
	unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) const
{
		glUniform4ui(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}


void Shader::setVUnsignedInt(unsigned int nUInt, const std::string& name, unsigned int count, const unsigned int* value) const
{
	switch (nUInt)
	{
	case 1:
		glUniform1uiv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 2:
		glUniform2uiv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 3:
		glUniform3uiv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	case 4:
		glUniform4uiv(glGetUniformLocation(ID, name.c_str()), count, value);
		break;
	default:
		break;
	}
}

void Shader::setMatrixFV(unsigned int row_col_Mat, const std::string& name, unsigned int count, bool transpose, const float* value) const
{
	switch (row_col_Mat)
	{
	case 2:
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	case 23:
		glUniformMatrix2x3fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	case 24:
		glUniformMatrix2x4fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	case 3:
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	case 32:
		glUniformMatrix3x2fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	case 34:
		glUniformMatrix3x4fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	case 4:
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	case 42:
		glUniformMatrix4x2fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	case 43:
		glUniformMatrix4x3fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
		break;
	default:
		break;
	}
}



void Shader::setVec(const std::string& name, float value1, float value2) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void Shader::setVec(const std::string& name, float value1, float value2, float value3) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setVec(const std::string& name, float value1, float value2, float value3, float value4) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}



void Shader::setVec(const std::string& name, glm::vec2 vector) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y);
}

void Shader::setVec(const std::string& name, glm::vec3 vector) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z);
}

void Shader::setVec(const std::string& name, glm::vec4 vector) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z, vector.w);
}
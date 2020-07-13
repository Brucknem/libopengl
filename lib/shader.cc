#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

namespace libopengl {

	void Shader::Activate()
	{
		glUseProgram(ID);
	}
	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void Shader::setVec2(const std::string& name, const float x, const float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void Shader::setVec3(const std::string& name, const glm::vec3 vec) const
	{
		setVec3(name, vec.x, vec.y, vec.z);
	}
	void Shader::setVec3(const std::string& name, const float x, const float y, const float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void Shader::setVec3i(const std::string& name, const int x, const int y, const int z) const
	{
		glUniform3i(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void Shader::setColor(const std::string& name, float r, float g, float b, float a) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), r, g, b, a);
	}
	void Shader::setMat3(const std::string& name, const glm::mat3 matrix) {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void Shader::setMat4(const std::string& name, const glm::mat4 matrix) {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void Shader::setArray3(const std::string& name, GLfloat *vec, int count) {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), count, vec);
	}

	bool Shader::checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		return success != 0;
	}
	void Shader::attachIfValid(unsigned int shaderId) {
		if (shaderId != (unsigned int)-1) {
			glAttachShader(ID, shaderId);
		}
	}
	void Shader::deleteIfValid(unsigned int shaderId) {
		if (shaderId != (unsigned int)-1) {
			glDeleteShader(shaderId);
		}
	}
	unsigned int Shader::compileShader(const char* shaderPath, int type) {
		std::string name;
		switch (type) {
		case GL_VERTEX_SHADER:
			name = "VERTEX";
			break;
		case GL_FRAGMENT_SHADER:
			name = "FRAGMENT";
			break;
		case GL_GEOMETRY_SHADER:
			name = "GEOMETRY";
			break;
		case GL_COMPUTE_SHADER:
			name = "COMPUTE";
			break;
		default:
			std::cerr << "(" << name << ") Can only compile shaders of types: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER" << std::endl;
			return -1;
		}

		if (std::strlen(shaderPath) == 0) {
			//std::cout << "Skipping " << name << std::endl;
			return -1;
		}

		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::ifstream vertexShaderFile;
		// ensure ifstream objects can throw exceptions:
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vertexShaderFile.open(shaderPath);
			std::stringstream vertexShaderStream;
			// read file's buffer contents into streams
			vertexShaderStream << vertexShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			// convert stream into string
			vertexCode = vertexShaderStream.str();
		}
		catch (const std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vertexShaderCode = vertexCode.c_str();
		// 2. compile shaders
		unsigned int vertexShader;
		// vertex shader
		vertexShader = glCreateShader(type);
		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, name);

		return vertexShader;
	}

	VertexFragmentShader::VertexFragmentShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) : Shader()
	{			
		unsigned int vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER );
		unsigned int fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
		unsigned int geometryShader = compileShader(geometryPath, GL_GEOMETRY_SHADER);

		ID = glCreateProgram();
		attachIfValid(vertexShader);
		attachIfValid(fragmentShader);
		attachIfValid(geometryShader);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		deleteIfValid(vertexShader);
		deleteIfValid(fragmentShader);
		deleteIfValid(geometryShader);
	}

	ComputeShader::ComputeShader(const char* computeShaderPath) : Shader()
	{
		unsigned int computeShader = compileShader(computeShaderPath, GL_COMPUTE_SHADER);

		// shader Program
		ID = glCreateProgram();
		attachIfValid(computeShader);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(computeShader);

		int work_grp_size[3];

		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

		printf("max local (in one shader) work group sizes x:%i y:%i z:%i\n",
			work_grp_size[0], work_grp_size[1], work_grp_size[2]);

		int work_grp_inv;
		glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
		printf("max local work group invocations %i\n", work_grp_inv);
	}
}
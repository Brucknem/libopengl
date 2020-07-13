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
	
	/**
	 * @brief Determines the shader name by the OpenGL type flag.
	 * 
	 * @param type 
	 * @return std::string 
	 */
	std::string determineName(int type){
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
			throw std::invalid_argument("(" + name + ") Can only compile shaders of types: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER");
		}
		return name;
	}

	/**
	 * @brief Reads some glsl shader code from the given path.
	 * 
	 * @param shaderPath 
	 * @return std::string 
	 */
	std::string readShaderCode(const char* shaderPath){
		std::string code;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		code = shaderStream.str();
		return code;
	}

	unsigned int Shader::compileShader(const char* shaderPath, int type) {
		std::string name = determineName(type);

		if (std::strlen(shaderPath) == 0) {
			return -1;
		}

		std::string shaderCode = readShaderCode(shaderPath);
		const char* c_style = shaderCode.c_str();

		unsigned int shader;
		shader = glCreateShader(type);
		glShaderSource(shader, 1, &c_style, NULL);
		glCompileShader(shader);
		checkCompileErrors(shader, name);

		return shader;
	}

	VertexFragmentShader::VertexFragmentShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) : Shader()
	{			
		unsigned int shader = compileShader(vertexPath, GL_VERTEX_SHADER );
		unsigned int fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
		unsigned int geometryShader = compileShader(geometryPath, GL_GEOMETRY_SHADER);

		ID = glCreateProgram();
		attachIfValid(shader);
		attachIfValid(fragmentShader);
		attachIfValid(geometryShader);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		deleteIfValid(shader);
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

		std::cout << "max local (in one shader) work group sizes x: " << work_grp_size[0] << " y: " << work_grp_size[1] << " z:" << work_grp_size[2] << std::endl;

		int work_grp_inv;
		glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
		std::cout << "max local work group invocations " << work_grp_inv;
	}
}
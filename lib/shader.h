#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace libopengl {
	class Shader
	{
	public:
		unsigned int ID;

		/**
		 * @brief Activates the shader.
		 */
		void Activate();

		/**
		 * @brief Sets a boolean shader value by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setBool(const std::string& name, bool value) const;

		/**
		 * @brief Sets a integer shader value by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setInt(const std::string& name, int value) const;

		/**
		 * @brief Sets a floating point shader value by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setFloat(const std::string& name, float value) const;

		/**
		 * @brief Sets a two dimensional shader vector by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setVec2(const std::string& name, const float x, const float y) const;

		/**
		 * @brief Sets a three dimensional shader vector by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setVec3(const std::string& name, const glm::vec3 vec) const;

		/**
		 * @brief Sets a three dimensional shader vector by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setVec3(const std::string& name, const float x, const float y, const float z) const;

		/**
		 * @brief Sets a integer three dimensional shader vector by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setVec3i(const std::string& name, const int x, const int y, const int z) const;

		/**
		 * @brief Sets a RGBA shader vector by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setColor(const std::string& name, float r, float g, float b, float a) const;

		/**
		 * @brief Sets a three dimensional square shader matrix by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setMat3(const std::string& name, const glm::mat3 matrix);

		/**
		 * @brief Sets a four dimensional square shader matrix by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 */
		void setMat4(const std::string& name, const glm::mat4 matrix);

		/**
		 * @brief Sets a three dimensional shader array by name.
		 * 
		 * @param name The name of the shader attribute
		 * @param value The value of the shader attribute
		 * @param count The number of array entries.
		 */
		void setArray3(const std::string& name, GLfloat *vec, int count);

	protected:
		/**
		 * @brief Checks the compiled shader or program for errors during compilation. 
		 * 
		 * @param shader The OpenGL object id.
		 * @param type The shader type.
		 */
		bool checkCompileErrors(unsigned int shader, std::string type);
		
		/**
		 * @brief Attaches the shader to the program.
		 * 
		 * @param shaderId The OpenGL object id.
		 */
		void attachIfValid(unsigned int shaderId) ;

		/**
		 * @brief Deletes the shader from the program.
		 * 
		 * @param shaderId The OpenGL object id.
		 */
		void deleteIfValid(unsigned int shaderId) ;

		/**
		 * @brief Compiles a shader, links the different parts and checks for compile errors. 
		 * 
		 * @param shaderPath The file path to the shader.
		 * @param type The shader type.
		 * @return unsigned int 
		 */
		unsigned int compileShader(const char* shaderPath, int type) ;
	};

	/**
	 * @brief A combined rendering shader program consisting of a vertex, fragment and optional geometry shaders.
	 * 
	 */
	class VertexFragmentShader : public Shader {
	public :

		/**
		 * @brief Construct a new Vertex Fragment Shader object
		 * 
		 * @param vertexPath The file path to the vertex shader code.
		 * @param fragmentPath The file path to the fragment shader code.
		 * @param geometryPath The file path to the geometry shader code.
		 */
		VertexFragmentShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = "");
	};

	/**
	 * @brief A generic compute shader program.
	 * 
	 */
	class ComputeShader : public Shader
	{
	public:
		/**
		 * @brief Construct a new Compute Shader object
		 * 
		 * @param computeShaderPath The file path to the compute shader code.
		 */
		ComputeShader(const char* computeShaderPath);
	};
}
#endif
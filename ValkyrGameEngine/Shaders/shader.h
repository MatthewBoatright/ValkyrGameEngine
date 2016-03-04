#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Valkyr { namespace Graphics {  

	class Shader
	{
	public:
		GLuint m_ProgramID;

		Shader(const char * vertex_file_path, const char * fragment_file_path);
		~Shader();

		GLuint getUniformLocation(const GLchar * uniform_name);
		GLuint getAttributeLocation(const char * attribute_name);
		void setUniform1i(const GLchar* name, int value);
		void setUniform1f(const GLchar* name, float value);
		void setUniform2f(const GLchar* name, const glm::vec2 & vector);
		void setUniform3f(const GLchar* name, const glm::vec3 & vector);
		void setUniform4f(const GLchar* name, const glm::vec4 & vector);
		void setUniformMat4(const GLchar* name, const glm::mat4 matrix);

		void enable() const;
		void disable() const;

	private:
		void loadShader(const char * vertex_file_path, const char * fragment_file_path);

	};

} }
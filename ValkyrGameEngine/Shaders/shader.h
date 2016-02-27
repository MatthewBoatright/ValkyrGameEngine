#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <fstream>

namespace Valkyr { namespace Graphics {  

	class Shader
	{
	public:
		GLuint m_ProgramID;
		Shader(const char * vertex_file_path, const char * fragment_file_path);
		~Shader();
		static Shader LoadShader(const char * vertex_file_path, const char * fragment_file_path);
	protected:
	private:
	};

} }
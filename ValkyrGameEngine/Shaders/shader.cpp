#include "shader.h"

namespace Valkyr { namespace Graphics {

	Shader::Shader(const char * vertex_file_path, const char * fragment_file_path)
	{
		// TODO: Remove all of this code away from the constructor
		// STEPS
		// 1) Create the shader objects
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// 2) Read the vertex code
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
		if (VertexShaderStream.is_open())
		{
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else
		{
			printf("Couldn't open vertex file: %s\n", vertex_file_path);
			return;
		}

		// 3) Read the fragment code
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);		
		if (FragmentShaderStream.is_open())
		{
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
		else
		{
			printf("Couldn't open fragment file: %s\n", fragment_file_path);
		}


		GLint Result = GL_FALSE;
		int InfoLogLength;

		// 4) Compile the vertex shader
		printf("Compiling vertex: %s\n", vertex_file_path);
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// 4.2) Check the vertex shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}

		// 5) Compile the fragment shader
		printf("Compiling fragment: %s\n", fragment_file_path);
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// 5.2) Check the fragment shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}

		// 6) Link the program
		printf("Linking...\n");
		m_ProgramID = glCreateProgram();
		glAttachShader(m_ProgramID, VertexShaderID);
		glAttachShader(m_ProgramID, FragmentShaderID);
		glLinkProgram(m_ProgramID);

		// 6.2) Check the program
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(m_ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}

		// 7) Detach shader objects
		glDetachShader(m_ProgramID, VertexShaderID);
		glDetachShader(m_ProgramID, FragmentShaderID);
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramID);
	}

} }
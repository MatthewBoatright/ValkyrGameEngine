#include <iostream>
#include "Window/window.h"
#include "Shaders/shader.h"

int main()
{
	using namespace Valkyr;
	using namespace Graphics;

	ShellWindow window("Valkyr Engine", 960, 540);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	Shader shader("Shaders/SimpleVertexShader.shd", "Shaders/SimpleFragmentShader.shd");

	double x, y;
	while (!window.closed())
	{
		window.clear();
		window.getCursorPosition(x, y);

		printf("%f, %f\n", x, y);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glUseProgram(shader.m_ProgramID);

		window.update();
	}

	return 0;
}

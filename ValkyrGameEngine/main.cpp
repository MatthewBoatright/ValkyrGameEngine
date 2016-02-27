#include <iostream>
#include "Window/window.h"
#include "Shaders/shader.h"
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

int main()
{
	using namespace Valkyr;
	using namespace Graphics;

	float width = 960;
	float height = 540;
	ShellWindow window("Valkyr Engine", width, height);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = 
	{
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

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		glm::mat4 View = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3((x / width), (height / y), 0), glm::vec3(0, 1, 0));
		glm::mat4 Model = glm::mat4(1.0f);
		shader.enable();
		shader.setUniformMat4("pr_matrix", Projection);
		shader.setUniformMat4("vw_matrix", View);
		shader.setUniformMat4("ml_matrix", Model);

		window.update();
	}

	return 0;
}

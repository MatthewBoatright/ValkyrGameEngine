#include <iostream>
#include "Window/window.h"
#include "Shaders/shader.h"
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Buffers/index_buffer.h"
#include "Buffers/vertex_array.h"
#include "Buffers/vertex_buffer.h"
#include "ToyBox/cube.h"

int main()
{
	using namespace Valkyr;
	using namespace Graphics;

	float width = 960;
	float height = 540;
	ShellWindow window("Valkyr Engine", width, height);

	Cube cube(5, 3, 2);

	//VertexBuffer vertexBuffer(g_vertex_buffer_data, 36 * 3, 3);
	//VertexBuffer colorBuffer(g_color_buffer_data, 36 * 3, 3);

	//VertexArray * vertexArray = new VertexArray();
	//vertexArray->addBuffer(&vertexBuffer, 0);
	//vertexArray->addBuffer(&colorBuffer, 1);
	//vertexArray->bind();

	Shader shader("Shaders/SimpleVertexShader.shd", "Shaders/SimpleFragmentShader.shd");

	double x, y;
	float rx = 0.0f;
	float ry = 0.0f;
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	while (!window.closed())
	{
		window.clear();
		window.getCursorPosition(x, y);	

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glm::mat4 Projection = glm::perspective(glm::radians(70.0f), 16.0f / 9.0f, 0.1f, 50.0f);
		glm::mat4 View = glm::lookAt(glm::vec3(0, 0, 8), 
									 glm::vec3(((float)(x * (10 * 2) / window.getWidth() - 10)), ((float)(10 - y * (10 * 2) / window.getHeight())) , 0), 
									 glm::vec3(0, 1, 0));
		glm::mat4 Model = glm::mat4(1.0f);
		Model *= glm::rotate(Model, (glm::mediump_float)rx += 0.01, glm::vec3(0, 1, 0));
		shader.enable();
		shader.setUniformMat4("pr_matrix", Projection);
		shader.setUniformMat4("vw_matrix", View);
		shader.setUniformMat4("ml_matrix", Model);

		window.update();

		if (rx > 360.0f)
			rx = 0.0f;

		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0)
		{
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
	}

	return 0;
}

#include <iostream>
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

int depmain()
{
	using namespace Valkyr;
	using namespace Graphics;

	float width = 960;
	float height = 540;
	ShellWindow window("Valkyr Engine", width, height);

#if 1
	Cube cube(1, 1, 1);
	//Cube cube(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec4(1, 0, 1, 0));
#else
	float x = 2;
	float y = 2;
	float z = 2;
	VertexArray * m_VertexArray = new VertexArray();

	GLfloat g_vertex_buffer_data[] =
	{
		-x,-y,-z, // A
		-x,-y, z, // B,
		-x, y, z, // C
		x, y,-z, // D
		-x,-y,-z, // A
		-x, y,-z, // E
		x,-y, z, // B,
		-x,-y,-z, // A
		x,-y,-z, // F
		x, y,-z, // D
		x,-y,-z, // F
		-x,-y,-z, // A
		-x,-y,-z, // A
		-x, y, z, // C
		-x, y,-z, // E
		x,-y, z, // B,
		-x,-y, z, // B,
		-x,-y,-z, // A
		-x, y, z, // C
		-x,-y, z, // B,
		x,-y, z, // B,
		x, y, z, // G
		x,-y,-z, // F
		x, y,-z, // D
		x,-y,-z, // F
		x, y, z, // G
		x,-y, z, // B,
		x, y, z, // G
		x, y,-z, // D
		-x, y,-z, // E
		x, y, z, // G
		-x, y,-z, // E
		-x, y, z, // C
		x, y, z, // G
		-x, y, z, // C
		x,-y, z, // B
	};

	GLfloat g_color_buffer_data[] =
	{
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};

	GLfloat g_uv_buffer_data[] = {
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};

	GLuint Texture = BMPLoader::loadBMP_custom("../lena_gray.bmp");

	m_VertexArray->addBuffer(new VertexBuffer(g_vertex_buffer_data, 36 * 3, 3), 0);
	m_VertexArray->addBuffer(new VertexBuffer(g_uv_buffer_data, 36 * 2, 2), 1);
	//m_VertexArray->addBuffer(new VertexBuffer(g_color_buffer_data, 36 * 3, 3), 1);
#endif

	//Shader shader("Shaders/SimpleVertexShader.shd", "Shaders/SimpleFragmentShader.shd");
	Shader shader("Shaders/TextureVertexShader.shd", "Shaders/TextureFragmentShader.shd");

	double cursorX, cursorY;
	float rx = 0.0f;
	float ry = 0.0f;
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	while (!window.closed())
	{
		window.clear();
		window.getCursorPosition(cursorX, cursorY);
		glfwGetCursorPos(window.getWindow(), &cursorX, &cursorY);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);


		glm::mat4 Projection = glm::perspective(glm::radians(70.0f), 16.0f / 9.0f, 0.1f, 50.0f);
		glm::mat4 View = glm::lookAt(glm::vec3(0, 0, 6),
			glm::vec3(((float)(cursorX * (10 * 2) / window.getWidth() - 10)), ((float)(10 - cursorY * (10 * 2) / window.getHeight())), 0),
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
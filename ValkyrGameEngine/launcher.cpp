// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "ToyBox/cube.h"
#include "Common/window.h"
#include "Common/objloader.hpp"
#include "Common/vboindexer.hpp"
#include "Shaders/shader.h"
#include "Shaders/texture.h"
#include "Buffers/vertex_buffer.h"
#include "Buffers/index_buffer.h"
#include "Buffers/vertex_array.h"
#include "Models/obj_model.h"

using namespace Valkyr;
using namespace Graphics;

int main(void)
{
	// Main Window
	ShellWindow mainWindow("Valkyr Engine", 1024, 768);

	Shader shader("Shaders/SimpleVertexShader.shd", "Shaders/SimpleFragmentShader.shd");

	GLuint MatrixID = glGetUniformLocation(shader.m_ProgramID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(shader.m_ProgramID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(shader.m_ProgramID, "M");

	Texture tex("uvmap.dds");

	GLuint TextureID = glGetUniformLocation(shader.m_ProgramID, "myTextureSampler");

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("epidote.obj", vertices, uvs, normals);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	VertexBuffer vertexBuffer(indexed_vertices);
	VertexBuffer uvBuffer(indexed_uvs);
	VertexBuffer normalBuffer(indexed_normals);
	IndexBuffer elementBuffer(indices);

	VertexArray vertexArray;
	vertexArray.addBuffer(&vertexBuffer, 0);
	vertexArray.addBuffer(&uvBuffer, 1);
	vertexArray.addBuffer(&normalBuffer, 2);

	shader.enable();
	GLuint LightID = glGetUniformLocation(shader.m_ProgramID, "LightPosition_worldspace");

	while (!mainWindow.closed())
	{
		mainWindow.clear();
		shader.enable();

		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4, 4, 4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		glActiveTexture(GL_TEXTURE0);
		tex.bind();
		glUniform1i(TextureID, 0);

		vertexArray.bind();
		elementBuffer.bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		elementBuffer.unbind();
		vertexArray.unbind();

		mainWindow.update();
		mainWindow.calculateFPS();
	}

	return 0;
}
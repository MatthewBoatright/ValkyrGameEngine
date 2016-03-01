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
#include "Common/textureloader.hpp"
#include "Shaders/shader.h"
#include "Shaders/texture.h"
#include "Buffers/vertex_buffer.h"
#include "Buffers/index_buffer.h"
#include "Buffers/vertex_array.h"

using namespace Valkyr;
using namespace Graphics;

void loadVertexBuffer(const std::vector<glm::vec2> indexed_vertices, GLuint & buffer_id)
{
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec2), &indexed_vertices[0], GL_STATIC_DRAW);
}

void loadVertexBuffer(const std::vector<glm::vec3> indexed_vertices, GLuint & buffer_id)
{
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
}

int main(void)
{
	// Main Window
	ShellWindow mainWindow("Valkyr Engine", 1024, 768);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	Shader shader("Shaders/SimpleVertexShader.shd", "Shaders/SimpleFragmentShader.shd");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(shader.m_ProgramID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(shader.m_ProgramID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(shader.m_ProgramID, "M");

	// Load the texture
	//GLuint Texture = loadDDS("uvmap.DDS");
	//GLuint Texture = loadBMP_custom("uvmap.dds");
	Texture tex("uvmap.dds");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(shader.m_ProgramID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);

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

	// Get a handle for our "LightPosition" uniform
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

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4, 4, 4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		tex.bind();
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		vertexArray.bind();
		elementBuffer.bind();
		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
			);
		elementBuffer.unbind();
		vertexArray.unbind();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		mainWindow.update();
		mainWindow.calculateFPS();
	}

	return 0;
}
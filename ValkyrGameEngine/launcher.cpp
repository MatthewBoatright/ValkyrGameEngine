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

	OBJModel Epidote("epidote.obj");
	OBJModel Potato("potato2.obj");

	shader.enable();
	GLuint LightID = glGetUniformLocation(shader.m_ProgramID, "LightPosition_worldspace");

	int transX = 0;
	int transY = 0;
	while (!mainWindow.closed())
	{
		mainWindow.clear();
		shader.enable();

		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 TranslationMatrix = translate(mat4(), glm::vec3(transX++, 0, 0));
		glm::mat4 ModelMatrix = TranslationMatrix;
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4, 4, 4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		Epidote.bind();
		glDrawElements(GL_TRIANGLES, Epidote.getIndexBuffer()->getSize(), GL_UNSIGNED_SHORT, (void*)0);
		Epidote.unbind();

		ProjectionMatrix = getProjectionMatrix();
		ViewMatrix = getViewMatrix();
		ModelMatrix = glm::toMat4(glm::normalize(glm::quat(glm::vec3(0, transY++, 0))));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		Potato.bind();
		glDrawElements(GL_TRIANGLES, Potato.getIndexBuffer()->getSize(), GL_UNSIGNED_SHORT, (void*)0);
		Potato.unbind();

		mainWindow.update();
		mainWindow.calculateFPS();

		if (transX > 50)
			transX = -50;
		if (transY > 360)
			transY = 0;
	}

	return 0;
}
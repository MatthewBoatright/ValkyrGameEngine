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
#include "Models/mesh.h"

using namespace Valkyr;
using namespace Graphics;

int main(void)
{
	// Main Window
	ShellWindow mainWindow("Valkyr Engine", 1024, 768);

	Mesh * mesh = new Mesh();
	mesh->loadMesh("muro.mtl");

	Mesh * mesh2 = new Mesh();
	mesh2->loadMesh("epidote.obj");

	Shader shader("Shaders/basic.vsh", "Shaders/basic.fsh");
	shader.enable();

	//Shader shader("Shaders/SimpleVertexShader.shd", "Shaders/SimpleFragmentShader.shd");

	double transX = 0;
	double transY = 0;
	while (!mainWindow.closed())
	{
		mainWindow.clear();

		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		//glm::mat4 TranslationMatrix = translate(mat4(), glm::vec3(transX += 0.1, 0, 0));
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		shader.setUniform3f("LightPosition_WorldSpace", glm::vec3(4, 4, 4));
		shader.setUniformMat4("MVP", MVP);
		shader.setUniformMat4("V", ModelMatrix);
		shader.setUniformMat4("M", ViewMatrix);

		//ModelMatrix = glm::toMat4(glm::normalize(glm::quat(glm::vec3(0, transY += 0.1, 0))));
		//MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		//glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		mesh->render();
		mesh2->render();

		mainWindow.update();
		mainWindow.calculateFPS();
	}

	return 0;
}
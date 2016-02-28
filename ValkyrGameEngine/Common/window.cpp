#include "window.h"

namespace Valkyr { namespace Graphics {  

	ShellWindow::ShellWindow(char * windowName, int windowWidth, int windowHeight)
	{
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW.\n");
			return;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);

		if (m_Window == NULL)
		{
			fprintf(stderr, "Window instance could not be created.\n");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);

		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			fprintf(stderr, "Failed to initialize GLEW.\n");
			glfwTerminate();
			return;
		}

		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwPollEvents();
		glfwSetCursorPos(m_Window, windowWidth / 2, windowHeight / 2);

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);
	}

	ShellWindow::~ShellWindow()
	{
		glfwTerminate();
	}

	void ShellWindow::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		computeMatricesFromInputs(m_Window);
	}

	void ShellWindow::update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	bool ShellWindow::closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

} }
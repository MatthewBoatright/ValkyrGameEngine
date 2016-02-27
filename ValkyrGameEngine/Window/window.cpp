#include "window.h"

namespace Valkyr { namespace Graphics {  

	ShellWindow::ShellWindow(char* windowName, int windowWidth, int windowHeight)
		: m_Title(windowName), m_Width(windowWidth), m_Height(windowHeight)
	{
		if (!init())
			glfwTerminate();
	}

	ShellWindow::~ShellWindow()
	{
		glfwTerminate();
	}

	void ShellWindow::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void ShellWindow::update()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
		glfwPollEvents();
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glfwSwapBuffers(m_Window);
	}

	bool ShellWindow::closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void ShellWindow::getCursorPosition(double & x, double & y)
	{
		x = m_CursorX;
		y = m_CursorY;
	}

	bool ShellWindow::init()
	{
		// Initialize GLFW.
		if (!glfwInit())
		{
			fprintf(stderr, "Error initializing GLFW.\n");
			return false;
		}

		// Configure window hints.
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create the window.
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (m_Window == NULL)
		{
			fprintf(stderr, "Failed to open the GLFW window.\n");
			glfwTerminate();
			return false;
		}

		// Set callbacks.
		setWindowCallbacks();

		// Set V-Sync
		//glfwSwapInterval(0.0);

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			//Problem: glewInit failed, something is seriously wrong.
			std::cout << "glewInit failed, aborting." << std::endl;
		}

		// Odd GLEW error after initializing. Doesn't affect anything so just ignore it.
		GLenum error = glGetError();
		if (error != 1280)
			std::cout << "OpenGL Error: " << error << std::endl;

		// Set input mode.
		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		return true;
	}

	void ShellWindow::setWindowCallbacks()
	{
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, windowResized);
		glfwSetKeyCallback(m_Window, keyboardCallback);
		glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, cursorPositionCallback);
	}

	void windowResized(GLFWwindow * window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void keyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mod)
	{

	}

	void mouseButtonCallback(GLFWwindow * window, int button, int action, int mod)
	{

	}

	void cursorPositionCallback(GLFWwindow * window, double cursorX, double cursorY)
	{
		ShellWindow * win = (ShellWindow*)glfwGetWindowUserPointer(window);
		win->m_CursorX = cursorX;
		win->m_CursorY = cursorY;
	}

} }
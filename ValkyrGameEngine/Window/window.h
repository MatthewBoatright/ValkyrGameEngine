#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Valkyr { namespace Graphics {

	class ShellWindow
	{
	public:
		ShellWindow(char* windowName, int windowWidth, int windowHeight);
		~ShellWindow();

		void clear() const;
		void update();
		bool closed() const;
		void getCursorPosition(double & x, double & y);
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

	private:
		GLuint m_ProgramID;
		GLFWwindow * m_Window;
		const char * m_Title;
		int m_Width, m_Height;
		double m_CursorX, m_CursorY;

		bool init();
		void setWindowCallbacks();
		friend static void windowResized(GLFWwindow * window, int width, int height);
		friend static void keyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mod);
		friend static void mouseButtonCallback(GLFWwindow * window, int button, int action, int mod);
		friend static void cursorPositionCallback(GLFWwindow * window, double cursorX, double cursorY);
	};

} } 
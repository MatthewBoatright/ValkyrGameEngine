#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "controls.hpp"

namespace Valkyr { namespace Graphics {

	class ShellWindow
	{
	public:
		ShellWindow(char * windowName, int windowWidth, int windowHeight);
		~ShellWindow();

		void clear() const;
		void update();
		bool closed() const;
		inline void calculateFPS()
		{
			static double lastTime = glfwGetTime();
			static int nbFrames = 0;

			double currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0)
			{
				printf("%d FPS (%f ms/frame)\n", nbFrames, 1000.0 / double(nbFrames));
				nbFrames = 0;
				lastTime += 1.0;
			}
		}
	private:
		GLFWwindow * m_Window;

	};

} } 
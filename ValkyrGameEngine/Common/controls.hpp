#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <GLM/mat4x4.hpp>

void computeMatricesFromInputs(GLFWwindow * window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif
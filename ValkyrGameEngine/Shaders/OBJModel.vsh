#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in mat4 model_matrix;
// loc 4 occupied
// loc 5 occupied
// loc 6 occupied

int main()
{
	gl_Position = vec3(3);
}
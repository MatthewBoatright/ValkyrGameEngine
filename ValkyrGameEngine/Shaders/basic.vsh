#version 330 core

layout(location = 0) in vec3 vPosition_ModelSpace;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal_ModelSpace;

out DATA
{
	vec2 UV;
	vec3 Position_WorldSpace;
	vec3 Normal_CameraSpace;
	vec3 LightDirection_CameraSpace;
	vec3 EyeDirection_CameraSpace;
} v_OUT;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_WorldSpace;

void main()
{
	gl_Position = MVP * vec4(vPosition_ModelSpace, 1);
	
	v_OUT.Position_WorldSpace = (M * vec4(vPosition_ModelSpace, 1)).xyz;	
	
	vec3 vPosition_CameraSpace = (V * M * vec4(vPosition_ModelSpace, 1)).xyz;
	v_OUT.EyeDirection_CameraSpace = vec3(0, 0, 0) - vPosition_CameraSpace;	
	
	vec3 LightPosition_CameraSpace = (V * vec4(LightPosition_WorldSpace, 1)).xyz;
	v_OUT.LightDirection_CameraSpace = LightPosition_CameraSpace + v_OUT.EyeDirection_CameraSpace;	
	
	v_OUT.Normal_CameraSpace = (V * M * vec4(vNormal_ModelSpace, 0)).xyz;	
	
	v_OUT.UV = vUV;
}
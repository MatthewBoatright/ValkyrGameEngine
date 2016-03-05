#version 330 core

in DATA
{
	vec2 UV;
	vec3 Position_WorldSpace;
	vec3 Normal_CameraSpace;
	vec3 LightDirection_CameraSpace;
	vec3 EyeDirection_CameraSpace;
} f_IN;

out vec3 color;

uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_WorldSpace;

void main()
{
	vec3 LightColor = vec3(1, 1, 1);
	float LightPower = 50.0f;
	
	vec3 MaterialDiffuseColor = texture(myTextureSampler, f_IN.UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);
	
	float distance = length (LightPosition_WorldSpace - f_IN.Position_WorldSpace);
	
	vec3 n = normalize(f_IN.Normal_CameraSpace);
	vec3 l = normalize(f_IN.LightDirection_CameraSpace);
	float cosTheta = clamp(dot(n, l), 0, 1);
	
	vec3 E = normalize(f_IN.EyeDirection_CameraSpace);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E, R), 0, 1);
	
	color = MaterialAmbientColor + 
			MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance) + 
			MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance * distance);
}
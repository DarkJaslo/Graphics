#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec3 vfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 reflectionMatrix;

void main() 
{
	vfrontColor = color;
	gl_Position = modelViewProjectionMatrix * reflectionMatrix * vec4(vertex, 1.0);
}

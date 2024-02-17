#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float amplitude = 0.1;
uniform float freq = 1.0; // expressada en Hz
uniform float time;
const float PI = 3.14159;

void main()
{
    vec3 V = vertex + amplitude*sin(2*PI*time*freq) * normal;
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
}

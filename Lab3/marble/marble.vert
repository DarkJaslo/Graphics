#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

out vec4 objectVert;
out vec3 objectNorm;
out vec3 eyeNorm;
out vec4 eyePos;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    objectVert = vec4(vertex,1.0);
    objectNorm = normal;

    vec3 N = normalize(normalMatrix * normal);
    eyeNorm = N;
    eyePos = modelViewMatrix*vec4(vertex,1.0);

    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = projectionMatrix*eyePos;
}

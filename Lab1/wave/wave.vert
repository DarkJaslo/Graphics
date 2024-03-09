#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const float pi = 3.141592;
uniform float amp = 0.5;
uniform float freq = 0.25;
uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;

    float angle = amp*sin(vertex.y+2.0*pi*time*freq);
    mat3 waveMat = mat3(vec3(1.0,0.0,0.0),vec3(0.0,cos(angle),sin(angle)),vec3(0.0,-sin(angle),cos(angle)));

    gl_Position = modelViewProjectionMatrix * vec4(waveMat*vertex, 1.0);
}

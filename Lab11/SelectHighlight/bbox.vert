#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 scale;
uniform vec3 translate;

void main()
{
    vec3 V = vertex;
    frontColor = vec4(1,0,0,1);
    gl_Position = modelViewProjectionMatrix * vec4(scale* V + translate, 1.0);
}

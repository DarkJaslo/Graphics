#version 330 core
uniform float radius = 1.0;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
out vec2 vtexCoord;
out float factor;

void main() 
{
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.);
    vtexCoord = (4.0/radius)*(vertex.xy+vertex.zx);

    vec3 N = normalize(normalMatrix*normal);
    factor = N.z;
}

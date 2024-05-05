#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 vfrontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const vec4 red = vec4(1,0,0,1);
const vec4 green = vec4(0,1,0,1);
const vec4 blue = vec4(0,0,1,1);
const vec4 cyan = vec4(0,1,1,1);
const vec4 yellow = vec4(1,1,0,1);

vec4 cols[5];

//The color approximation should be done in the Geometry Shader. Didn't want to.

void main()
{
    cols[0] = vec4(1,0,0,1); //red
    cols[1] = vec4(0,1,0,1); //green
    cols[2] = vec4(0,0,1,1); //blue
    cols[3] = vec4(0,1,1,1); //cyan
    cols[4] = vec4(1,1,0,1); //yellow

    //vec3 N = normalize(normalMatrix * normal);
    vec4 col = vec4(color,1.0);

    int opt = 0;
    float mindist = distance(cols[0],col);

    for(int i = 1; i < 5; ++i)
    {
        float aux = distance(cols[i],col);
        if (aux < mindist)
        {
            opt = i;
            mindist = aux;
        }
    }

    vfrontColor = cols[opt];
    vtexCoord = texCoord;
    gl_Position = vec4(vertex, 1.0);
}

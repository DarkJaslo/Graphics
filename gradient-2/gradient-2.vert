#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const vec3 red = vec3(1.0,0.0,0.0);
const vec3 yellow = vec3(1.0,1.0,0.0);
const vec3 green = vec3(0.0,1.0,0.0);
const vec3 cyan = vec3(0.0,1.0,1.0);
const vec3 blue = vec3(0.0,0.0,1.0);

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vtexCoord = texCoord;

    vec4 position = modelViewProjectionMatrix*vec4(vertex,1.0);
    float y = position.y/position.w;
    
    float a = 4.0*((y+1.0)/2.0); 
    vec3 newCol;
    if(a >= 0.0 && a < 1.0) //Red-yellow
    {
        newCol = mix(red,yellow,fract(a));
    }
    else if(a >= 1.0 && a < 2.0) //Yellow-green
    {
        newCol = mix(yellow,green,fract(a));
    }   
    else if(a >= 2.0 && a < 3.0) //Green-cyan
    {
        newCol = mix(green,cyan,fract(a));
    }   
    else if(a >= 3.0 && a <= 4.0) //Cyan-blue
    {
        newCol = mix(cyan,blue,max(a-3.0,fract(a)));
    }   
    frontColor = vec4(newCol,1.0);

    gl_Position = position;
}

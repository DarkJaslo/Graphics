#version 330 core

//Procedural texture

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

const vec4 grey = vec4(0.8,0.8,0.8,1.0);
const vec4 black = vec4(0.0,0.0,0.0,1.0);

uniform float n = 8;

void main()
{

    float casella = 1.0/n;

    float posX = vtexCoord.x/casella;
    float posY = vtexCoord.y/casella;

    //int mod =  int(ceil(posX) + ceil(posY))%2;

    if(fract(posX) <= 0.1 || fract(posY) <= 0.1)
    {
        fragColor = black;
    }
    else
    {
        fragColor = grey;
    }
}

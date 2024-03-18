#version 330 core

//Procedural texture

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

const vec4 grey = vec4(0.8,0.8,0.8,1.0);
const vec4 black = vec4(0.0,0.0,0.0,1.0);

void main()
{

    const float casella = 1/8.0;

    float posX = vtexCoord.x/casella;
    float posY = vtexCoord.y/casella;

    int mod =  int(ceil(posX) + ceil(posY))%2;

    if(mod == 1)
    {
        fragColor = black;
    }
    else
    {
        fragColor = grey;
    }
}

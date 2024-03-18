#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

const vec4 white = vec4(1.0,1.0,1.0,1.0);
const vec4 red = vec4(1.0,0.0,0.0,1.0);

const vec2 CENTER = vec2(0.5,0.5);
const float RADIUS = 0.2;

void main()
{

    if(distance(vtexCoord,CENTER) < RADIUS)
    {
        fragColor = red;
    }
    else
    {
        fragColor = white;
    }
}

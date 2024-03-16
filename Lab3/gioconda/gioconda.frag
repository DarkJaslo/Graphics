#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D sampler;

const float RADIUS = 0.025;
const vec2 MOUTH = vec2(0.45,0.48);
const vec2 EYE = vec2(0.393,0.652);
const vec2 OFFSET = MOUTH-EYE;

uniform float time;

void main()
{
    vec2 tcoord = vtexCoord;

    if(fract(time) > 0.5)
    {
        if(distance(vtexCoord,EYE) <= RADIUS)
        {
            tcoord = vtexCoord+OFFSET;
        }
    }

    fragColor = texture(sampler,tcoord);
}

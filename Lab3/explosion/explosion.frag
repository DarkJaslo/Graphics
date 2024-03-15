#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D explosion;

void main()
{
    const float SLICE_TIME = 1.0/30.0;
    const int FRAMES = 48;

    int slice = int(mod(time/SLICE_TIME,FRAMES));

    float s = (slice%8);
    float t = (5-(slice/8)%6);

    vec2 tcoord = vec2((vtexCoord.s+s)/8, (vtexCoord.t+t)/6);
    vec4 col = texture(explosion,tcoord);
    fragColor = col*col.a;
}

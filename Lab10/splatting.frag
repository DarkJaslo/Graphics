#version 330 core

in vec2 vtexCoord;
in float factor;
out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
    vec4 grass = texture(grass2,vtexCoord);
    vec4 rock = texture(rock1,vtexCoord);
    vec4 noise = texture(noise0,vtexCoord);

    fragColor = factor*mix(rock,grass,noise.r);
}

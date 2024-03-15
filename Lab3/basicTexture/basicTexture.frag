#version 330 core

uniform sampler2D colorMap;
in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

void main()
{
    fragColor = frontColor * texture(colorMap, vtexCoord);
}

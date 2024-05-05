#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

uniform sampler2D tex0;

void main()
{
    fragColor = gfrontColor * texture(tex0,gtexCoord);
}

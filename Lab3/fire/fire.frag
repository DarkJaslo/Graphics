#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D foc0;
uniform sampler2D foc1;
uniform sampler2D foc2;
uniform sampler2D foc3;

uniform float slice=0.1;
uniform float time;

const int FRAMES = 4;

void main()
{
    int frame = int(mod(time/slice,FRAMES));

    if(frame==0){
        fragColor = texture(foc0,vtexCoord);
    }
    else if(frame==1){
        fragColor = texture(foc1,vtexCoord);
    }
    else if(frame==2){
        fragColor = texture(foc2,vtexCoord);
    }
    else{
        fragColor = texture(foc3,vtexCoord);
    }
}

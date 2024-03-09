#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;

    float angle = 0.0;
    vec4 newVertex = vec4(vertex,1.0);

    //Don't touch anything from the knees to the feet
    if(vertex.y >= 0.5)
    {
        angle = (vertex.y-0.5)*sin(time);

        //Move down to rotate approx. at the stomach's height
        mat4 transldown = mat4(
            vec4(1.0,0.0,0.0,0.0),
            vec4(0.0,1.0,0.0,0.0),
            vec4(0.0,0.0,1.0,0.0),
            vec4(0.0,-1.0,0.0,1.0)
        );
        mat4 rotMat = mat4(
            vec4(1.0,0.0,        0.0,       0.0),
            vec4(0.0, cos(angle),sin(angle),0.0),
            vec4(0.0,-sin(angle),cos(angle),0.0),
            vec4(0.0,0.0,        0.0,       1.0)
        );

        //Move human up to undo transformation
        mat4 translup = mat4(
            vec4(1.0,0.0,0.0,0.0),
            vec4(0.0,1.0,0.0,0.0),
            vec4(0.0,0.0,1.0,0.0),
            vec4(0.0,1.0,0.0,1.0)
        );
        newVertex = translup*rotMat*transldown*newVertex;
    }

    gl_Position = modelViewProjectionMatrix * newVertex;
}

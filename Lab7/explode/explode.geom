#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 normalOut[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

const float speed = 0.5;

void main( void )
{
	vec3 norm = vec3(0,0,0); 
	
	for( int i = 0 ; i < 3 ; i++ )
	{
		norm += normalOut[i];
	}

	norm /= 3;

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix* (gl_in[i].gl_Position + speed*time*vec4(norm,0));
		EmitVertex();
	}
    EndPrimitive();
}

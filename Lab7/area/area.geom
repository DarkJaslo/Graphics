#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

uniform mat4 projectionMatrix;

const float areamax = 0.0005;

const vec3 red = vec3(1,0,0);
const vec3 yellow = vec3(1,1,0);

void main( void )
{
	vec3 xz = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 xy = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;

	float value = (length(cross(xz,xy)))/(2*areamax);

	gfrontColor = vec4(mix(red,yellow,value),1);

	for( int i = 0 ; i < 3 ; i++ )
	{
		gl_Position = projectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}

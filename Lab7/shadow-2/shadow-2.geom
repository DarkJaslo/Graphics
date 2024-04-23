#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix* gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
	
	for( int i = 0; i < 3; i++)
	{
		gfrontColor = vec4(0,0,0,1);
		vec4 pos = gl_in[i].gl_Position;
		pos.y *= 0.01;
		pos.y += boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix* pos;
		EmitVertex();
	}
	EndPrimitive();

	if(gl_PrimitiveIDIn == 0)
	{
		vec3 diagVec = boundingBoxMax-boundingBoxMin;
		vec3 RVec = 0.5*diagVec;
		float R = length(RVec);
		vec3 centre = boundingBoxMin+RVec;
		float height = boundingBoxMin.y-0.01;

		gfrontColor = vec4(0,1,1,1);
		gl_Position = modelViewProjectionMatrix * vec4(centre.x-R,height,centre.z-R,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix *vec4(centre.x+R,height,centre.z-R,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix *vec4(centre.x-R,height,centre.z+R,1); EmitVertex();
		EndPrimitive();

		gl_Position = modelViewProjectionMatrix *vec4(centre.x+R,height,centre.z-R,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix *vec4(centre.x+R,height,centre.z+R,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix *vec4(centre.x-R,height,centre.z+R,1); EmitVertex();
		EndPrimitive();
	}
}

#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform float step = 0.25;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main( void )
{

	//Repeated computations are left for clarity. In a real use case, it would be best to optimize this

	vec4 baricenter = vec4(0,0,0,0);
	for( int i = 0 ; i < 3 ; i++ )
	{
		baricenter+=gl_in[i].gl_Position;
	}
	baricenter /= 3;
	vec4 center = vec4(0,0,0,1);

	center.x = step*round(baricenter.x/step);
	center.y = step*round(baricenter.y/step);
	center.z = step*round(baricenter.z/step);

	vec4 color = vec4(0.5,0.5,0.5,1.0);
	
	//Cara lateral 1
	gfrontColor = color*normalize(normalMatrix*vec3(0,0,-1)).z;
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2,-step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara lateral 2
	gfrontColor = color*normalize(normalMatrix*vec3(1,0,0)).z;
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2, step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara lateral 3
	gfrontColor = color*normalize(normalMatrix*vec3(0,0,1)).z;
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2, step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara lateral 4
	gfrontColor = color*normalize(normalMatrix*vec3(-1,0,0)).z;
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2,-step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara arriba
	gfrontColor = color*normalize(normalMatrix*vec3(0,1,0)).z;
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2, step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara abajo
	gfrontColor = color*normalize(normalMatrix*vec3(0,-1,0)).z;
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2, step/2, 0)); EmitVertex();
	EndPrimitive();
}

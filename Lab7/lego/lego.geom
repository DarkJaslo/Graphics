#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec2 vtexCoord[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform float step = 0.25;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main( void )
{
	//Repeated computations are left for clarity. In a real use case, it would be best to optimize this

	vec4 baricenter = vec4(0,0,0,0);
	vec4 color = vec4(0);
	vec2 texCoord = vec2(0);
	for( int i = 0 ; i < 3 ; i++ )
	{
		color += vfrontColor[i];
		baricenter+=gl_in[i].gl_Position;
		texCoord += vtexCoord[i];
	}
	texCoord /= 3;
	color /= 3;
	baricenter /= 3;
	vec4 center = vec4(0,0,0,1);

	center.x = step*round(baricenter.x/step);
	center.y = step*round(baricenter.y/step);
	center.z = step*round(baricenter.z/step);

	gtexCoord = vec2(0);
	
	//Cara lateral 1
	gfrontColor = color;
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2,-step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara lateral 2
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2, step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara lateral 3
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2, step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara lateral 4
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2,-step/2, 0)); EmitVertex();
	EndPrimitive();

	//Cara arriba
	gtexCoord = vec2(0,0);
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2,-step/2, 0)); EmitVertex();
	gtexCoord = vec2(0,1);
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2, step/2, step/2, 0)); EmitVertex();
	gtexCoord = vec2(1,0);
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2,-step/2, 0)); EmitVertex();
	gtexCoord = vec2(1,1);
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2, step/2, step/2, 0)); EmitVertex();
	EndPrimitive();

	gtexCoord = vec2(0);

	//Cara abajo
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4(-step/2,-step/2, step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2,-step/2, 0)); EmitVertex();
	gl_Position = modelViewProjectionMatrix * (center + vec4( step/2,-step/2, step/2, 0)); EmitVertex();
	EndPrimitive();
}

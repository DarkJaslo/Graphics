#version 330 core
in vec3 vfrontColor;
out vec4 fragColor;
uniform sampler2D colorMap;
uniform float SIZE;

uniform bool doreflect;

const vec4 grey = vec4(vec3(0.5),1);

void main() 
{
	if (doreflect) {
		vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
		fragColor = mix(grey,texture2D(colorMap,st),0.5);
		return;
	} 
	fragColor = vec4(vfrontColor, 1);
}

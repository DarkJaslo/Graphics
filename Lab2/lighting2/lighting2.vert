#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition; //in eye space

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

vec4 Ambient() {
    return lightAmbient * matAmbient;
}

vec4 Diffuse (vec3 NEye, vec3 L, vec4 light) 
{
    // Assumes normalized inputs
    vec4 result = vec4(0);
    if (dot (L, NEye) > 0)
      result = light * matDiffuse * dot (L,NEye);
    return (result);
}

vec4 Specular (vec3 NEye, vec3 L, vec4 eyePos, vec3 light) 
{
    // Assumes normalized inputs
    vec4 result = vec4 (0);
    // Avoid subtracting light
    if ((dot(NEye,L) < 0) || (matShininess == 0))
      return result;  // No reflections

    vec3 R = reflect(-L, NEye); // equivalent to 2.0*dot(NEye,L)*NEye - L;
    vec3 V = normalize(-eyePos.xyz); // the camera is (0,0,0) in eye space

    if (dot(R, V) < 0)
      return result;  // No reflections
    
    float shine = pow(max(0.0, dot(R,V)), matShininess);
    return (matSpecular * vec4(light,0) * shine); 
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vec4 position = modelViewMatrix*vec4(vertex,1.0);
    vec3 L = normalize(lightPosition.xyz - position.xyz);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;

    frontColor = Ambient() + Diffuse(N,L,vec4(1.0,1.0,1.0,1.0)) + Specular(N,L,position,vec3(1.0,1.0,1.0)); 
    gl_Position = projectionMatrix * position;
}

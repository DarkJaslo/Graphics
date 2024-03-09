#version 330 core

in vec4 frontColor;
in vec3 NEye;
in vec3 vertEye;

out vec4 fragColor;

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

vec4 Specular (vec3 NEye, vec3 L, vec3 eyePos, vec3 light) 
{
    // Assumes normalized inputs
    vec4 result = vec4 (0);
    // Avoid subtracting light
    if ((dot(NEye,L) < 0) || (matShininess == 0))
      return result;  // No reflections

    vec3 R = reflect(-L, NEye); // equivalent to 2.0*dot(NEye,L)*NEye - L;
    vec3 V = normalize(-eyePos); // the camera is (0,0,0) in eye space

    if (dot(R, V) < 0)
      return result;  // No reflections
    
    float shine = pow(max(0.0, dot(R,V)), matShininess);
    return (matSpecular * vec4(light,0) * shine); 
}

void main()
{
    vec3 N = normalize(NEye);
    vec3 L = normalize(lightPosition.xyz-vertEye);
    const vec4 light = vec4(1.0,1.0,1.0,1.0);

    fragColor = Ambient() + Diffuse(N,L,light) + Specular(N,L,vertEye,light.xyz);
}

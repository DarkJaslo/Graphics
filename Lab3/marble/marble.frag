#version 330 core

in vec4 frontColor;
in vec4 objectVert;
in vec3 objectNorm;
in vec3 eyeNorm;
in vec4 eyePos;
out vec4 fragColor;

uniform sampler2D noiseSmooth;

const vec4 splane = vec4(0.0,0.3,-0.3,0.0);
const vec4 tplane = vec4(0.3*-2.0,-0.3,0.3,0.0);

const vec4 white = vec4(1.0,1.0,1.0,1.0);
const vec4 redish = vec4(0.5,0.2,0.2,1.0);

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {
 vec3 lightPos = vec3(0.0,0.0,2.0);
 vec3 L = normalize( lightPos - Pos );
 vec3 V = normalize( -Pos);
 vec3 R = reflect(-L,N);
 float NdotL = max( 0.0, dot( N,L ) );
 float RdotV = max( 0.0, dot( R,V ) );
 float Ispec = pow( RdotV, 20.0 );
 return diffuse * NdotL + Ispec;
}


void main()
{
    float s = dot(splane,objectVert);
    float t = dot(tplane,objectVert);

    vec4 sample = texture(noiseSmooth,vec2(s,t));

    float v = sample.r;
    
    vec4 dif;

    if(v <= 0.5)
    {
        dif = mix(white,redish,2*v);
    }
    else
    {
        dif = mix(redish,white,2*(v-0.5));
    }

    vec3 norm = normalize(eyeNorm);



    fragColor = shading(norm,eyePos.xyz,dif);
}

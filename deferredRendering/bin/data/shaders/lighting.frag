#version 330 core

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
const int LightNUM=3;

uniform Light light[LightNUM];
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gDepth;
uniform sampler2D ssao;

uniform vec3 viewPos;
uniform int DebugMode;
uniform float farClip;

in vec2 TexCoord;

out vec4 color;

float DecodeDepth(in float depth,in float farClip)
{
    return depth*farClip;
}

void main()
{
    vec3 position=texture(gPosition,TexCoord).xyz;
    vec3 normal=texture(gNormal,TexCoord).xyz;
    vec3 albedo=texture(gAlbedo,TexCoord).rgb;
    vec3 depth=texture(gDepth,TexCoord).xyz;
    
    float AmbientOcculusion=texture(ssao,TexCoord).r*1.5;
    
    // float viewSpaceDepth=DecodeDepth(depth.x,farClip);
    vec3 lighting=vec3(0.,0.,0.);
    
    for(int i=0;i<LightNUM;i++)
    {
        float distance=length(light[i].position-position);
        if(distance<3000)
        {
            //Ambient
            vec3 ambient=albedo*AmbientOcculusion;
            // vec3 ambient=albedo;
            
            //Diffuse
            vec3 lightDir=normalize(light[i].position-position);
            vec3 diffuse=max(dot(normal,lightDir),0.)*light[i].diffuse;
            
            //Specular
            vec3 viewDir=normalize(viewPos-position);
            vec3 halfwayDir=normalize(lightDir+viewDir);
            float spec=pow(max(dot(normal,halfwayDir),0.),30.);
            vec3 specular=light[i].specular*spec;
            
            //Attenuation
            float dist=length(light[i].position-position)*1.;
            float attenuation=1.+(.1*dist)+(.01*dist*dist);
            
            ambient/=attenuation;
            diffuse/=attenuation;
            specular/=attenuation;
            lighting+=ambient+diffuse+specular;
        }
    }
    
    if(DebugMode==0)
    {
        color=vec4(position,1.);
    }
    
    else if(DebugMode==1)
    {
        color=vec4(normal,1.);
    }
    
    else if(DebugMode==2)
    {
        color=vec4(albedo,1.);
    }
    
    else if(DebugMode==3){
        color=vec4(depth.x,depth.x,depth.x,1.);
    }
    
    else if(DebugMode==4){
        color=vec4(lighting,1.);
    }
    
}

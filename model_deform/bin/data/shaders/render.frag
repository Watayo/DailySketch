#version 150
precision mediump float;

uniform mat4 invMat;
uniform vec3 lightPos;
uniform float lightAttenuation;
uniform vec3 eyePos;
uniform vec4 ambientCol;
uniform float time;

in vec3 gsPosition;
in vec3 gsNormal;
in vec4 gsColor;

out vec4 outputColor;

void main()
{
    vec3 lightVec = lightPos - gsPosition;
    float lightLen = length(lightVec);

    float attenuation =  1.0 / (lightAttenuation * lightLen);

    vec3 invLight = normalize(invMat * vec4(lightVec, 0.0)).xyz;

    vec3 invEye = normalize(invMat * vec4(eyePos, 0.0)).xyz;
    vec3 halfLE=normalize(invLight+invEye);

    float diffuse=clamp(dot(gsNormal,invLight),0.,.8)+.1;

    float specular=pow(clamp(dot(gsNormal,halfLE),0.1,.9), 50.0);

    vec4 diffuseColor = vec4(1.0);
    vec4 specularColor =vec4(1.0);

    // vec4 destColor=vColor*vec4(vec3(diffuse),1.)+specular+ambientCol;
    vec4 destColor=gsColor*diffuseColor*diffuse*attenuation+specular*specularColor*attenuation+ambientCol;
    outputColor=destColor;
    // outputColor = gsColor;
}

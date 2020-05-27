#version 150

uniform vec3 eyePosition;
uniform samplerCube cubeTexture;
uniform mat4 invMatrix;
//uniform bool reflection;

in vec3 vPosition;
in vec3 vNormal;
in vec4 vColor;

const vec3 lightDir=vec3(0.,0.,-1.);

out vec4 fragColor;

void main() {
  vec3 invLight=normalize(invMatrix*vec4(lightDir,0.)).xyz;
  vec3 invEye=normalize(invMatrix*vec4(vPosition-eyePosition,0.)).xyz;
  vec3 halfLE=normalize(invLight+invEye);
  float diffuse=clamp(abs(dot(vNormal,invLight)),0.,1.);
  float specular=pow(clamp(dot(vNormal,halfLE),0.,1.),150.);

  vec3 I=normalize(eyePosition-vPosition);
  vec3 R=reflect(I,normalize(vNormal));// 反射

  vec3 envColor = texture(cubeTexture, R).rgb;
  vec4 ambientColor = vec4(envColor * 0.7, 1.0);
  vec4 destColor=vec4(envColor,1.)*vec4(vec3(diffuse),1.)+vec4(vec3(specular),1.)+ambientColor;
  fragColor = destColor;
}
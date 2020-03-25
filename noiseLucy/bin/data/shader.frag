#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform float time;
varying vec3 normal;
varying vec3 vertex;
varying vec3 lightDirection;

void main() {
  float light = abs(dot(normalize(-normal), normalize(-lightDirection)));

  vec3 color = vec3(light);
  gl_FragColor = vec4(color, 1.0);
}

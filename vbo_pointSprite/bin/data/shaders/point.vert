#version 120

uniform float size;
uniform mat4 mvp;

void main() {
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  float sizes = length(gl_Normal.xyz) * 10.0;
  gl_PointSize = 100 * ( sizes * size);
  gl_FrontColor = gl_Color;
}

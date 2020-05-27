#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

in vec4 position;
in vec2 texcoord;
in vec3 normal;
in vec4 color;

out vec3 vPosition;
out vec3 vNormal;
out vec4 vColor;

void main() {
  vPosition = position.xyz;
  vNormal = normal;
  vColor = color;
  gl_Position = modelViewProjectionMatrix * vec4(vPosition, 1.0);

}

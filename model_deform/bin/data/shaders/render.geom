#version 150
precision mediump float;

layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat3 normalMat;
uniform mat4 projectionMat;
uniform mat4 mvpMat;
uniform int scale;
uniform int NormalMode;

in vec3 vNormal[];
in vec4 vColor[];
in vec3 vPosition[];

out vec3 gsNormal;
out vec3 gsPosition;
out vec4 gsColor;

void main(){
  vec3 faceEdgeA=vPosition[1]-vPosition[0];
  vec3 faceEdgeB=vPosition[2]-vPosition[0];
  vec3 faceNormal=normalize(cross(faceEdgeA,faceEdgeB));
  vec3 offset;
  if(NormalMode==0){
    offset=faceNormal * scale;
  }

  for(int i=0;i<gl_in.length();i++) {
    if(NormalMode==1){
      offset= vNormal[i] * -scale * i;
    }
    gl_Position=mvpMat*vec4(vPosition[i]+(offset.xyz),1.);
    gsPosition= (modelMat*vec4(vPosition[i],1.)).xyz;
    gsNormal=normalMat * vNormal[i];
    gsColor=vColor[i];
    EmitVertex();
  }
  EndPrimitive();
}

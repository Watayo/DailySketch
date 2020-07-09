#version 150
precision mediump float;

uniform mat4 modelMat;
uniform mat4 mvpMat;
uniform mat3 normalMat;
uniform float time;
uniform vec4 uniColor;
uniform float power;
uniform int deformAngle;

in vec3 position;
in vec4 color;
in vec3 normal;

out vec3 vPosition;
out vec3 vNormal;
out vec4 vColor;

mat3 translate(float x=1, float y=1 , float z=1) {
    return mat3(x, 0, 0, 0, y, 0, 0, 0, z);
}

mat3 rotateX(float theta){
    float s = sin(theta);
    float c = cos(theta);
    return mat3(0,1,0,s,0,c,-s,0,c);
}

mat3 rotateY(float theta) {
    float s=sin(theta);
    float c=cos(theta);
    return mat3(c,0,s,0,1,0,-s,0,c);
}

mat3 rotateZ(float theta) {
    float s=sin(theta);
    float c=cos(theta);
    return mat3(s,0,c,-s,0,c,0,1,0);
}

void main(){
    // float theta = power * (time+position.y/deformAngle) ;
    // float angle = sin(theta);
    // mat3 m = rotateY(angle);
    float pos = position.y;
    if(pos/100)

    mat3 m = translate(pos, 1, 1);

    vec3 transformed = m * position;
    vPosition=transformed;
    vNormal=normal;

    // vColor = vec4(0.0784, 0.8627, 1.0, 1.0);
    vColor = uniColor;

    // gl_Position=mvpMat*vec4(transformed,1.);

}

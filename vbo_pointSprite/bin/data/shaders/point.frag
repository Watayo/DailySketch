#version 120

uniform sampler2D tex;

void main() {
  //if(texture2D(tex, gl_TexCoord[0].st).a < 0.5) {
    // discard;
  //}
  
  gl_FragColor = gl_Color * texture2D(tex, gl_TexCoord[0].st);
}

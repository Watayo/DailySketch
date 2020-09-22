#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec3 Position;
out vec3 Normal;
out float ViewSpaceDepth;
out vec2 TexCoord;

void main()
{
    
    Position=(view*model*vec4(position,1.)).xyz;
    Normal=normalize((view*model*vec4(normal,0.)).xyz);
    
    // view-space depth
    ViewSpaceDepth=(view*model*vec4(position,1.)).z;
    
    TexCoord=texcoord;
    
    gl_Position=projection*view*model*vec4(position,1.);
}

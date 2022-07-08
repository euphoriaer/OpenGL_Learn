#version 330 core
out vec4 FragColor;
in vec4 vertexcolor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;
uniform vec3 ambientColor;//环境色
uniform vec3 objColor;

void main() 
{
   //FragColor = vertexcolor;
   //FragColor=texture(ourTexture,TexCoord)*texture(ourFace,TexCoord);
   FragColor=vec4(objColor*ambientColor,1.0);
}
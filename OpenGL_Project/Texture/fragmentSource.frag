#version 330 core
out vec4 FragColor;
in vec4 vertexcolor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;

uniform vec4 ourColor;

void main() 
{
   //FragColor = vertexcolor;
   FragColor=texture(ourTexture,TexCoord)*texture(ourFace,TexCoord);
}
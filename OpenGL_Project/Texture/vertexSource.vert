#version 330 core
layout (location = 3) in vec3 aPos;
layout (location = 4) in vec3 aColor;
layout (location = 5) in vec2 aTexCoord;


out vec4 vertexcolor;//顶点传出的参数，片元着色器接收要同参数名，参数名不同，无法接受数值，且不报错
out vec2 TexCoord;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   vertexcolor =vec4(aColor.x,aColor.y,aColor.z,1.0);
   TexCoord=aTexCoord;
}

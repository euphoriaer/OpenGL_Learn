#version 330 core
layout (location = 3) in vec3 aPos;

layout (location = 9) in vec3 aNormal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectMat;


out vec3 Normal;
out vec3 FragPos;
void main()
{
   gl_Position = projectMat * viewMat * modelMat * vec4(aPos.xyz, 1.0);//从左往右变换
 
   FragPos=(modelMat * vec4(aPos.xyz, 1.0)).xyz;
   Normal=mat3(transpose(inverse(modelMat)))*aNormal;
   //不匀称缩放    transpose(inverse(modelMat) 运算量大，
   //如果没有需求，不要用，最好物体就是1，1，1或匀称缩放
}

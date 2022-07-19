#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 uvTexcoord;


uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectMat;

uniform float uvTime;
uniform float sinTime;

out vec3 Normal;
out vec3 FragPos;
out vec2 Texcoord;
out float Time;

void main()
{
  
   //vec3 vertPos=vec3(aPos.xyz)*sinTime;
   vec3 vertPos=vec3(aPos.xyz);
   gl_Position = projectMat * viewMat * modelMat * vec4(vertPos, 1.0);//从左往右变换
 
   FragPos=(modelMat * vec4(aPos.xyz, 1.0)).xyz;
   Normal=mat3(transpose(inverse(modelMat)))*aNormal;

   Texcoord=uvTexcoord;
   Time=uvTime;
   //不匀称缩放    transpose(inverse(modelMat) 运算量大，
   //如果没有需求，不要用，最好物体就是1，1，1或匀称缩放
}

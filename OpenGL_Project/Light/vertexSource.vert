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
   gl_Position = projectMat*viewMat*modelMat*vec4(aPos.xyz, 1.0);//从左往右变换
   Normal=mat3(modelMat)*aNormal;
//   vertexcolor =vec4(aColor.x,aColor.y,aColor.z,1.0);
//   TexCoord=aTexCoord;
}

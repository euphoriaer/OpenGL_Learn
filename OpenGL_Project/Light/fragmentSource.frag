#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 ambientColor;//环境色
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 FragColor;
void main() 
{
   vec3 lightDir=normalize(lightPos-FragPos);

   vec3 diffuse=dot(lightDir,Normal)*lightColor;

   FragColor=vec4((diffuse+ambientColor)*objColor,1.0);
}
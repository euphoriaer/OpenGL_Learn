#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 ambientColor;//环境色
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
out vec4 FragColor;
void main() 
{
   vec3 lightDir=normalize(lightPos-FragPos);
   vec3 reflectVec=reflect(-lightDir,Normal);
   vec3 cameraVec=normalize(cameraPos-FragPos);
   
   float speclarAmount=dot(reflectVec,cameraVec);

   vec3 speclar= pow( max(speclarAmount,0),32) * lightColor;

   vec3 diffuse=max(dot(lightDir,Normal),0 ) * lightColor;

   FragColor=vec4((diffuse+ambientColor+speclar)*objColor,1.0);
} 
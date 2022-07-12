#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 Texcoord;

struct Material
{
 vec3 ambiend;
 sampler2D diffuse;
 vec3 specular;
 float shininess;
};

uniform Material material;

uniform vec3 objColor;
uniform vec3 ambientColor;
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

   vec3 speclar=material.specular * (pow(max(speclarAmount,0),material.shininess)) * lightColor;

   vec3 diffuse=texture(material.diffuse,Texcoord).xyz * max(dot(lightDir,Normal),0 ) * lightColor;
   //vec3 diffuse=texture(material.diffuse,Texcoord).xyz;

   vec3 anbient=texture(material.diffuse,Texcoord).xyz *material.ambiend*ambientColor;

   FragColor=vec4((diffuse+anbient+speclar)*objColor,1.0);
} 
#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 Texcoord;
in float Time;


struct LightPoint
{
float constant ;
float linear ;
float quadratic;

};


struct LightSpot
{
float cosPhyInner;
float cosPhyOut;
};

struct Material
{
 vec3 ambiend;
 sampler2D diffuse;
 sampler2D specular;
 sampler2D emissive;
 float shininess;
};

uniform Material material;
uniform LightPoint lightP;
uniform LightSpot lightS;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

out vec4 FragColor;
void main() 
{

   float dist=length(lightPos-FragPos);
   float attenuation=1.0 / (lightP.constant+lightP.linear*dist+lightP.quadratic*(dist*dist));//点光源衰减

   vec3 lightDir=normalize(lightPos-FragPos);
   vec3 reflectVec=reflect(-lightDir,Normal);
   vec3 cameraVec=normalize(cameraPos-FragPos);
   
   float speclarAmount=dot(reflectVec,cameraVec);

   vec3 speclar=texture(material.specular,Texcoord).xyz * (pow(max(speclarAmount,0),material.shininess)) * lightColor;

   vec3 diffuse=texture(material.diffuse,Texcoord).xyz * max(dot(lightDir,Normal),0 ) * lightColor;
   //vec3 diffuse=texture(material.diffuse,Texcoord).xyz;

   vec3 anbient=texture(material.diffuse,Texcoord).xyz *material.ambiend*ambientColor;

   float cosTheta=dot(normalize(FragPos-lightPos),-lightDirUniform);
   if(cosTheta>lightS.cosPhyInner)
   {
      //inside
      FragColor=vec4((diffuse+(anbient+speclar)*1.0f)*objColor,1.0);


   }else  if(cosTheta>lightS.cosPhyOut)
   {
     //mid
     FragColor=vec4((diffuse+(anbient+speclar)*0.5f)*objColor,1.0);
   }
   else
   {
      FragColor=vec4((diffuse+(anbient+speclar)*0.0f)*objColor,1.0);
     //outside
   }

   
//自发光

//   float  emissivePow=1.8f;
//   float  uvSpeed=0.1;
//
//   //uv流动
//   vec2 uv=vec2(Texcoord.x+Time,Texcoord.y+Time);
//
//   //vec3 emissive=texture(material.emissive,uv).xyz * pow(max(speclarAmount,0),emissivePow);
//   vec3 emissive=texture(material.emissive,uv).xyz * emissivePow;
//
//   FragColor=vec4((diffuse+(anbient+speclar))*attenuation*objColor+emissive,1.0);
   //FragColor=vec4(emissive,1.0);
} 
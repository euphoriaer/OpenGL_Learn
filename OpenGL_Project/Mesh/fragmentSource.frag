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
   float spotRatio;
   if(cosTheta>lightS.cosPhyInner)
   {
      //inside
      spotRatio=1.0f;

   }else  if(cosTheta>lightS.cosPhyOut)
   {
     //mid
     //cosTheta 判断当前片元处于聚光灯边缘哪个位置(判断与Inner距离，也可以判断与Out距离，cosTheta 一定处于两者之间)
     //，根据Inner Out 范围光滑过度

     //spotRatio=1.0f-(cosTheta-lightS.cosPhyInner)/(lightS.cosPhyOut-lightS.cosPhyInner);
     spotRatio=(lightS.cosPhyOut-cosTheta)/(lightS.cosPhyOut-lightS.cosPhyInner);
   }
   else
   {
     //outs
     spotRatio=0;
     
   }
   FragColor=vec4((anbient+(diffuse+speclar)*spotRatio)*objColor,1.0);
   
} 
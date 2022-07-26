#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 Texcoord;
in float Time;


struct LightDirectional
{
vec3 pos;
vec3 color;
vec3 dirToLight;
};

struct LightPoint
{
vec3 pos;
vec3 color;
vec3 dirToLight;
float constant;
float linear;
float quadratic;

};


struct LightSpot
{
vec3 pos;
vec3 color;
vec3 dirToLight;
float constant;
float linear;
float quadratic;
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
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;
uniform LightDirectional lightDir;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 cameraPos;

out vec4 FragColor;

vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera)
{

    //diffuse 
   float diffIntensity=max(dot(light.dirToLight,uNormal),0);

   vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,Texcoord).rgb;

   //speclar
   vec3 R=normalize(reflect(-light.dirToLight,uNormal));
   float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess);
   vec3 specColor=specIntensity*light.color*texture(material.specular,Texcoord).rgb;

   vec3 result=diffColor+specColor;

   //result=vec3(0,0,1.0);
    return result;
}

vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera)
{
//attenuation 点光源衰减
float dist=length(light.pos-FragPos);
float atttenuation=1/(light.constant+light.linear*dist+light.quadratic*(dist*dist));


//diffuse
float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*atttenuation;
vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,Texcoord).rgb;


//speclar
   vec3 R=normalize(reflect(-normalize(light.pos-FragPos),uNormal));
   float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess)*atttenuation;
   vec3 specColor=specIntensity*light.color*texture(material.specular,Texcoord).rgb;

vec3 result=diffColor+specColor;


return result;
}
vec3 CalcLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera)
{


//attenuation 光源衰减
float dist=length(light.pos-FragPos);
float atttenuation=1/(light.constant+light.linear*dist+light.quadratic*(dist*dist));

float spotRatio=0;
float CosTheta=dot(normalize(FragPos-light.pos),-light.dirToLight);

if(CosTheta>light.cosPhyInner)
{
    spotRatio=1.0;
}else if(CosTheta>light.cosPhyOut)
{
   spotRatio=(CosTheta-light.cosPhyOut)/(light.cosPhyInner-light.cosPhyOut);
}else
{
spotRatio=0;
}
//diffuse
float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*atttenuation*spotRatio;
vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,Texcoord).rgb;


//speclar
   vec3 R=normalize(reflect(-normalize(light.pos-FragPos),uNormal));
   float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess)*atttenuation*spotRatio;
   vec3 specColor=specIntensity*light.color*texture(material.specular,Texcoord).rgb;

vec3 result=diffColor+specColor;


return result;
}
void main() 
{
        vec3 finalResult=vec3(0,0,0);
        vec3 uNormal=normalize(Normal);
        vec3 dirToCamera=normalize(cameraPos-FragPos);

        finalResult+=CalcLightDirectional(lightDir,uNormal,dirToCamera);

        finalResult+=CalcLightPoint(lightP0,uNormal,dirToCamera);
        finalResult+=CalcLightPoint(lightP1,uNormal,dirToCamera);
        finalResult+=CalcLightPoint(lightP2,uNormal,dirToCamera);
        finalResult+=CalcLightPoint(lightP3,uNormal,dirToCamera);

        finalResult+=CalcLightSpot(lightS,uNormal,dirToCamera);
        FragColor=vec4(finalResult,1);
} 
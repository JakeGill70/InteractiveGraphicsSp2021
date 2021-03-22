#version 400
in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragPosition;
in vec2 fragTexCoord;

out vec4 color;

uniform float materialAmbientIntensity;
uniform float materialSpecularIntensity;
uniform float materialShininess;

uniform vec3 viewPosition;

uniform vec3 globalLightPosition;
uniform vec3 globalLightColor;
uniform float globalLightIntensity;

uniform int numberOfLights;
uniform vec3 localLightPosition[10];
uniform vec3 localLightColor[10];
uniform float localLightIntensity[10];
uniform float localLightAttenuationCoefficient[10];

uniform sampler2D tex;

vec4 calculateTotalLocalDiffuse();
vec4 calculateDiffuse(vec3 lightDir, vec3 unitNormal, float lightIntensity, vec3 lightColor);
vec4 calculateTotalSpecular();

void main()
{
   vec3 toGlobalLightDir = normalize(globalLightPosition - fragPosition);
   vec4 globalDiffuse = calculateDiffuse(
      toGlobalLightDir, fragNormal, globalLightIntensity, globalLightColor);

   vec4 totalLocalDiffuse = calculateTotalLocalDiffuse();

   vec4 totalSpecular = calculateTotalSpecular();

   vec4 texFragColor = texture(tex, fragTexCoord) * fragColor;
   vec4 ambientColor = materialAmbientIntensity * vec4(1.0f, 1.0f, 1.0f, 1.0f);
   color = 
      (ambientColor + totalLocalDiffuse + globalDiffuse + totalSpecular) 
      * texFragColor;

   // Gamma correction
   float gamma = 1.0/2.2;
   color.r = pow(color.r, gamma);
   color.g = pow(color.g, gamma);
   color.b = pow(color.b, gamma);
}

vec4 calculateTotalLocalDiffuse()
{
   vec4 totalLocalDiffuse, localDiffuse;
   vec3 toLocalLightDir;
   float distanceToLight, attenuation;

   for(int i = 0; i < numberOfLights; i++){
      toLocalLightDir = normalize(localLightPosition[i] - fragPosition);
      localDiffuse = calculateDiffuse(
         toLocalLightDir, fragNormal, localLightIntensity[i], localLightColor[i]);

      distanceToLight = length(localLightPosition[i] - fragPosition);
      attenuation = 1.0 
         / (1.0 + localLightAttenuationCoefficient[i] * pow(distanceToLight, 2));
      totalLocalDiffuse += (attenuation * localDiffuse);
   }
   return totalLocalDiffuse;
}

vec4 calculateDiffuse(vec3 lightDir, vec3 unitNormal, float lightIntensity, vec3 lightColor)
{
   float cosAngIncidence = dot(unitNormal, lightDir);
   cosAngIncidence = clamp(cosAngIncidence, 0.0f, 1.0f);
   return cosAngIncidence * lightIntensity * vec4(lightColor, 1.0f);
}

vec4 calculateTotalSpecular()
{
   vec3 toLocalLightDir;
   vec3 reflectDir;
   float angIncidence, specular;
   vec4 totalSpecular;
   vec3 viewDir;
   for(int i = 0; i < numberOfLights; i++){
      if(materialShininess > 0.0f){
         toLocalLightDir = normalize(localLightPosition[i] - fragPosition);
         viewDir = normalize(viewPosition - fragPosition);
         reflectDir = reflect(-toLocalLightDir, fragNormal);
         angIncidence = max(dot(viewDir, reflectDir), 0.0f);
         specular = pow(angIncidence, materialShininess);
         totalSpecular += 
            materialSpecularIntensity * specular * localLightIntensity[i] 
            * vec4(localLightColor[i], 1.0f); 
      }
   }

   return totalSpecular;
}

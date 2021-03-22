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

uniform vec3 localLightPosition;
uniform vec3 localLightColor;
uniform float localLightIntensity;
uniform float localLightAttenuationCoefficient;

uniform sampler2D tex;

vec4 calculateDiffuse(vec3 lightDir, vec3 unitNormal, float lightIntensity, vec3 lightColor);
vec4 calculateSpecular(vec3 toLocalLightDir);

void main()
{
   vec3 toGlobalLightDir = normalize(globalLightPosition - fragPosition);
   vec4 globalDiffuse = calculateDiffuse(
      toGlobalLightDir, fragNormal, globalLightIntensity, globalLightColor);

   vec3 toLocalLightDir = normalize(localLightPosition - fragPosition);
   vec4 localDiffuse = calculateDiffuse(
      toLocalLightDir, fragNormal, localLightIntensity, localLightColor);

   float distanceToLight = length(localLightPosition - fragPosition);
   float attenuation = 1.0 
      / (1.0 + localLightAttenuationCoefficient * pow(distanceToLight, 2));

   vec4 totalSpecular = calculateSpecular(toLocalLightDir);

   vec4 texFragColor = texture(tex, fragTexCoord) * fragColor;
   vec4 ambientColor = materialAmbientIntensity * vec4(1.0f, 1.0f, 1.0f, 1.0f);
   color = 
      (ambientColor + (localDiffuse * attenuation) + globalDiffuse 
         + totalSpecular) 
      * texFragColor;

   // Gamma correction
   float gamma = 1.0/2.2;
   color.r = pow(color.r, gamma);
   color.g = pow(color.g, gamma);
   color.b = pow(color.b, gamma);
}

vec4 calculateDiffuse(vec3 lightDir, vec3 unitNormal, float lightIntensity, vec3 lightColor)
{
   float cosAngIncidence = dot(unitNormal, lightDir);
   cosAngIncidence = clamp(cosAngIncidence, 0.0f, 1.0f);
   return cosAngIncidence * lightIntensity * vec4(lightColor, 1.0f);
}

vec4 calculateSpecular(vec3 toLocalLightDir)
{
   vec3 reflectDir;
   float angIncidence, specular;
   vec4 totalSpecular;
   vec3 viewDir;
   if(materialShininess > 0.0f){
      viewDir = normalize(viewPosition - fragPosition);
      reflectDir = reflect(-toLocalLightDir, fragNormal);
      angIncidence = max(dot(viewDir, reflectDir), 0.0f);
      specular = pow(angIncidence, materialShininess);
      totalSpecular += 
         materialSpecularIntensity * specular * localLightIntensity 
         * vec4(localLightColor, 1.0f); 
   }
   return totalSpecular;
}

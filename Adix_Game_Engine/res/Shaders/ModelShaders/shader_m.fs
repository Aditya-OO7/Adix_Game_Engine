#version 330 core

struct Material
{
	//sampler2D diffuse;
	//sampler2D specular;

	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_normal1;
	sampler2D texture_height1;

	float shininess;
};

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 lightColor;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

uniform Material material;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform vec3 viewPos;

//uniform Light light;
//uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform vec3 lightPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 aTex, vec3 dTex, vec3 sTex);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 aTex, vec3 dTex, vec3 sTex);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 dTex, vec3 sTex);

void main()
{
	vec3 norm = normalize(Normal);

	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 ambientTex = vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 diffuseTex = vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 specularTex = vec3(texture(material.texture_specular1, TexCoords));
	
	vec3 result = vec3(0.0, 0.0, 0.0);
	result = calcDirLight(dirLight, norm, viewDir, ambientTex, diffuseTex, specularTex);

	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += calcPointLight(pointLights[i], norm, FragPos, viewDir, ambientTex, diffuseTex, specularTex);
	}

	//we have to do it on ourself;
	//result += calcSpotLight(spotLight, norm, FragPos, viewDir, diffuseTex, specularTex);

	FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 aTex, vec3 dTex, vec3 sTex)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 ambient = light.ambient * aTex;
	vec3 diffuse = light.diffuse * diff * dTex;
	vec3 specular = light.specular * spec * sTex;
	vec3 normalTex = vec3(texture(material.texture_normal1, TexCoords));
	vec3 heightTex = vec3(texture(material.texture_height1, TexCoords));

	return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 aTex, vec3 dTex, vec3 sTex)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * aTex;
	vec3 diffuse = light.diffuse * diff * dTex;
	vec3 specular = light.specular * spec * sTex;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular) * light.lightColor;
}

vec3 calcSpotLight(SpotLight light,vec3 normal, vec3 fragPos, vec3 viewDir, vec3 dTex, vec3 sTex)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 diffuse = light.diffuse * diff * dTex;
	vec3 specular = light.specular * spec * sTex;

	diffuse *= intensity;
	specular *= intensity;

	return (diffuse + specular);
}
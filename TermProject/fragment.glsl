#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 out_Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec3 lightColor; 
uniform int light_on;
uniform float light_intensity;
uniform sampler2D outTexture;

void main()
{
	float ambientLight = light_intensity;
	vec3 ambient = ambientLight * lightColor;

	vec3 normalVector = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);

	if(light_on == 0) {diffuseLight = 0;}
	vec3 diffuse = diffuseLight * lightColor;

	float specularStrength = 1.0;
	int shininess = 128;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalVector);
	float specularLight = max(dot(viewDir, reflectDir), 0.0);
	specularLight = pow(specularLight, shininess);

	if(light_on == 0) {specularLight = 0;}
	vec3 specular = specularStrength * specularLight * lightColor;

	vec3 vTexCol = texture(outTexture, TexCoord).rgb;
	vec3 result = ((ambient + diffuse) * vTexCol + specular) * out_Color;

	FragColor = vec4(result, 1.0f);
}

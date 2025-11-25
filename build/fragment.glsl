#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * vec3(1.0);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1.0);
	
	float specularStrength = 0.6;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = specularStrength * spec * vec3(1.0);
	
	float distance = length(lightPos - FragPos);
	float attenuation = 1.0 / (1.0 + 0.009 * distance + 0.0032 * distance * distance);
	
	diffuse *= attenuation;
	specular *= attenuation;
	
	vec3 lighting = ambient + diffuse + specular;
	vec4 texColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
	FragColor = vec4(lighting, 1.0) * texColor;
}

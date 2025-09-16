#version 330 core

out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
uniform vec4 sunLightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

vec4 pointLight()
{	
	// Used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - crntPos;

	// Intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 1.0;
	float b = 0.09;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// 🌟 Ambient lighting (increased for more impact)
	float ambient = 0.35f;

	// 🌟 Diffuse lighting (boosted for stronger illumination)
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f) * 1.5f;

	// 🌟 Specular lighting (stronger and shinier reflections)
	float specularLight = 1.0f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 128);
	float specular = specAmount * specularLight * 1.5f;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 directLight()
{
	// 🌟 Ambient lighting (increased)
	float ambient = 0.30f;

	// 🌟 Diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f) * 1.5f;

	// 🌟 Specular lighting
	float specularLight = 0.5f; // Used to be 1.0f
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * specularLight * 1.5f;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * sunLightColor;
}

vec4 spotLight()
{
	// Spotlight cone parameters
	float outerCone = 0.85f;
	float innerCone = 0.90f;

	// 🌟 Ambient lighting
	float ambient = 0.35f;

	// Calculate light direction and distance
	vec3 lightDirection = normalize(lightPos - crntPos);
	float distance = length(lightPos - crntPos);

	// Distance-based attenuation (quadratic falloff)
	float a = 1.0;
	float b = 0.14; // Linear attenuation factor
	float c = 0.07; // Quadratic attenuation factor
	float distanceAtten = 1.0 / (a + b * distance + c * distance * distance);

	// 🌟 Diffuse lighting
	vec3 normal = normalize(Normal);
	float diffuse = max(dot(normal, lightDirection), 0.0f) * 1.5f;

	// 🌟 Specular lighting
	float specularLight = 1.0f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * specularLight * 1.5f;

	// Spotlight angle intensity
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float angleAtten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	// Combine distance and angle attenuation
	float attenuation = distanceAtten * angleAtten;

	// Apply attenuation to the lighting components
	return (texture(diffuse0, texCoord) * (diffuse * attenuation + ambient) + texture(specular0, texCoord).r * specular * attenuation) * lightColor;
}

float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
	// Outputs final color
	// FragColor = spotLight() + directLight();
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	vec4 depthVec4 = vec4(vec3(pow(depth, 1.4)), 1.0);
	FragColor = directLight() * (1 - depthVec4) + depthVec4;
}

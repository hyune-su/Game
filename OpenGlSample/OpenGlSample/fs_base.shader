#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 Position_worldspace2;
in vec3 Normal_cameraspace2;
in vec3 EyeDirection_cameraspace2;
in vec3 LightDirection_cameraspace2;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;
uniform vec3 LightPosition_worldspace2;

void main() {

	vec3 LightColor = vec3(1, 1, 1);
	float LightPower = 25.0f;

	vec3 MaterialDiffuseColor = texture(myTextureSampler, UV).rgb;

	float distance = length(LightPosition_worldspace - Position_worldspace);

	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);
	float cosTheta = clamp(dot(n, l), 0, 1);

	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E, R), 0, 1);

	//조명2
	vec3 LightColor2 = vec3(1, 1, 1);
	float LightPower2 = 30.0f;

	float distance2 = length(LightPosition_worldspace2 - Position_worldspace2);

	vec3 n2 = normalize(Normal_cameraspace2);
	vec3 l2 = normalize(LightDirection_cameraspace2);
	float cosTheta2 = clamp(dot(n2, l2), 0, 1);

	vec3 E2 = normalize(EyeDirection_cameraspace2);
	vec3 R2 = reflect(-l2, n2);
	float cosAlpha2 = clamp(dot(E2, R2), 0, 1);
	//조명 1 + 조명 2 + 주변광
	color = MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance)
		+ MaterialDiffuseColor * LightColor2 * LightPower2 * cosTheta2 / (distance2 * distance2)
		+ (MaterialDiffuseColor * 0.3);
}
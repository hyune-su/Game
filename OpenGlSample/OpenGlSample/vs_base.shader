#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 Position_worldspace2;
out vec3 Normal_cameraspace2;
out vec3 EyeDirection_cameraspace2;
out vec3 LightDirection_cameraspace2;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;
uniform mat4 M2;
uniform vec3 LightPosition_worldspace2;
void main() {

	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	// Position of the vertex, in worldspace : M * position
	Position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
	EyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace;

	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	// Normal of the the vertex, in camera space
	Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	// UV of the vertex. No special space for this one.
	UV = vertexUV;

	//���� 2
	Position_worldspace2 = (M2 * vec4(vertexPosition_modelspace, 1)).xyz;

	vec3 vertexPosition_cameraspace2 = (V * M2 * vec4(vertexPosition_modelspace, 1)).xyz;
	EyeDirection_cameraspace2 = vec3(0, 0, 0) - vertexPosition_cameraspace2;

	vec3 LightPosition_cameraspace2 = (V * vec4(LightPosition_worldspace2, 1)).xyz;
	LightDirection_cameraspace2 = LightPosition_cameraspace2 + EyeDirection_cameraspace2;

	Normal_cameraspace2 = (V * M2 * vec4(vertexNormal_modelspace, 0)).xyz;


}
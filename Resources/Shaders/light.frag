#version 330 core

out vec4 FragColor;

uniform vec4 lightColor;

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

// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

uniform float lightIntensity;

void main()
{
	FragColor  = vec4(1.0, 1.0, 1.0, 1.0);


}
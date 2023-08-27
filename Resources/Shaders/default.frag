#version 330 core

// Outputs colors in RGBA
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
//uniform vec4 lightColor;
// Gets the position of the light from the main function
//uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

//uniform vec4 ambientColor;

uniform float lightIntensity;



void main()
{
	vec2 texCoordRotated = texCoord;
	 texCoordRotated.y = 1.0 - texCoordRotated.y;
	// outputs final color
	FragColor = texture(diffuse0, texCoordRotated) * lightIntensity ;

}
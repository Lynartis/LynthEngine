#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include"shaderClass.h"

class Camera
{
private:
	float cameraSpeed;

public:

	glm::mat4 unitsScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.01f));

	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 left = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	glm::mat4 GetProjectionMatrix(float FOVdeg, float nearPlane, float farPlane);

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;


	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 250.0f ;
	float sensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window, float deltaTime);


};
#endif
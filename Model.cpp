#include "Model.h"
#include<iostream>
#include <thread>

Model::Model(std::vector <Vertex>& vertices, std::vector <GLuint>& indices)
{
	Model::vertices = vertices;
	Model::indices = indices;

	ModelVaoBinding();
}

void Model::ModelVaoBinding() 
{
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);						//positions
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));	//Normals
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));	//colors
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));	//Uvs

 /* In the Vertex Shader Default.vert
		 layout (location = 0) in vec3 aPos;

		layout (location = 1) in vec3 aNormal;

		layout (location = 2) in vec3 aColor;

		layout (location = 3) in vec2 aTex;
*/

// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();


//	std::cout << "MModelVaoBinding" << std::endl;



}

#ifndef GRID_CLASS_H
#define GRID_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"
#include <vector>         // For std::vector
#include <glm/glm.hpp>    // For glm types like glm::vec3


class Grid
{
public:
	Grid() = default; // Default constructor
	//vectors so we don't have to know the size of the arrays beforehand
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;

	glm::mat4 gridModel;

	// Initializes the mesh
	Grid(const int gridSize, const float spacing, const glm::vec4 gridColor, glm::vec3 gridPos);

	

	Shader gridShader;

	GLuint gridVBO;
	std::vector<Vertex> gridVertices;


	// Draws the mesh
	void Draw(Camera& camera, float lineSize);
};
#endif
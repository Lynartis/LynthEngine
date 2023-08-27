
#include "Grid.h"

Grid::Grid(const int gridSize, const float spacing, const glm::vec4 gridColor, glm::vec3 gridPos) :  gridShader("gridShader" , "grid.vert", "grid.frag")

{

	 gridModel = glm::mat4(1.0f);
	gridModel = glm::translate(gridModel, gridPos);

	gridShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(gridShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(gridModel));
	glUniform4f(glGetUniformLocation(gridShader.ID, "gridColor"), gridColor.x, gridColor.y, gridColor.z, gridColor.w);

	
	for (int i = -gridSize / 2; i <= gridSize / 2; ++i) {
		gridVertices.push_back({ glm::vec3(-gridSize / 2 * spacing, 0.0f, i * spacing) });
		gridVertices.push_back({ glm::vec3(gridSize / 2 * spacing, 0.0f, i * spacing) });

		gridVertices.push_back({ glm::vec3(i * spacing, 0.0f, -gridSize / 2 * spacing) });
		gridVertices.push_back({ glm::vec3(i * spacing, 0.0f, gridSize / 2 * spacing) });
	}





	// Generate grid vertex data
	//std::vector<Vertex> gridVertices = GenerateGridVertices(gridSize, spacing);

	// Create a VAO
	

	// Bind the VAO to configure its attributes
	VAO.Bind();

	// Create and set up grid VBO
	VBO gridVBO(gridVertices);

	// Link the VBO to the VAO
	VAO.LinkAttrib(gridVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);

	// Unbind the VAO and VBO
	VAO.Unbind();

}

void Grid::Draw(Camera& camera, float lineSize)
{
	
	

	gridShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(gridShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(gridModel));

	// Take care of the camera Matrix
//	glUniform3f(glGetUniformLocation(gridShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(gridShader, "camMatrix");

	// Bind the VAO before drawing
	VAO.Bind();

	// Set line width
	glLineWidth(lineSize);

	// Draw the grid lines
	glDrawArrays(GL_LINES, 0, gridVertices.size());

	// Unbind the VAO after drawing
	VAO.Unbind();

	glUseProgram(0);

}
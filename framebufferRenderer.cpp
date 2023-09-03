#include "framebufferRenderer.h"

framebufferRenderer::framebufferRenderer(float width, float height) {

	
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// generate texture

	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::vector<GLuint> quadIndices = {
	0, 1, 2,  // First triangle (bottom-right)
	0, 2, 3   // Second triangle (top-left)
	};
	/*
		std::vector<Vertex> quadVertices = {
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // Bottom-left vertex
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // Bottom-right vertex
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},   // Top-right vertex
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}   // Top-left vertex
		};


	*/



	std::vector<Vertex> quadVertices = {
		 {
		glm::vec3(-1.0f, -1.0f, 0.0f), // Position
		glm::vec3(0.0f, 0.0f, 1.0f),  // Normal
		glm::vec3(1.0f, 0.0f, 0.0f),  // Color (red)
		glm::vec2(0.0f, 0.0f)         // Texture coordinates (bottom-left)
	},
		// Bottom-right vertex
		{
			glm::vec3(1.0f, -1.0f, 0.0f),  // Position
			glm::vec3(0.0f, 0.0f, 1.0f),  // Normal
			glm::vec3(0.0f, 1.0f, 0.0f),  // Color (green)
			glm::vec2(1.0f, 0.0f)         // Texture coordinates (bottom-right)
		},
		// Top-right vertex
		{
			glm::vec3(1.0f, 1.0f, 0.0f),   // Position
			glm::vec3(0.0f, 0.0f, 1.0f),  // Normal
			glm::vec3(0.0f, 0.0f, 1.0f),  // Color (blue)
			glm::vec2(1.0f, 1.0f)         // Texture coordinates (top-right)
		},
		// Top-left vertex
		{
			glm::vec3(-1.0f, 1.0f, 0.0f),  // Position
			glm::vec3(0.0f, 0.0f, 1.0f),  // Normal
			glm::vec3(1.0f, 1.0f, 1.0f),  // Color (white)
			glm::vec2(0.0f, 1.0f)         // Texture coordinates (top-left)
		}
	};

	// CONSTRUCT VAO HERE!

	vao.GenVertexArrays();
	// Create VBO and VAO for the quad
	vao.Bind();
	VBO vbo(quadVertices);
	EBO EBO(quadIndices);
	// Link vertex attributes

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);						//positions
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));	//Normals
	vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));	//colors
	vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));	//Uvs

	vao.Unbind();
	vbo.Unbind();
	EBO.Unbind();

	setInt();

};

void framebufferRenderer::Render() {

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glActiveTexture(GL_TEXTURE0);
	frameBufferShader.Activate();

	vao.Bind();
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Draw the quad
	vao.Unbind();
	frameBufferShader.Unbind();




}

void framebufferRenderer::Bind() {

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

}


void framebufferRenderer::setInt() 
{


	glUniform1i(glGetUniformLocation(frameBufferShader.ID,"screenTexture"), 0);

}


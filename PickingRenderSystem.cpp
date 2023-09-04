#include "PickingRenderSystem.h"
#include <iostream>



PickingRenderSystem::PickingRenderSystem(float width, float height) {

	framewidth = width;
	frameheight = height;
	glGenFramebuffers(1, &framebuffer2);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);

	// generate texture

	glGenTextures(1, &textureColorbuffer2);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer2, 0);

	unsigned int rbo2;
	glGenRenderbuffers(1, &rbo2);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo2);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo2);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	


};



// Sample function to decode the entityId from a color
int DecodeEntityId(glm::vec3 color) {
	int entityId = 0;

	// Decode the red, green, and blue components back into an integer
	entityId |= static_cast<int>(color.r * 255.0);
	entityId |= (static_cast<int>(color.g * 255.0) << 8);
	entityId |= (static_cast<int>(color.b * 255.0) << 16);

	return entityId;
}

// Sample code to read the pixel color at mouse cursor position and decode entityId
void PickingRenderSystem::GetPickedEntityId(int mouseX, int mouseY, int& entityId) {
	// Read the color from the framebuffer at the mouse cursor position
	glm::vec3 color;
	glReadPixels(mouseX, frameheight - mouseY, 1, 1, GL_RGB, GL_FLOAT, &color[0]);

	// Decode the entityId
	entityId = DecodeEntityId(color);
}



int PickingRenderSystem::Pick(entt::registry& registry, Camera& camera, GLFWwindow* window)
{


		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
	//	std::cout << mouseX << " , " << mouseY << std::endl;
		// Handle left mouse button click at (mouseX, mouseY)
		// Your code here
	

		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);
		glClearColor(1.0, 1.0, 1.0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			// Create a view that only selects entities with the specified components 
		auto view = registry.view<TransformComponent, ModelComponent, PickingComponent>();

		for (entt::entity entity : view) {

			TransformComponent& transformComp = view.get<TransformComponent>(entity);
			ModelComponent& modelComp = view.get<ModelComponent>(entity);
			PickingComponent& pickComp = view.get<PickingComponent>(entity);





			glActiveTexture(GL_TEXTURE0);
			pickingShader.Activate();


			// Take care of the camera Matrix
			glUniform3f(glGetUniformLocation(pickingShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			camera.Matrix(pickingShader, "camMatrix");

			glUniformMatrix4fv(glGetUniformLocation(pickingShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(transformComp.modelMatrix));

			glUniform1i(glGetUniformLocation(pickingShader.ID, "entityId"), pickComp.ID);


			modelComp.model.VAO.Bind();

			glBindTexture(GL_TEXTURE_2D, textureColorbuffer2);

			glDrawElements(GL_TRIANGLES, modelComp.model.indices.size(), GL_UNSIGNED_INT, 0);

			modelComp.model.VAO.Unbind();
			pickingShader.Unbind();

		//	std::cout << "Im Picking" << std::endl;

		}

		int selection;
		GetPickedEntityId(mouseX,mouseY,selection);
		std::cout << selection << std::endl;


		glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default

		return selection;

	
	

}
#include "RenderSystem.h"
#include <iostream>

void RenderSystem::Draw(entt::registry& registry, Camera& camera)
{

	
		// Create a view that only selects entities with the specified components 
		auto view = registry.view<MaterialComponent, TransformComponent, ModelComponent>();

		// Loop through entities with all three components and perform actions
		for (entt::entity entity : view) {
			MaterialComponent& materialComp = view.get<MaterialComponent>(entity);
		  TransformComponent& transformComp = view.get<TransformComponent>(entity);
			ModelComponent& modelComp = view.get<ModelComponent>(entity);

		
			materialComp.shaderProgram.Activate();

			// Take care of the camera Matrix
			glUniform3f(glGetUniformLocation(materialComp.shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			camera.Matrix(materialComp.shaderProgram, "camMatrix");

			glUniformMatrix4fv(glGetUniformLocation(materialComp.shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(transformComp.modelMatrix));


			// Keep track of how many of each type of textures we have
			unsigned int numDiffuse = 0;
			unsigned int numSpecular = 0;

		
			for (unsigned int i = 0; i < materialComp.textures.size(); i++)
			{
				std::string num;
				std::string type = materialComp.textures[i].type;
				if (type == "diffuse")
				{
					num = std::to_string(numDiffuse++);
				}
				else if (type == "specular")
				{
					num = std::to_string(numSpecular++);
				}
				materialComp.textures[i].texUnit(materialComp.shaderProgram, (type + num).c_str(), i);
				materialComp.textures[i].Bind();
			}
		
			modelComp.model.VAO.Bind();
		//	std::cout << "drawing" << std::endl;
			// Draw the actual mesh
			glDrawElements(GL_TRIANGLES,modelComp.model.indices.size(), GL_UNSIGNED_INT, 0);

		//texture Cleanup
			for (unsigned int i = 0; i < materialComp.textures.size(); i++)
			{
				materialComp.textures[i].Unbind();
			}
			// modelComp.model.VAO.Unbind();
	
			materialComp.shaderProgram.Unbind();
			modelComp.model.VAO.Unbind();

		}
			
		

}











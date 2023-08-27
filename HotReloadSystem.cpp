#include "HotReloadSystem.h"



	
	void HotReloadSystem::HotReload(entt::registry& registry) {
	


	

		
			std::cout << "Hot Reloading Shaders" << std::endl;
			
			std::this_thread::sleep_for(std::chrono::seconds(1));

			std::string shaderName = "Null";

			auto view2 = registry.view<MaterialComponent, TransformComponent, ModelComponent>();

			std::unordered_set<std::string> encounteredShaderNames;

			for (entt::entity entity : view2)
			{
				// Access the components using ENTT's get method
				TransformComponent& transformComp = view2.get<TransformComponent>(entity);
				MaterialComponent& materialComp = view2.get<MaterialComponent>(entity);
				ModelComponent& modelComp = view2.get<ModelComponent>(entity);



				shaderName = materialComp.shaderProgram.shaderName;
				std::cout << "Current Shader" << shaderName << std::endl;

				if (encounteredShaderNames.find(shaderName) == encounteredShaderNames.end()) {

					materialComp.shaderProgram.reloadShaders();


					encounteredShaderNames.insert(shaderName);
				}

		//		materialComp.shaderProgram.Activate();
		


				//




				materialComp.shaderProgram.Unbind();
			
		

				
			}

			



			std::this_thread::sleep_for(std::chrono::seconds(2));
			isHotReloading = false;

		
	
	
	
	};



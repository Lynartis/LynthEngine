#ifndef IMPORTER_CLASS_H
#define IMPORTER_CLASS_H
#include<entt/entt.hpp>
#include<string>
#include <thread>
#include"TransformComponent.h"
#include"Mesh.h"
#include"MaterialComponent.h"
#include"ModelComponent.h"
#include"PickingComponent.h"

class Importer
{
public:




	// Initializes the mesh
	void Import(entt::registry& registry);

	glm::mat4 generateModelMatrix(glm::vec3 position);
	
	Model ModelImporter(std::string modelPath);
};
#endif
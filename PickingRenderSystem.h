#ifndef PICKING_RENDER_SYSTEM_H
#define PICKING_RENDER_SYSTEM_H

#include<string>
#include<entt/entt.hpp>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"shaderClass.h"



#include"TransformComponent.h"
#include"ModelComponent.h"
#include"MaterialComponent.h"
#include"PickingComponent.h"

class PickingRenderSystem
{

public:
	
	unsigned int framebuffer2;
	unsigned int textureColorbuffer2;
	Shader pickingShader = Shader("PickingShader", "pickingShader.vert", "pickingShader.frag");

	PickingRenderSystem(float width, float height);
	int Pick(entt::registry& registry, Camera& camera, GLFWwindow* window);
	void GetPickedEntityId(int mouseX, int mouseY, int& entityId);


private:
	bool releaseMouse = false;
	float framewidth;
	float frameheight;
};

#endif
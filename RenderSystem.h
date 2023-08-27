#ifndef RENDERSYSTEM_CLASS_H
#define RENDERSYSTEM_CLASS_H

#include<string>
#include<entt/entt.hpp>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"


#include"TransformComponent.h"
#include"ModelComponent.h"
#include"MaterialComponent.h"

class RenderSystem
{
public:

	void Draw(entt::registry& registry, Camera& camera);



};

#endif
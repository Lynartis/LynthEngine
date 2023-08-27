#ifndef HOTRELOADSYSTEM_CLASS_H
#define HOTRELOADSYSTEM_CLASS_H

#include<iostream>
#include<filesystem>
namespace fs = std::filesystem;
#include<glm/gtx/string_cast.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp> 
#include<entt/entt.hpp>
#include"RenderSystem.h"
#include"Importer.h"
#include <chrono>
#include <thread>


class HotReloadSystem
{
public:

	bool isHotReloading = false;
	void HotReload(entt::registry& registry);


};

#endif
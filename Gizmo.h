#ifndef GIZMO_CLASS_H
#define GIZMO_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include "imgui/imGuizmo/ImGuizmo.h"
#include<entt/entt.hpp>



#include"TransformComponent.h"

class Gizmo
{
private:
	bool controlKeyPressed = false; // Flag to track the left control key press

public:
	bool isActive = true;
	Gizmo(bool active);
	void GizmoDraw(entt::registry& registry, entt::entity selected, float width, float height, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void GizmoInputs(GLFWwindow* window);


};
#endif
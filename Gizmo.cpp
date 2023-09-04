#include"Gizmo.h"
#include <iostream>
Gizmo::Gizmo(bool active)
{
//	isActive = active;


};



void Gizmo::GizmoInputs(GLFWwindow* window)
{

  


	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && boolq) {

		isActive =	!isActive;
		boolq = false;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {

		boolq = true;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){

		 currentGuizmo = ImGuizmo::TRANSLATE;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {

		currentGuizmo = ImGuizmo::ROTATE;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

		currentGuizmo = ImGuizmo::SCALE;
	}

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {

		currentGuizmo = ImGuizmo::UNIVERSAL;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

		snap = !snap;
	}



}

void Gizmo::AssignGuizmo(entt::registry& registry, int selection) {

	//SELECT ENTITY TO DRAW GIZMO



	auto view2 = registry.view<PickingComponent>();

	// Iterate over the entities and perform actions
	for (const auto entity : view2) {

		PickingComponent& picking = registry.get<PickingComponent>(entity);


		if (picking.ID == selection  && !ImGuizmo::IsOver())
		{
			selectedEntity = entity;
			isActive = true;

			std::cout << "SelectedEntity = " << selection << std::endl;
		}

		if (selection == 16777215 && !ImGuizmo::IsOver())
		{

			isActive = false;

		}
	}
	

}




void Gizmo::GizmoDraw(entt::registry& registry, float width, float height, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{

	
	if (isActive) {

		auto& entityTransform = registry.get<TransformComponent>(selectedEntity);


		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		// Draw translation, rotation, and scaling gizmos
		ImGuizmo::SetOrthographic(false); 
		//ImGuizmo::SetDrawlist();

		ImGuizmo::SetRect(0, 0, width, height);


		float snapValue = 10.0f;

		float snapValues[3] = { snapValue, snapValue, snapValue };

		ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
			currentGuizmo, ImGuizmo::LOCAL, glm::value_ptr(entityTransform.modelMatrix), nullptr, snap ? snapValues : nullptr);
		//	std::cout << ImGuizmo::UNIVERSAL << std::endl;


		bool showDebugWindow = true;
		glm::vec3 positionImGui = glm::vec3(entityTransform.modelMatrix[3]);

		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 250, io.DisplaySize.y - 70));
		ImGui::SetNextWindowSize(ImVec2(250, 70));
		ImGui::Begin("Debug Window", &showDebugWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);


		
		ImVec4 clearColor = ImVec4(1.0f, 1.0f, 1.0f, 0.1f);
		ImGui::PushStyleColor(ImGuiCol_Border, clearColor);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, clearColor);


		ImGui::Text("Selected Object Transforms: ");

		if (ImGui::DragFloat3("Position", &positionImGui[0], 1.00f)) {


			entityTransform.modelMatrix[3] = glm::vec4(positionImGui, 1.0f);

		
		}

		
		ImGui::PopStyleColor(2);


		ImGui::End();

		glDisable(GL_BLEND);



	}
	


}

	


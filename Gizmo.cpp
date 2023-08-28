#include"Gizmo.h"

Gizmo::Gizmo(bool active)
{
	isActive = active;


};



void Gizmo::GizmoInputs(GLFWwindow* window)
{

    // Check for key presses
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        if (!controlKeyPressed) {
            isActive = !isActive; // Toggle the state
            controlKeyPressed = true; // Set the flag to true
        }
    }
    else {
        controlKeyPressed = false; // Reset the flag when any of the keys is released
    }

}
void Gizmo::GizmoDraw(entt::registry& registry, entt::entity selected, float width, float height, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{

	//Matilda test
	

	auto& entityTransform = registry.get<TransformComponent>(selected);
		
		
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


			// Draw translation, rotation, and scaling gizmos
			ImGuizmo::SetOrthographic(false); // Set to true for orthographic view
			//ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(0, 0, width, height);

			ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
				ImGuizmo::TRANSLATE, ImGuizmo::WORLD, glm::value_ptr(entityTransform.modelMatrix));



			bool showDebugWindow = true;
			glm::vec3 positionImGui = glm::vec3(entityTransform.modelMatrix[3]);

			ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 250, io.DisplaySize.y - 70));
			ImGui::SetNextWindowSize(ImVec2(250, 70));
			ImGui::Begin("Debug Window", &showDebugWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);


			// Set the background color with alpha to achieve transparency
			ImVec4 clearColor = ImVec4(1.0f, 1.0f, 1.0f, 0.1f);
			ImGui::PushStyleColor(ImGuiCol_Border, clearColor);
			ImGui::PushStyleColor(ImGuiCol_WindowBg, clearColor);


			// Add your debug information here
			ImGui::Text("Selected Object Transforms: ");

			if (ImGui::DragFloat3("Position", &positionImGui[0], 1.00f)) {


				entityTransform.modelMatrix[3] = glm::vec4(positionImGui, 1.0f);

				//	transformComp.m0odelMatrix = glm::translate(transformComp.modelMatrix, positionImGui);
			}

			// Restore original colors
			ImGui::PopStyleColor(2);




			ImGui::End();

			glDisable(GL_BLEND);


}

	


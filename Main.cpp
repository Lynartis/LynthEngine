#include<filesystem>
namespace fs = std::filesystem;
#include<glm/gtx/string_cast.hpp>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include "imgui/imGuizmo/ImGuizmo.h"


#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp> 
#include<entt/entt.hpp>

#include"Model.h"
#include"Mesh.h"
#include"Time.h"
#include"Grid.h"
#include"RenderSystem.h"
#include"Importer.h"
#include"HotReloadSystem.h"
#include"Gizmo.h"

#include<filewatch/FileWatch.hpp>


const unsigned int width = 1366;
const unsigned int height = 768;



int main()
{


	entt::registry registry;



	std::cout << "88     Yb  dP 88b 88 888888 88  88     888888 88b 88  dP``b8 88 88b 88 888888    " << std::endl;
	std::cout << "88      YbdP  88Yb88   88   88  88     88__   88Yb88 dP   `´ 88 88Yb88 88__      " << std::endl;
	std::cout << "88  .o   8P   88 Y88   88   888888     88´´   88 Y88 Yb  ´88 88 88 Y88 88''      " << std::endl;
	std::cout << "88ood8  dP    88  Y8   88   88  88     888888 88  Y8  YboodP 88 88  Y8 888888  " << std::endl;
	std::cout << "_____________________________________________________________________________" << std::endl;
	std::cout << " " << std::endl;



	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "LynthEngine"
	GLFWwindow* window = glfwCreateWindow(width, height, "LynthEngine", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	
	HotReloadSystem hotReload;
	
	std::string texPath = fs::current_path().string() + "\\Resources\\Shaders\\";

	filewatch::FileWatch<std::string> watch(texPath ,[&hotReload, &registry](const std::string& path, const filewatch::Event change_type) {
		//	std::cout << path << " - " << (int)change_type << std::endl;

			switch (change_type)
			{
		
			case filewatch::Event::modified:
				if (!hotReload.isHotReloading && (int)change_type == 2) {
					hotReload.isHotReloading = true;
				
				}
				
				break;
		
			};

		}
	);






	Importer importer;
	importer.Import(registry);



	float lightIntensity = 1.0f;

	auto view = registry.view<TransformComponent, MaterialComponent>();

	// Iterate over the entities and perform actions
	for (const auto entity : view) {
		// Access the components using ENTT's get method
		TransformComponent& transform = view.get<TransformComponent>(entity);
		MaterialComponent& material = view.get<MaterialComponent>(entity);

		material.shaderProgram.Activate();

		glUniform1f(glGetUniformLocation(material.shaderProgram.ID, "lightIntensity"), lightIntensity);


	}


	//Enables the Depth Buffer:
	glEnable(GL_DEPTH_TEST);

	//Camera Object:
	Camera camera(width, height, glm::vec3(0.0f, 200.0f, 500.0f));

	//Gizmo Object;
	Gizmo gizmo(true);

	//IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange; // Disable ImGui's mouse cursor rendering

	// IMGHUI VARIABLES
	bool wireframe = false;
	bool storeCameraPos = false;
	float cameraPov = 45;
	float size;
	float color[4] = { 0.07f, 0.13f, 0.17f, 1.0f };



	float px = 0.5f;
	float py = 0.5f;
	float pz = 0.5f;

	Time time;



	// -- Grid --


	float gridColorUi[4] = { 0.2f, 0.2f, 0.2f, 0.2f };
	glm::vec4 gridColor = glm::vec4(gridColorUi[0], gridColorUi[1], gridColorUi[2], gridColorUi[3]);
	float gridColorUi2[4] = { 0.1f, 0.1f, 0.1f, 0.1f };
	glm::vec4 gridColor2 = glm::vec4(gridColorUi2[0], gridColorUi2[1], gridColorUi2[2], gridColorUi2[3]);
	glm::vec3 gridPos = glm::vec3(0.0f, 0.0f, 0.0f);



	Grid grid(30,100.0f, gridColor2, gridPos);
	Grid grid2(300, 10.0f, gridColor, gridPos);
	Grid grid3(2, 100.0f, glm::vec4(0.8f, 0.1f, 0.1f, 0.1f), gridPos);



	glm::vec3 gyzmoPosition = glm::vec3(0.0f, 0.0, 0.0f);

	// Create the object's transformation matrix
	glm::mat4 objectMatrix = glm::mat4(1.0f); // Start with the identity matrix

	// Apply translation
	objectMatrix = glm::translate(objectMatrix, gyzmoPosition);




	//SELECT ENTITY TO DRAW GIZMO

	entt::entity selectedEntity;

	auto view2 = registry.view<MaterialComponent>();

	// Iterate over the entities and perform actions
	for (const auto entity : view2) {

		MaterialComponent& material = registry.get<MaterialComponent>(entity);


		if (material.materialID == "matildaOpaque")
		{
			selectedEntity = entity;

		}
	}






//RENDER SYSTEM
	RenderSystem renderer;

	bool rKeyPressed = false;  // Initialize the key state

	// ---------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------
	// -----------------------------Main while loop-------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{

		//-----Time-----
		time.RunTime();


		if (hotReload.isHotReloading) 
		{

			hotReload.HotReload(registry);
		//	std::cout << "loading works aqui " << std::endl;


			auto view2 = registry.view<MaterialComponent, TransformComponent, ModelComponent>();

	
			// Replaced for initial Setup Void Renderer/Importer
			for (entt::entity entity : view2)
			{
				// Access the components using ENTT's get method
				TransformComponent& transformComp = view2.get<TransformComponent>(entity);
				MaterialComponent& materialComp = view2.get<MaterialComponent>(entity);
				ModelComponent& modelComp = view2.get<ModelComponent>(entity);


				materialComp.shaderProgram.Activate();
				
				 glUniform1f(glGetUniformLocation(materialComp.shaderProgram.ID, "lightIntensity"), lightIntensity);


				// Take care of the camera Matrix
				glUniform3f(glGetUniformLocation(materialComp.shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
				camera.Matrix(materialComp.shaderProgram, "camMatrix");

				glUniformMatrix4fv(glGetUniformLocation(materialComp.shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(transformComp.modelMatrix));


			}

		}

		
	
			//-----Background Color:-------
				// Specify the color of the background		
			glClearColor(color[0], color[1], color[2], 1.0f);
			// Clean the back buffer and assign the new color to it
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			//------Wireframe-----
			if (wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			//----CAMERA----
			camera.Inputs(window, time.DeltaTime());
			camera.updateMatrix(cameraPov, 0.01f, 500.0f);

			//----RENDER SYSTEM----
			renderer.Draw(registry, camera);

			


			//----IMGUIZMOTEST----

			gizmo.GizmoInputs(window);

		//	std::cout << "Gyzmo is: " << gizmo.isActive << std::endl;
				//-----IMGUI----
			if (gizmo.isActive) 
			{
				grid.Draw(camera, 2.0f);
				grid2.Draw(camera, 1.0f);


				ImGuizmo::BeginFrame();

				// Get the camera's view and projection matrices
				const glm::mat4 viewMatrix = camera.view;
				const glm::mat4 projectionMatrix = camera.projection;
				
			
				
				gizmo.GizmoDraw(registry, selectedEntity, width, height, viewMatrix, projectionMatrix);



			}
		
		
			


		
			
			
			
			//--------IMGUI-----------


			if (ImGui::BeginMainMenuBar())
			{
				// Create a menu item
				if (ImGui::BeginMenu("File"))
				{

					if (ImGui::Button("SAVE")) {
						//		DO SAVE STUFF
					}
					if (ImGui::Button("LOAD")) {
						//		DO SAVE STUFF
					}

					ImGui::EndMenu();
				}

				// Create another menu item
				if (ImGui::BeginMenu("Lights"))
				{
					// Add menu items to the "Edit" menu
					ImGui::MenuItem("Ambient Light:");
					//	ImGui::ColorEdit4("Ambient Color", ambientColorUi);
					ImGui::MenuItem("Light 01");
					//		ImGui::DragFloat3("Position", &lightPos[0], 0.01f);
					ImGui::DragFloat("Intensity", &lightIntensity, 0.01f);
					//	ImGui::ColorEdit4("Light Color", lightColorUi);


						// End the "Edit" menu
					ImGui::EndMenu();
				}


				if (ImGui::BeginMenu("Deferred"))
				{
					// Text that appears in the window
					ImGui::Text("That is a test text");
					// Checkbox that appears in the window
					ImGui::Checkbox("Wireframe", &wireframe);
					// Slider that appears in the window
					ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);



					ImGui::Text("BackGround Color:");
					// Fancy color editor that appears in the window
					ImGui::ColorEdit4("Color", color);
					// Create a button
					if (ImGui::Button("resetBGColor")) {
						color[0] = 0.07f;
						color[1] = 0.13f;
						color[2] = 0.17f;
						color[3] = 1.0f;
					}

					// End the "Edit" menu
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Camera"))
				{
					// Text that appears in the window
					ImGui::Text("Work In Progress Settings");
					// Checkbox that appears in the window

					if (ImGui::Button("Store Default Pos")) {
						//		storeCameraPos = true;
					}

					ImGui::SliderFloat("Camera Pov", &cameraPov, 25.0f, 140.0f);


					// End the "Edit" menu
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Objects"))
				{
					
					if (ImGui::Button("Matilda")) {
						
						auto view2 = registry.view<MaterialComponent>();

						// Iterate over the entities and perform actions
						for (const auto entity : view2) {

							MaterialComponent& material = registry.get<MaterialComponent>(entity);


							if (material.materialID == "matildaOpaque")
							{
								selectedEntity = entity;

							}
						}


					}

					if (ImGui::Button("llunetaOpaque")) {

						auto view2 = registry.view<MaterialComponent>();

						// Iterate over the entities and perform actions
						for (const auto entity : view2) {

							MaterialComponent& material = registry.get<MaterialComponent>(entity);


							if (material.materialID == "llunetaOpaque")
							{
								selectedEntity = entity;

							}
						}


					}
					if (ImGui::Button("robotOpaque2")) {

						auto view2 = registry.view<MaterialComponent>();

						// Iterate over the entities and perform actions
						for (const auto entity : view2) {

							MaterialComponent& material = registry.get<MaterialComponent>(entity);


							if (material.materialID == "robotOpaque2")
							{
								selectedEntity = entity;

							}
						}


					}






			


					// End the "Edit" menu
					ImGui::EndMenu();
				}




				// End the main menu bar
				ImGui::EndMainMenuBar();
			}


			// Renders the ImGUI elements
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



			// ------ OpenGL -----

				// Swap the back buffer with the front buffer
			glfwSwapBuffers(window);
			// Take care of all GLFW events
			glfwPollEvents();
		}



		// Deletes all ImGUI instances
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();





		// Delete all the objects we've created


		auto shaderDelete = registry.view<MaterialComponent>();

		// Iterate over the entities and perform actions
		for (const auto entity : view) {

			MaterialComponent& material = registry.get<MaterialComponent>(entity);

			material.shaderProgram.Delete();

		}

		//	lightShader.Delete();

			// Delete window before ending the program
		glfwDestroyWindow(window);
		// Terminate GLFW before ending the program
		glfwTerminate();
		return 0;
	}

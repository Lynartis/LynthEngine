#include "Importer.h"

#include<filesystem>
namespace fs = std::filesystem;


void Importer::Import(entt::registry& registry)
{

/*

    // 1 Create entity

        //Assign transform component
                // generateModelMatrix()

        //Assign MaterialComponent

                           std::string materialID;
                           std::vector <Texture> textures;
                           Shader shaderProgram;

        //Assign ModelComponent
                        std::string ModelName;
                        Model model;

*/



	//Plan hardcode it


    /// ---------------- TRANSFORM COMPONENTS ----------------

    glm::vec3 testPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 testPosition2 = glm::vec3(250.0f, 50.0f, 350.0f);
    glm::vec3 robotPosition = glm::vec3(-20.00f, 0.0f, -400.0f);
    glm::vec3 robotPosition2 = glm::vec3(-250.00f, 50.0f, -150.0f);

    // pyramidModel = glm::translate(pyramidModel, pyramidPos);

    TransformComponent llunatransformComponent(generateModelMatrix(testPosition));
    TransformComponent llunatransformComponent2(generateModelMatrix(testPosition2));
    TransformComponent robottransformComponent(generateModelMatrix(robotPosition));
    TransformComponent robottransformComponent2(generateModelMatrix(robotPosition2));




	//--------------- MATERIAL MAP components --------------------

    std::string texPath = fs::current_path().string() + "\\Resources\\textures\\";  //	this is a c++17 feature to setup the path of the textures folder:
  //  std::cout << texPath << "\n";
    
    Texture textures[]
    {
       Texture((texPath + "lluna.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
       Texture((texPath + "lluna.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    Texture textures2[]
    {
        Texture((texPath + "matilda.tga").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture((texPath + "planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };
 
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    std::vector <Texture> tex2(textures2, textures2 + sizeof(textures) / sizeof(Texture));

  
    Shader shaderProgram("ShaderProgram", "default.vert", "default.frag");
    Shader lightShader("LightShader", "light.vert", "light.frag");
   

// THE MAP materialMap -----
    // Create an unordered_map to store MaterialComponent instances
//    std::unordered_map<std::string, MaterialComponent> materialMap;

    // Populate the material map with MaterialComponent instances
 //   materialMap["lluna"] = MaterialComponent{ "llunetaOpaque", tex, shaderProgram };
 //   materialMap["robot"] = MaterialComponent{ "RobotOpaque", tex2, shaderProgram };
    // Add more materials as needed...



    // PARA ASIGNAR TENEMOS materialMap["lluna"]

 /*
    // Load model information from JSON and assign material components
    // Assume materialName is extracted from JSON
    std::string materialName = "lluna"; // Example material name

    // Check if the material exists in the map
    if (materialMap.find(materialName) != materialMap.end()) {
        // Material exists, create an entity and assign the material component
        auto entity = registry.create();
        registry.emplace<MaterialComponent>(entity, materialMap[materialName]);


        // ... Other components ...
    }
    else {
        // Handle the case where the material does not exist
    }


 */


    MaterialComponent llunaMaterialComponent("llunetaOpaque", tex, shaderProgram);
    MaterialComponent robotMaterialComponent("matildaOpaque", tex2, shaderProgram);
    MaterialComponent robotMaterialComponent2("robotOpaque2", tex2, lightShader);

// ---------------------------MODEL COMPONENT -----------------------------------------

 //   Model modelLunna;
    ModelComponent llunaModelComponent(ModelImporter(texPath + "test.obj"));
    ModelComponent robotModelComponent(ModelImporter(texPath + "matilda.obj"));
 

    // ---------------------------PICKING COMPONENT -----------------------------------------

    PickingComponent Pick1(1);
    PickingComponent Pick2(250);
    PickingComponent Pick3(3469);
    PickingComponent Pick4(45556);


    entt::entity entity1 = registry.create();

    registry.emplace<TransformComponent>(entity1, robottransformComponent);
    registry.emplace<MaterialComponent>(entity1, robotMaterialComponent);
    registry.emplace<ModelComponent>(entity1, robotModelComponent);
    registry.emplace<PickingComponent>(entity1, Pick1);

    // Create an entity
    entt::entity entity5 = registry.create();

    // Assign the components to the entity
    registry.emplace<TransformComponent>(entity5, llunatransformComponent);
    registry.emplace<MaterialComponent>(entity5, llunaMaterialComponent);
    registry.emplace<ModelComponent>(entity5, llunaModelComponent);
    registry.emplace<PickingComponent>(entity5, Pick2);



    // Create an entity
    entt::entity entity2 = registry.create();

    // Assign the components to the entity
    registry.emplace<TransformComponent>(entity2, llunatransformComponent2);
    registry.emplace<MaterialComponent>(entity2, llunaMaterialComponent);
    registry.emplace<ModelComponent>(entity2, llunaModelComponent);
    registry.emplace<PickingComponent>(entity2, Pick3);
    entt::entity entity3 = registry.create();

    // Assign the components to the entity
    registry.emplace<TransformComponent>(entity3, robottransformComponent2);
    registry.emplace<MaterialComponent>(entity3, robotMaterialComponent2);
    registry.emplace<ModelComponent>(entity3, llunaModelComponent);
    registry.emplace<PickingComponent>(entity3, Pick4);

   
 

}

Model Importer::ModelImporter(std::string modelPath) {


    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    // const float CM_PER_METER = 1.0f;


     // Check if the scene is loaded
    while (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        // The model is not fully loaded yet, so wait for a short duration before checking again.
        // You can use std::this_thread::sleep_for or any other mechanism to pause the loop.
        // For example, here's a simple sleep using <chrono>:
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    }

    // The model has finished loading, so you can proceed with your code here.
    // Convert the loaded properties to your OpenGL VBO, setup shaders, etc.



    if (scene && scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE && scene->mRootNode) {
        // Model loaded successfully
     //   std::cout << "Model loaded successfully!" << std::endl;

        unsigned int numMeshes = scene->mNumMeshes;
      //  std::cout << "Number of meshes in the model: " << numMeshes << std::endl;



        std::vector<Vertex> vertices; // Vector to store the converted vertices

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[i];

            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
                Vertex vertex;

                // Convert position
                vertex.position = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);

                /*
                                    Vertex vertex;
                                    vertex.position.x = mesh->mVertices[j].x * CM_PER_METER;
                                    vertex.position.y = mesh->mVertices[j].y * CM_PER_METER;
                                    vertex.position.z = mesh->mVertices[j].z * CM_PER_METER;

                */



                // Convert normal
                if (mesh->HasNormals()) {
                    vertex.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
                }
                else {
                    // If normals are missing, you can set a default value or calculate them
                    vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
                }

                // Convert color (if available) - you may set a default color if not present
                vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);

                // Convert texture coordinates (if available) - you may set default UVs if not present
                if (mesh->HasTextureCoords(0)) {
                    vertex.texUV = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
                }
                else {
                    // If texture coordinates are missing, you can set a default value
                    vertex.texUV = glm::vec2(0.0f, 0.0f);
                }

                vertices.push_back(vertex); // Add the converted vertex to the vector
            }
        }


        //Indices:
        std::vector<unsigned int> indices; // Vector to store the mesh indices (faces)

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[i];

            for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                aiFace face = mesh->mFaces[j];
                for (unsigned int k = 0; k < face.mNumIndices; k++) {
                    indices.push_back(face.mIndices[k]);
                }
            }
        }
      //  std::cout << "Can't belive we are here!" << std::endl;
        Model model(vertices, indices);
        return model;
        //      Mesh mesh(vertices, indices, textures);
      //  Model::mesh = Mesh(vertices, indices, textures);
     





        // Your additional code to work with the loaded model can go here
        // For example, you can extract mesh data and process it, setup VBO, etc.
    }
    else {
        // Model loading failed
        std::cout << "Failed to load the model!" << std::endl;


        // RETURN EMPTY DEFAULT MODEL SIMS LIKE TO SEE THE ERROR ON SCREEN

    }



}




//MIRAR ORDRE DE TRANSFORMACIONS FER PRIMER NOMES POSICIO PER ARA I DESPUES JA FICAREM ROTACIONS I TONTUNES
//aqui hi ha un exemple de com modificar sa model matrix amb lo que ma donen
//Igual val mes la pena fer un void generateModelMatrix(){} cuan sa importi pos rotation y scale (scale nose si la vull importar (resetxform y tal xD)



glm::mat4 Importer::generateModelMatrix( glm::vec3 position ) {


    // TO DO :  ADD ROTATION AND SCALE ---  first scale, then rotate, then translate

    //matrix initialization
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    
    //scale:

    //rotate:
    
    //translate
    modelMatrix = glm::translate(modelMatrix, position);

    return modelMatrix;

}
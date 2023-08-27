#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct MaterialComponent {
public:
    std::string materialID;
    std::vector <Texture> textures;
    Shader shaderProgram;


 
    // Constructor to initialize
    MaterialComponent(std::string materialID, std::vector <Texture> tex, Shader shaderProgram)
        : materialID(materialID) , textures(tex), shaderProgram(shaderProgram) {}

};

#endif  MATERIAL_COMPONENT_H









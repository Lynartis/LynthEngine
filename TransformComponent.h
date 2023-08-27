#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct TransformComponent {
public:
    glm::mat4 modelMatrix;
 //   glm::vec3 position;  // 3D vector for position (x, y, z)
  //  glm::quat rotation;  // Quaternion for rotation
  //  glm::vec3 scale;     // 3D vector for scale (x, y, z)


        // Default constructor
   // TransformComponent() : modelMatrix(glm::mat4(1.0f)) {}

    TransformComponent(const glm::mat4& matrix) : modelMatrix(matrix) {}
  
  };

#endif  TRANSFORM_COMPONENT_H







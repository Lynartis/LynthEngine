#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<string>

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include"Mesh.h"

class Model
{
public:
	Model() = default;
	
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;

	VAO VAO;
	//Initializes the Model
	Model(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);

	void ModelVaoBinding();
};
#endif

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include <filesystem>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	const char* vertexFile;
	const char* fragmentFile;
	std::string shaderName;
	


	// Constructor that build the Shader Program from 2 different shaders
	Shader(std::string shaderName, const char* vertexFile, const char* fragmentFile);
	void reloadShaders();

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
	void Unbind();

private:
	GLuint vertexShader;    // Store the ID of the vertex shader
	GLuint fragmentShader;  // Store the ID of the fragment shader

	// TO DELETE WHEN CUSTOM LOGGER:
	const std::string RED = "\033[35m";
	const std::string RESET = "\033[0m";

	// Checks if the different Shaders have compiled properly
	bool compileErrors(unsigned int shader, const char* type);

	GLuint createAndCompileShader(GLenum shaderType, const char* shaderSource);
};


#endif
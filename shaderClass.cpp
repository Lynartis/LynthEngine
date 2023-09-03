#include"shaderClass.h"

// Reads a text file and outputs a string with everything in the text file

std::string get_file_contents(const char* filename)
{
	std::string filenameString = filename;
	// Construct the full file path
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::string filePath = currentPath.string() + "/Resources/Shaders/" + filenameString;

	std::ifstream in(filePath, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	std::cout << filePath << std::endl;
	throw std::runtime_error("Error opening file: " + filePath);
}



Shader::Shader(std::string shaderStringName)
{
	shaderName = shaderStringName;

	// Vertex shader source code for a simple passthrough shader
	const char* vertexSource = R"(
		   #version 330 core
	layout (location = 0) in vec3 aPos;

	layout (location = 1) in vec3 aNormal;

	layout (location = 2) in vec3 aColor;

	layout (location = 3) in vec2 aTex;

		out vec2 TexCoords;

		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
			TexCoords = aTex;
		}
    )";

	// Fragment shader source code for a white color
	const char* fragmentSource = R"(
			   #version 330 core
		out vec4 FragColor;
  
		in vec2 TexCoords;

		uniform sampler2D screenTexture;

		void main()
		{ 
			FragColor = texture(screenTexture, TexCoords);
			
		}
    )";

	// Create Vertex Shader Object and get its reference
	vertexShader = createAndCompileShader(GL_VERTEX_SHADER, vertexSource);

	// Create Fragment Shader Object and get its reference
	fragmentShader = createAndCompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();

	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Checks if Shaders linked successfully
	compileErrors(ID, "PROGRAM");
}



// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(std::string shaderStringName, const char* vFile, const char* fragFile)
{
	shaderName = shaderStringName;
	vertexFile = vFile;
	fragmentFile = fragFile;
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	// Checks if Shaders linked succesfully
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	//std::cout << "ShaderProgram class created" << std::endl;

}

void Shader::reloadShaders() {
	// Read new shader source files
	std::string newVertexCode = get_file_contents(vertexFile);
	std::string newFragmentCode = get_file_contents(fragmentFile);

	std::cout <<"Reloading Shaders: " << vertexFile << " - " << fragmentFile <<  std::endl;

	// Convert the shader source strings into character arrays
	const char* newVertexSource = newVertexCode.c_str();
	const char* newFragmentSource = newFragmentCode.c_str();


	// Recreate shaders and relink the program
	GLuint newVertexShader = createAndCompileShader(GL_VERTEX_SHADER, newVertexSource);
	GLuint newFragmentShader = createAndCompileShader(GL_FRAGMENT_SHADER, newFragmentSource);

	// Delete old shaders
	glDetachShader(ID, vertexShader);
	glDetachShader(ID, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Attach new shaders and relink the program
	glAttachShader(ID, newVertexShader);
	glAttachShader(ID, newFragmentShader);
	glLinkProgram(ID);


	// Update shader object state
	vertexShader = newVertexShader;
	fragmentShader = newFragmentShader;


}


// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}



// Checks if the different Shaders have compiled properly
bool Shader::compileErrors(unsigned int shader, const char* type)
{
	
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << RED <<"SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << RESET << std::endl;
			return false;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << RED << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << RESET << std::endl;
			return false;
		}
	}

	return true;
}

GLuint Shader::createAndCompileShader(GLenum shaderType, const char* shaderSource) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	if (compileErrors(shader, (shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT")) 
	{

		return shader;

	}
	else 
	{
		
		std::string errorVertCode = get_file_contents("error.vert");
		std::string errorFragCode = get_file_contents("error.frag");

		std::cout << "Error Shader Applied" << std::endl;

		// Convert the shader source strings into character arrays
		const char* errorVertSource = errorVertCode.c_str();
		const char* errorFragSource = errorFragCode.c_str();


		if (shaderType == GL_VERTEX_SHADER) {

			std::cout << "VertexShader Applied" << std::endl;
			GLuint shaderV = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(shaderV, 1, &errorVertSource, NULL);
			glCompileShader(shaderV);
			return shaderV;
		}
		if (shaderType == GL_FRAGMENT_SHADER) {
			std::cout << "FragmentShader Applied" << std::endl;
			GLuint shaderF = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(shaderF, 1, &errorFragSource, NULL);
			glCompileShader(shaderF);
			return shaderF;
		}
			
	}
	
}




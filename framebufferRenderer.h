#ifndef FRAMEBUFFERRENDERER_CLASS_H
#define FRAMEBUFFERRENDERER_CLASS_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include <string>


class framebufferRenderer
{

public:
	VAO vao;
	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	framebufferRenderer(float width, float height);
	Shader frameBufferShader = Shader("postProcessShader", "postprocessShader.vert", "postprocessShader.frag");
	void Render();
	void Bind();
private:
	void setInt();

};

#endif
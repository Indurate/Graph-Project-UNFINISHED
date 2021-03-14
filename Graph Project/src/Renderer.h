#include <GLM/glm.hpp>
#include "Point.h"
#include "Line.h"
#include "TextRenderer.h"
#include "Shader.h"
#include "ShaderType.h"
#ifndef RENDERER_H
#define RENDERER_H
#pragma once

namespace Renderer {
	void setupShaders();
	Shader& getShader(unsigned int index);
	TextRenderer& getTextRenderer();

	void drawLine(Line& line, glm::vec4 colors);
	void drawConnectedLine(float* positions, int size, glm::vec3 colors);
	void drawRect(float width, float height, float x, float y, glm::vec3 colors);
	void drawRectBorder(float width, float height, float x, float y, glm::vec3 color);
}
#endif

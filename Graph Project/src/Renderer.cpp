#include <GL/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Renderer.h"
#include "ScreenData.h"
#include "Line.h"
#include "ShaderType.h"
#include "TextRenderer.h"

Shader* shader;
Shader* fontShader;
TextRenderer* tRenderer;

void Renderer::setupShaders() {
	shader = new Shader("res/shaders/Basic.shader");
	fontShader = new Shader("res/shaders/Font.shader");
	tRenderer = new TextRenderer("C:/Windows/Fonts/arial.ttf", 50);
}

TextRenderer& Renderer::getTextRenderer() {
	return *tRenderer;
}

Shader& Renderer::getShader(unsigned int index) {
	Shader* ptr = (index == ShaderType::BASIC ? shader : fontShader);
	Shader& ref = *ptr;
	return ref;
}

void Renderer::drawConnectedLine(float* positions, int size, glm::vec3 colors) {
	Renderer::getShader(ShaderType::BASIC).bind();
	Renderer::getShader(ShaderType::BASIC).setUniform4f("u_Color", colors[0], colors[1], colors[2], 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(1);
	float* vertices = (float*) malloc(size * sizeof(float));
	float* end = positions + size;
	int i = 0;
	for (float* p = positions; p != end; ++p) {
		vertices[i++] = *p;
	}
	glColor3f(colors[0], colors[1], colors[2]);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glDrawArrays(GL_POINTS, 0, size);
	glDisableVertexAttribArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDisable(GL_PROGRAM_POINT_SIZE);
	free(vertices);
	Renderer::getShader(ShaderType::BASIC).unbind();
}

void Renderer::drawLine(Line& line, glm::vec4 colors) {
	glEnable(GL_BLEND);
	glBlendFunci(0, GL_SRC_ALPHA, GL_ONE);
	glColor3f(colors[0], colors[1], colors[2]);
	Point& from = line.getFrom();
	Point& to = line.getTo();
	float fromX = from.x / ScreenData::getMaximumX();
	float toX = to.x / ScreenData::getMaximumX();
	float fromY = from.y / ScreenData::getMaximumY();
	float toY = to.y / ScreenData::getMaximumY();
	float positions[4] = {
		fromX, fromY,
		toX, toY
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glDisableVertexAttribArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDisable(GL_BLEND);
}

void Renderer::drawRectBorder(float width, float height, float x, float y, glm::vec3 color) {
	Renderer::getShader(ShaderType::BASIC).bind();
	Renderer::getShader(ShaderType::BASIC).setUniform4f("u_Color", color[0], color[1], color[2], 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	x /= ScreenData::getMaximumX();
	y /= ScreenData::getMaximumY();
	width /= ScreenData::getWidth();
	height /= ScreenData::getHeight();
	float positions[8] = {
		x + width, y + height,
		x + width, y - height,
		x - width, y - height,
		x - width, y + height
	};
	unsigned int indices[8] = {
		0, 1,
		2, 3,
		4, 5,
		6, 7
	};
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_INDEX_ARRAY, 0);
	glBindBuffer(GL_VERTEX_ARRAY, 0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
	glDisableVertexAttribArray(0);
	Renderer::getShader(ShaderType::BASIC).unbind();
	glDisable(GL_BLEND);
}

void Renderer::drawRect(float width, float height, float x, float y, glm::vec3 colors) {
	x /= ScreenData::getMaximumX();
	y /= ScreenData::getMaximumY();
	width /= ScreenData::getWidth();
	height /= ScreenData::getHeight();
	float positions[8] = {
		x + width, y + height,
		x + width, y - height,
		x - width, y - height,
		x - width, y + height
	};
	unsigned int indices[6] = {
		0, 2, 1,
		3, 2, 0
	};
	Renderer::getShader(ShaderType::BASIC).bind();
	Renderer::getShader(ShaderType::BASIC).setUniform4f("u_Color", colors[0], colors[1], colors[2], 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	Renderer::getShader(ShaderType::BASIC).unbind();
	glDisable(GL_BLEND);
}

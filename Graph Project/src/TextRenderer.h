#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "Shader.h"

#pragma once
#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H


class TextRenderer {
private:
	FT_Face face;
	FT_Library ft;
	const char* const fileName;

public:
	int fontSize;

public:
	TextRenderer(const char* const file, int fontSize);
	~TextRenderer();
	void loadFile(const char* const fileName, int fontSize);
	void setFontSize(int fontSize) {
		this->fontSize = fontSize;
		FT_Set_Pixel_Sizes(face, 0, fontSize);
	}
	void loadGlyphs();
	void renderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);

	int getLengthOfString(std::string& text, float scale);
};

#endif //FONT_RENDERER_H

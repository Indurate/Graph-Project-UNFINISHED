#include <GLFW/glfw3.h>
#ifndef SCREEN_DATA_H
#define SCREEN_DATA_H
#pragma once
namespace ScreenData {
	unsigned int getWindow();

	int getHeight();
	int getWidth();

	float getMaximumX();
	float getMaximumY();
	float getMinimumX();
	float getMinimumY();
}

#endif //SCREEN_DATA_H


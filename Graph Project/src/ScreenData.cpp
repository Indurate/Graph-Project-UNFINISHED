#include <freeglut.h>
#include <iostream>
#include "ScreenData.h"

GLFWwindow* window;

unsigned int ScreenData::getWindow() {
	return glutGetWindow();
}

int ScreenData::getHeight() {
	return 800;
}

int ScreenData::getWidth() {
	return 800;
}

float ScreenData::getMaximumX() {
	return ScreenData::getWidth() / 2.0f;
}

float ScreenData::getMaximumY() {
	return ScreenData::getHeight() / 2.0f;
}

float ScreenData::getMinimumX() {
	return -ScreenData::getMaximumX();
}

float ScreenData::getMinimumY() {
	return -ScreenData::getMaximumY();
}
#include "Chart.h"
#include "Renderer.h"
#include "ScreenData.h"

Chart::Chart(float width, float height, float x, float y, ChartType type) : yMultiplier(1), xMultiplier(1) {
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->type = type;
}

float Chart::getFromX() {
	return (ScreenData::getMinimumX() + (ScreenData::getWidth() - this->getWidth()) / 2) + x;
}

float Chart::getToX() {
	return (ScreenData::getMaximumX() - (ScreenData::getWidth() - this->getWidth()) / 2) + x;
}

float Chart::getFromY() {
	return (ScreenData::getMinimumY() + (ScreenData::getHeight() - this->getHeight()) / 2) + y;
}

float Chart::getToY() {
	return (ScreenData::getMaximumY() - (ScreenData::getHeight() - this->getHeight()) / 2) + y;
}


float Chart::getWidth() {
	return this->width;
}

float Chart::getHeight() {
	return this->height;
}

float Chart::getYMultiplier() {
	return this->yMultiplier;
}

float Chart::getXMultiplier() {
	return this->xMultiplier;
}

void Chart::setXMultiplier(float xMultiplier) {
	this->xMultiplier = xMultiplier;
}

void Chart::setYMultiplier(float yMultiplier) {
	this->yMultiplier = yMultiplier;
}

void Chart::setGraphType(ChartType type) {
	this->type = type;
}
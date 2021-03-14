#include "Line.h"
#include "ChartType.h"

#pragma once
#ifndef CHART_H
#define CHART_H

class Chart {
public:
	float width, height;
	float x, y;
	float xMultiplier, yMultiplier;
	ChartType type;
public:
	Chart(float width, float height, float x, float y, ChartType type);

	void setGraphType(ChartType type);

	float getFromX();
	float getToX();

	float getFromY();
	float getToY();

	void setYMultiplier(float yMultiplier);
	void setXMultiplier(float xMultiplier);

	float getYMultiplier();
	float getXMultiplier();

	float getWidth();
	float getHeight();
};

#endif //CHART_H
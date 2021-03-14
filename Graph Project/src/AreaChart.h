#include <map>
#include "Chart.h"

#pragma once
#ifndef AREA_CHART_H
#define AREA_CHART_H

class AreaChart : public Chart {
public:
	AreaChart(float width, float height, float x, float y, ChartType type);
	void render(std::vector<std::pair<long, float>> data, std::string& ticker, long beginSysTime, long endSysTime, float highestPrice, float lowestPrice);
};

#endif //AREA_CHART_H
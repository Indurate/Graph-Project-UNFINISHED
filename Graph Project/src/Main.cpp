#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <freeglut.h>
#include <map>
#include <utility>
#include <functional>
#include <random>
#include <timeapi.h>
#include "ScreenData.h"
#include "Renderer.h"
#include "Line.h"
#include "DataCacher.h"
#include "ShaderType.h"
#include "AreaChart.h"
#include "Chart.h"
#include "ChartType.h"

std::map<Line*, glm::vec4> lines;
std::vector<std::pair<long, float>> map;
float highest = -1;
float lowest = -1;
long systime = 0;
float lineDistance = 0.025f;
float lineVerticalHeight = 0.01f;

void render() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	/*
	std::map<Line*, glm::vec4>::iterator it;
	for (it = lines.begin(); it != lines.end(); ++it) {
		Line& ref = *it->first;
		glm::vec4 colors = it->second;
		Renderer::drawLine(ref, colors);
	}
	for (DataCacher cacher : DataCacheManager::getCachedValues()) {
		Renderer::drawConnectedLine(cacher.getCachedData(), cacher.size, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	}
	*/
	AreaChart chart = AreaChart(ScreenData::getWidth() * 0.25f, ScreenData::getHeight() * 0.25f, ScreenData::getMinimumX() + ScreenData::getMaximumX() * 0.5, 
	ScreenData::getMaximumY() - ScreenData::getMaximumY() * 0.4, ChartType::AREA_CHART);
	std::string ticker = "VIAC";
	chart.render(map, ticker, systime, systime + 1440 * 1000, highest, lowest);
	glutSwapBuffers();
}

void update(int argc) {
	render();
	glutTimerFunc(1000, update, 0);
}

void setupDataSets() {
	std::vector<Point*>& data = *new std::vector<Point*>;
	float y = 1;
	float x = 0;
	while (y <= DataCacheManager::maxY) {
		data.push_back(new Point(x, y));
		data.push_back(new Point(-x, y));
		data.push_back(new Point(x, -y));
		data.push_back(new Point(-x, -y));
		y += y * 0.01;
		x += 2 * 0.01;
	}
	DataCacheManager::addCachedData("data_set_1", *new DataCacher(data));
}

void init() {
	//LINE ON Y AXIS
	lines.insert(std::make_pair(new Line(new Point(0.0, ScreenData::getMaximumY()), new Point(0.0, ScreenData::getMinimumY())), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))); 
	for (float y = ScreenData::getMinimumY(); y < ScreenData::getMaximumY(); y += ScreenData::getHeight() * lineDistance) {
		lines.insert(std::make_pair(new Line(new Point(-ScreenData::getWidth() * (double)lineVerticalHeight, y), new Point(ScreenData::getWidth() * (double)lineVerticalHeight, y)), glm::vec4(1.0f, 1.0f, 1.0, 1.0f)));
	}

	//LINE ON X AXIS
	lines.insert(std::make_pair(new Line(new Point(ScreenData::getMinimumX(), 0.0), new Point(ScreenData::getMaximumX(), 0.0)), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	for (float x = ScreenData::getMinimumX(); x < ScreenData::getMaximumX(); x += ScreenData::getWidth() * lineDistance) {
		lines.insert(std::make_pair(new Line(new Point(x, -ScreenData::getHeight() * (double) lineVerticalHeight), new Point(x, ScreenData::getHeight() * (double) lineVerticalHeight)), glm::vec4(1.0f, 1.0f, 1.0, 1.0f)));
	}
	//INIT OF DATA SETS
	setupDataSets();

	//SETUP SHADER
	Renderer::setupShaders();

	srand(timeGetTime());
	systime = timeGetTime();
	bool positive = false;
	float accum = 100;
	for (int i = 1; i <= 1440; ++i) {
		if (rand() % 25 == 0 || accum == 0) {
			positive = !positive;
		}
		accum += positive ? 1 : -1;
		if (accum > highest) {
			highest = accum;
		}
		if (accum < lowest || lowest == -1) {
			lowest = accum;
		}
		long time = (i - 1) * 1000 + systime;
		map.push_back(std::make_pair(time, accum));
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ScreenData::getWidth(), ScreenData::getHeight());
	glutCreateWindow("Graph Project");
	if (glewInit() != GLEW_OK) {
		std::cout << "Could not init GLEW" << std::endl;
		return -1;
	}
	init();
	glutDisplayFunc(render);
	glutTimerFunc(10, update, 0);
	glutMainLoop();
	return 0;
}
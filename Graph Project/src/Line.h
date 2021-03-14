#include "Point.h" 
#pragma once
#ifndef LINE_H
#define LIME_H

class Line {
public:
	Point* from;
	Point* to;
	const char* name;

public:
	Line(Point* from, Point* to);

	Point& getFrom();
	Point& getTo();
	void setInternalName(const char* name);

	~Line();
};

#endif //LIME_H
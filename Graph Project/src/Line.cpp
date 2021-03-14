#include "Line.h"

Line::Line(Point* from, Point* to) {
	this->from = from;
	this->to = to;
}

Point& Line::getFrom() {
	Point& ref = *from;
	return ref;
}

Point& Line::getTo() {
	Point& ref = *to;
	return ref;
}

void Line::setInternalName(const char* name) {
	this->name = name;
}

Line::~Line() {
	delete from;
	delete to;
}
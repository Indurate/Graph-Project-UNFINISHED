#include <vector>
#include <string>
#include <map>
#include "Point.h"
#pragma once
#ifndef DATA_CACHER_H
#define DATA_CACHER_H

class DataCacher
{
private:
	float* cachedData;

public:
	int size;

public:
	DataCacher(std::vector<Point*> data);
	DataCacher();
	~DataCacher();

	void update(std::vector<Point*> data);

	float* getCachedData();
};

namespace DataCacheManager {
	static double maxX = 100;
	static double maxY = 100;
	static std::map<std::string, DataCacher> cachedData;

	std::map<std::string, DataCacher> getCachedData();

	std::vector<DataCacher> getCachedValues();

	std::vector<std::string> getCachedKeys();

	DataCacher findValue(std::string key);

	void addCachedData(std::string key, DataCacher cacher);
	void removeCachedData(std::string key);
};
#endif //DATA_CACHER_H


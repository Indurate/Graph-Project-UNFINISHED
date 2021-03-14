#include <iostream>
#include "DataCacher.h"

DataCacher::DataCacher(std::vector<Point*> data) {
	update(data);
}

DataCacher::DataCacher() {

}

DataCacher::~DataCacher() {

}

float* DataCacher::getCachedData() {
	return cachedData;
}

void DataCacher::update(std::vector<Point*> data) {
	if (size != data.size()) {
		if (size > 0 && cachedData != NULL) {
			free(cachedData);
		}
		float* positions = (float*) malloc(data.size() * sizeof(float) * 2);
		for (int i = 0; i < data.size(); ++i) {
			Point* point = data[i];
			Point& ref = *point;
			positions[i * 2] = (float) (ref.x / DataCacheManager::maxX);
			positions[i * 2 + 1] = (float) (ref.y / DataCacheManager::maxY);
		}
		this->cachedData = positions;
		size = data.size() * 2;
	}
}

std::map<std::string, DataCacher> DataCacheManager::getCachedData() {
	return cachedData;
}

void DataCacheManager::addCachedData(std::string key, DataCacher cacher) {
	std::string key_string = key;
	cachedData.insert(make_pair(key_string, cacher));
}

void DataCacheManager::removeCachedData(std::string key) {
	DataCacher& cacher = cachedData[key];
	cachedData.erase(key);
	delete &cacher;
}

DataCacher DataCacheManager::findValue(std::string key) {
	std::map<std::string, DataCacher>::iterator it;
	for (it = cachedData.begin(); it != cachedData.end(); ++it) {
		if (it->first == key) {
			return it->second;
		}
	}
	return DataCacher();
}

std::vector<std::string> DataCacheManager::getCachedKeys() {
	std::map<std::string, DataCacher>::iterator it;
	std::vector<std::string> data;
	for (it = cachedData.begin(); it != cachedData.end(); ++it) {
		data.push_back(it->first);
	}
	return data;
}

std::vector<DataCacher> DataCacheManager::getCachedValues() {
	std::map<std::string, DataCacher>::iterator it;
	std::vector<DataCacher> data;
	for (it = cachedData.begin(); it != cachedData.end(); ++it) {
		data.push_back(it->second);
	}
	return data;
}

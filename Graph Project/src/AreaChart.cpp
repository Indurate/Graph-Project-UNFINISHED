#include <map>
#include <Windows.h>
#include "Renderer.h"
#include "ScreenData.h"
#include "AreaChart.h"

enum FormatType {
	N_COMMAS = 0,
	N_DECIMAL = 1
};

AreaChart::AreaChart(float width, float height, float x, float y, ChartType type) : Chart(width, height, x, y, type) {

}

std::string formatString(std::string str, FormatType type) {
	if (type == FormatType::N_DECIMAL) {
		int index = str.find(".");
		if (index == std::string::npos) {
			return str;
		}
		int len = str.length();
		if (len - 3 <= index) {
			return str;
		}
		return str.substr(0, index + 3);
	}
	else if (type == FormatType::N_COMMAS) {
		int end = str.find(".");
		if (end == std::string::npos) {
			end = str.length();
		}
		if (end <= 3) {
			return str;
		}
		int start = end % 3;
		std::string format = str.substr(0, start).append(",");
		int i;
		for (i = start; i <= end - 3; i += 3) {
			format.append(str.substr(i, i + 2)).append(",");
		}
		if (start + 3 <= end) {
			format = format.substr(0, format.find_last_of(","));
		}
		if (end != str.length()) {
			format.append(str.substr(end + 1, str.length()));
		}
		return format;
	}
	return str;
}

void AreaChart::render(std::vector<std::pair<long, float>> data, std::string& ticker, long beginSysTime, long endSysTime, float highestPrice, float lowestPrice) {
	Renderer::drawRectBorder(this->getWidth() + 2, this->getHeight() + 2, this->x, this->y, glm::vec3(1.0f, 1.0f, 1.0f));
	float secondsElapsed = (endSysTime - beginSysTime) / 1000.0f;
	float lastPrice = std::get<1>(data[data.size() - 1]);
	for (int i = 0; i < data.size(); ++i) {
		std::pair<long, float> pair = data[i];
		long time = std::get<0>(pair);
		float price = std::get<1>(pair);
		float width = (1 / (float) secondsElapsed) * this->getWidth();
		float height = (price / highestPrice) * this->getHeight();
		float x = this->getFromX() + ((((time - beginSysTime) / 1000.0f / (float) secondsElapsed) * this->getWidth()) - width / 2);
		float y = this->getFromY() + height / 2;
		Renderer::drawRect(width, height, x, y, glm::vec3(90.0f / 255.0f, 148.0f / 255.0f, 69.0f / 255.0f));
	}
	std::string text = ticker;
	text.append(" - $");
	text.append(formatString(formatString(std::to_string(lastPrice), FormatType::N_COMMAS), FormatType::N_DECIMAL));
	float scale = ((this->getHeight() + this->getWidth()) / (ScreenData::getHeight() + ScreenData::getWidth())) * 1.5;
	float len = Renderer::getTextRenderer().getLengthOfString(text, scale);
	Renderer::getTextRenderer().renderText(Renderer::getShader(ShaderType::FONT), text, this->getFromX() + this->getWidth() / 2 -
	len / 2, this->getFromY() + height + height / 10, scale, glm::vec3(1.0f, 1.0f, 1.0f));
	for (float n = 0; n <= 1; n += 0.2) {
		std::string priceText = "$" + std::to_string((int)(lowestPrice + (highestPrice - lowestPrice) * n)) + " - ";
		Renderer::getTextRenderer().renderText(Renderer::getShader(ShaderType::FONT), priceText, this->getFromX() - this->getWidth() * 0.025 - 
		Renderer::getTextRenderer().getLengthOfString(priceText, scale), this->getFromY() + this->getHeight() * n - 6, scale,
		glm::vec3(1.0f, 1.0f, 1.0f));
	}
}
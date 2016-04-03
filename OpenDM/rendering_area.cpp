#include "main.h"
#include "rendering_area.h"

RenderingArea::RenderingArea() {
	this->renderingArea = std::map<std::pair<int, int>, int>();
	for (int i = 0; i < screenWidth; i += 32) {	
		for (int j = 0; j < screenHeight; j += 32) {
			std::pair<int, int> p = std::pair<int, int>(j, i);
			this->renderingArea.insert(std::pair<std::pair<int, int>, int>(p, 0));
		}
	}
}

std::map<std::pair<int, int>, int> RenderingArea::getRenderingArea() {
	return this->renderingArea;
}
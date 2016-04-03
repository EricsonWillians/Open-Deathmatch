#pragma once
#ifndef RENDERING_AREA_H
#define RENDERING_AREA_H

class RenderingArea {
private:
	std::map<std::pair<int, int>, int> renderingArea;
public:
	RenderingArea();
	~RenderingArea() {};
	std::map<std::pair<int, int>, int> getRenderingArea();
};

#endif
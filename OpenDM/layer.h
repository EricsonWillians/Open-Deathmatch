#pragma once
#ifndef LAYER_H
#define LAYER_H

#include "main.h"

class Layer {
private:
	const char* type;
	const char* name;
	int x;
	int y;
	int width;
	int height;
	bool visible;
	int opacity;
	int offsetx;
	int offsety;
	const char* encoding;
	std::vector<int> data;
public:
	Layer( const char* mapPath, int layerIndex );
	~Layer( void ) {};
	const char* getType( void );
	const char* getName( void );
	int getX(void);
	int getY( void );
	int getWidth( void );
	int getHeight( void );
	bool isVisible( void );
	int getOpacity( void );
	int getOffsetX( void );
	int getOffsetY( void );
	const char* getEncoding( void );
	std::vector<int> getData( void );
};

#endif


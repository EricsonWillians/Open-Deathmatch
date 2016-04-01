#pragma once
#ifndef TILESET_H
#define TILESET_H

#include "main.h"

class Tileset {
private:
	const char* name;
	int firstgid;
	int tilewidth;
	int tileheight;
	int spacing;
	int margin;
	const char* image;
	int imagewidth;
	int imageheight;
	std::map<const char, int> tileoffset;
	int tilecount;
	SDL_Surface* imageSurface;
public:
	Tileset( const char* mapPath, int tilesetIndex );
	~Tileset( void );
	const char* getName( void );
	int getFirstGID( void );
	int getTileWidth( void );
	int getTileHeight( void );
	int getSpacing( void );
	int getMargin( void );
	const char* getImage( void );
	int getImageWidth( void );
	int getImageHeight( void );
	std::map<const char, int> getTileOffset( void );
	int getTileCount( void );
	SDL_Surface* getImageSurface( void );
	std::map<int, SDL_Surface*> getTiles( void );
	void freeTiles( std::map<int, SDL_Surface*>& tiles );
};

#endif
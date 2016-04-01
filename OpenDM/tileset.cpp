#include "tileset.h"

Tileset::Tileset( const char* mapPath, int tilesetIndex ) {
	lua_State* tilesetState = luaL_newstate();
	luaL_dofile( tilesetState, mapPath );
	luaL_openlibs( tilesetState );
	lua_pcall( tilesetState, 0, 0, 0 );
	LuaRef _map = getGlobal( tilesetState, "map" );
	LuaRef tilesets = _map["tilesets"];
	LuaRef tileset = tilesets[tilesetIndex];
	this->name = tileset["name"];
	this->firstgid = tileset["firstgid"];
	this->tilewidth = tileset["tilewidth"];
	this->tileheight = tileset["tileheight"];
	this->spacing = tileset["spacing"];
	this->margin = tileset["margin"];
	this->image = tileset["image"];
	this->imagewidth = tileset["imagewidth"];
	this->imageheight = tileset["imageheight"];
	this->tileoffset = std::map<const char, int>();
	LuaRef tileOffset = tileset["tileoffset"];
	this->tileoffset['x'] = tileOffset["x"];
	this->tileoffset['y'] = tileOffset["y"];
	this->tilecount = tileset["tilecount"];
	this->imageSurface = IMG_Load( this->image ); 
}

Tileset::~Tileset( void ) {
	SDL_FreeSurface( this->imageSurface );
}

const char* Tileset::getName( void ) {
	return this->name;
}

int Tileset::getFirstGID( void ) {
	return this->firstgid;
}

int Tileset::getTileWidth( void ) {
	return this->tilewidth;
}

int Tileset::getTileHeight( void ) {
	return this->tileheight;
}

int Tileset::getSpacing( void ) {
	return this->spacing;
}

int Tileset::getMargin( void ) {
	return this->spacing;
}

const char* Tileset::getImage( void ) {
	return this->image;
}

int Tileset::getImageWidth( void ) {
	return this->imagewidth;
}

int Tileset::getImageHeight( void ) {
	return this->imageheight;
}

std::map<const char, int> Tileset::getTileOffset( void ) {
	return this->tileoffset;
}

int Tileset::getTileCount( void ) {
	return this->tilecount;
}

SDL_Surface* Tileset::getImageSurface( void ) {
	return this->imageSurface;
}

std::map<int, SDL_Surface*> Tileset::getTiles( void ) {
	std::map<int, SDL_Surface*> tiles = std::map<int, SDL_Surface*>();
	int idCounter = 1;
	for (int i = 0; i < this->imagewidth; i += this->tilewidth) {
		for (int j = 0; j < this->imageheight; j += this->tileheight) {
			const SDL_PixelFormat& fmt = *(this->imageSurface->format);
			SDL_Surface* tempSurface = SDL_CreateRGBSurface(
				0, 
				32, 
				32, 
				fmt.BitsPerPixel, 
				fmt.Rmask, 
				fmt.Gmask, 
				fmt.Bmask, 
				fmt.Amask
			);
			SDL_Rect tempRect = { j, i, this->tilewidth, this->tileheight };
			SDL_BlitSurface( this->imageSurface, &tempRect, tempSurface, NULL );
			tiles.insert( std::pair<int, SDL_Surface*>( idCounter, tempSurface ) );
			idCounter++;
		}
	}
	return tiles;
}

void Tileset::freeTiles( std::map<int, SDL_Surface*>& tiles ) {
	for ( std::map<int, SDL_Surface*>::iterator iter = tiles.begin(); iter != tiles.end(); ++iter ) {
		SDL_FreeSurface(iter->second);
	}
}
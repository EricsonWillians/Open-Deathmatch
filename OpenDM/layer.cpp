#include "layer.h"

Layer::Layer(const char* mapPath, int layerIndex) {
	lua_State* layerState = luaL_newstate();
    luaL_dofile( layerState, mapPath );
    luaL_openlibs( layerState );
    lua_pcall( layerState, 0, 0, 0 );
	LuaRef _map = getGlobal( layerState, "map" );
	LuaRef layers = _map["layers"];
	LuaRef layer = layers[layerIndex];
	this->type = layer["type"];
	this->name = layer["name"];
	this->x = layer["x"];
	this->y = layer["y"];
	this->width = layer["width"];
	this->height = layer["height"];
	this->visible = layer["visible"];
	this->opacity = layer["opacity"];
	this->offsetx = layer["offsetx"];
	this->offsety = layer["offsety"];
	this->encoding = layer["encoding"];
	this->data = std::vector<int>();
	LuaRef layerData = layer["data"];
	for (int i = 1; i < layerData.length() + 1; i++) {
		this->data.push_back(layerData[i]);
	}
}

const char* Layer::getType( void ) {
	return this->type;
}

const char* Layer::getName( void ) {
	return this->name;
}

int Layer::getX( void ) {
	return this->x;
}

int Layer::getY( void ) {
	return this->y;
}

int Layer::getWidth( void ) {
	return this->width;
}

int Layer::getHeight( void ) {
	return this->height;
}

bool Layer::isVisible( void ) {
	return this->visible;
}

int Layer::getOpacity( void ) {
	return this->opacity;
}

int Layer::getOffsetX( void ) {
	return this->offsetx;
}

int Layer::getOffsetY( void ) {
	return this->offsety;
}

const char* Layer::getEncoding( void ) {
	return this->encoding;
}

std::vector<int> Layer::getData( void ) {
	return this->data;
}
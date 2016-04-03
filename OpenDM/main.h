#pragma once
#ifndef MAIN_H
#define MAIN_H

# include <iostream>
# include <map>
# include <vector>
# include <SDL.h>
# include <SDL_image.h>
extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}
# include <LuaBridge/LuaBridge.h>
using namespace luabridge;

bool done = false;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event e;
int screenWidth;
int screenHeight;

#endif
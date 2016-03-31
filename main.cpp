# include <iostream>
# include <SDL.h>
extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}
# include <LuaBridge/LuaBridge.h>
using namespace luabridge;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
int screenWidth;
int screenHeight;

int main(int argc, char *argv[]) {
	
	lua_State* cfgState = luaL_newstate();
    luaL_dofile( cfgState, "cfg.lua" );
    luaL_openlibs( cfgState );
    lua_pcall( cfgState, 0, 0, 0 );

	LuaRef v = getGlobal( cfgState, "cfg" );
	screenWidth = v["SCREEN_WIDTH"];
	screenHeight = v["SCREEN_HEIGHT"];

	if ( SDL_Init( SDL_INIT_VIDEO ) != 0 ){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow( "Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
	if ( window == nullptr ){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if (renderer == nullptr){
		SDL_DestroyWindow( window );
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	getchar();
	return 0;
}
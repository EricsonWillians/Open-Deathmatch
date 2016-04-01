#include "OpenDM\main.h"
#include "OpenDM\tileset.h"
#include "OpenDM\layer.h"

bool done = false;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event e;
int screenWidth;
int screenHeight;

int main(int argc, char *argv[]) {
	
	lua_State* cfgState = luaL_newstate();
	luaL_dofile( cfgState, "cfg.lua" );
	luaL_openlibs( cfgState );
	lua_pcall( cfgState, 0, 0, 0 );
	LuaRef t = getGlobal( cfgState, "cfg" );
	screenWidth = t["SCREEN_WIDTH"];
	screenHeight = t["SCREEN_HEIGHT"];

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

	Tileset ts = Tileset("Maps/first.lua", 1);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, ts.getImageSurface());
	SDL_FreeSurface(ts.getImageSurface());

	while (!done) {
		while ( SDL_PollEvent( &e ) != 0 ) {
			if ( e.type == SDL_QUIT ) {
				done = true;
			}
		 }
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, tex, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
	}

	return 0;
}
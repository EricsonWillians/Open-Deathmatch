#include "OpenDM\main.h"
#include "OpenDM\tileset.h"
#include "OpenDM\layer.h"

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

	window = SDL_CreateWindow( "Open Deathmatch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
	if ( window == nullptr ) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if (renderer == nullptr) {
		SDL_DestroyWindow( window );
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	Tileset ts = Tileset("Maps/first.lua", 1);
	Layer l = Layer("Maps/first.lua", 1);
	std::map<int, SDL_Surface*> tiles = ts.getTiles();
	std::map<std::pair<int, int>, SDL_Texture*> renderingArea = std::map<std::pair<int, int>, SDL_Texture*>();
	int indexCounter = 0;
	for (int i = 0; i < 512; i += 32) {	
		for (int j = 0; j < 512; j += 32) {
			std::pair<int, int> p = std::pair<int, int>(j, i);
			renderingArea.insert(std::pair<std::pair<int, int>, 
				SDL_Texture*>(p, SDL_CreateTextureFromSurface(renderer, tiles[l.getData().at(indexCounter)])));
			std::cout << l.getData().at(indexCounter) << '\n';
			indexCounter++;
		}
	}
	ts.freeTiles(tiles);
	while (!done) {
		SDL_RenderClear(renderer);
		for ( std::map<std::pair<int, int>, SDL_Texture*>::iterator iter = renderingArea.begin(); iter != renderingArea.end(); ++iter ) {
			SDL_Rect tempRect = { iter->first.first, iter->first.second, 32, 32 };
			SDL_RenderCopy(renderer, iter->second, NULL, &tempRect);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		while ( SDL_PollEvent( &e ) != 0 ) {
			if ( e.type == SDL_QUIT ) {
				done = true;
			}
		 }
	}

	return 0;
}
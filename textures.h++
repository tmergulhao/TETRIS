#ifndef MOD_TEXTURES
	#define MOD_TEXTURES
	
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_Image.h>
	
	#include <stdbool.h>
	
	#include <iostream>
	#include <map>
	
	using namespace std;
	
	class ClassTextures {
			ClassTextures() {}
			static ClassTextures *p_instance;
			map<string, SDL_Texture*> TextureMap;
		public:
			void load (std::string,std::string, SDL_Renderer*);
			void draw (std::string, int, int, int, int, SDL_Renderer*, SDL_RendererFlip flip = SDL_FLIP_NONE);
			void drawframe (std::string, int, int, int, int, int, int, SDL_Renderer*, SDL_RendererFlip flip = SDL_FLIP_NONE);
			
			static ClassTextures* instance () {
				if (p_instance) return p_instance;
				return (p_instance = new ClassTextures());
			}
	};
	typedef ClassTextures TEXTURES;
#endif

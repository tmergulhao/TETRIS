#include "textures.h++"

ClassTextures* ClassTextures::p_instance = 0;

void ClassTextures::load (std::string FileName,std::string id, SDL_Renderer* Renderer) {
	SDL_Surface* TempSurface = IMG_Load(FileName.c_str());
	SDL_Texture* TempTexture = SDL_CreateTextureFromSurface(Renderer, TempSurface);
	
	SDL_FreeSurface(TempSurface);
	
	TextureMap[id] = TempTexture;
}
void ClassTextures::draw (	std::string id, 
							int x, int y, 
							int width, int height, 
							SDL_Renderer* Renderer, 
							SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w = width;
	destRect.h = srcRect.h = height;
	
	SDL_RenderCopy(Renderer, TextureMap[id], &srcRect, &destRect);
}
void ClassTextures::drawframe (	std::string id, 
								int x, int y, 
								int width, int height, 
								int currentFrame, int currentRow, 
								SDL_Renderer* Renderer, 
								SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w = width;
	destRect.h = srcRect.h = height;
	
	SDL_RenderCopy(Renderer, TextureMap[id], &srcRect, &destRect);
}

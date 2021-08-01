#pragma once

#include "SDL.h"
//#include "GameClass_character.h"

class Store
{
public:
	Store();
	~Store();

	void HandleEvents();
	void Update();
	void Render();

private:

	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;

};

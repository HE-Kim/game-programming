#pragma once

#include "SDL.h"

class Story2
{
public:
	Story2();
	~Story2();
	void HandleEvents();
	void Update();
	void Render();

private: // 
	SDL_Texture * texture;
	SDL_Rect source_rect;
	SDL_Rect destination_rect;
	;
};
#pragma once

#include "SDL.h"

class Story1
{
public:
	Story1();
	~Story1();
	void HandleEvents();
	void Update();
	void Render();

private: // 
	SDL_Texture * texture;
	SDL_Rect source_rect;
	SDL_Rect destination_rect;
	;
};
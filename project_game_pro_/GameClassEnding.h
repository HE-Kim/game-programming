#pragma once

#include "SDL.h"

class Ending
{
public:
	Ending();
	~Ending();
	void HandleEvents();
	void Update();
	void Render();

private: // 
	SDL_Texture * texture;
	SDL_Rect source_rect;
	SDL_Rect destination_rect;
	;
};
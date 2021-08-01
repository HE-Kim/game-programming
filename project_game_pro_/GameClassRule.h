#pragma once

#include "SDL.h"

class Rule
{
public:
	Rule();
	~Rule();
	void HandleEvents();
	void Update();
	void Render();

private: // 
	SDL_Texture * texture;
	SDL_Rect source_rect;
	SDL_Rect destination_rect;
	;
};

#pragma once

#include "SDL.h"
//#include "GameClass_character.h"

class Toilet2
{
public:
	Toilet2();
	~Toilet2();

	void HandleEvents();
	void Update();
	void Render();

private:

	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_1;
	SDL_Rect bg_destination_rectangle_;

	/*
	SDL_Texture * texture_; // the SDL_Texture
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination




	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;


	double character_x_;
	double character_y_;


	bool character[60][80]; */
	//bool arr[60][80];
};




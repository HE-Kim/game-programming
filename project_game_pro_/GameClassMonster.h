#pragma once

#include "SDL.h"


class Monster1
{
public:
	Monster1();
	~Monster1();
	//Stage1(); ~Stage1(); 

	void pre_update();
	void m_Location_false();
	void m_Location_true();
	void Update();
	void Render();

	void key_false();
	void m_destination_redef();
	//	void avoid();

private:
	SDL_Texture * m_texture_;// the SDL_Texture 
							 //SDL_Rect source_rectangle_[8]; // the rectangle for source image
	SDL_Rect m_destination_rectangle_; // for destination
	//SDL_Rect m_rectangle_;

	double mon_x_;
	double  mon_y_;
	bool mon_go_left_;
	bool mon_go_right_;
	bool mon_go_up_;
	bool mon_go_down_;



	//bool arr[60][80];
	//bool character[60][80]; //따로 class 만들어서 하면 될듯
};
class Monster2
{
public:
	Monster2();
	~Monster2();
	//Stage1(); ~Stage1(); 

	void pre_update();
	void m_Location_false();
	void m_Location_true();
	void Update();
	void Render();

	void key_false();
	void m_destination_redef();
	void red_mon_init();
	//	void avoid();

private:
	SDL_Texture * m_texture_;// the SDL_Texture 
							 //SDL_Rect source_rectangle_[8]; // the rectangle for source image
	SDL_Rect m_destination_rectangle_; // for destination
	SDL_Rect m_rectangle_;

	double mon_x_;
	double  mon_y_;
	bool mon_go_left_;
	bool mon_go_right_;
	bool mon_go_up_;
	bool mon_go_down_;

};
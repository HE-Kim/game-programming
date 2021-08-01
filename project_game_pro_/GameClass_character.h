#pragma once

#include "SDL.h"


class Character
{
public:
	Character();
	~Character();
	//Stage1(); ~Stage1(); 
	
	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();
	void key_event_false();
	void destination_redef();
	
	


private:
	SDL_Texture * texture_;// the SDL_Texture 
	//SDL_Rect source_rectangle_[8]; // the rectangle for source image
	SDL_Rect c_rectangle_;
	SDL_Rect destination_rectangle_; // for destination
	SDL_Texture* f_texture_; //  SDL_Texture variable
	SDL_Rect f_source_rectangle_;
	SDL_Rect f_destination_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	SDL_Texture *info;
	SDL_Rect info_rect;
	SDL_Rect i;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
*/
	//int c_move_index;
	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	



	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};

class Character2  //룸1 
{
public:
	Character2();
	~Character2();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();
	void cnt_check();
	void key_event_false();
	void destination_redef();

private:
	SDL_Texture * texture_; // the SDL_Texture 
	//SDL_Rect source_rectangle_[8]; // the rectangle for source image
	//SDL_Rect destination_rectangle_; // for destination
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;
	//double character_x_;
	//double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};
class Character3 //무비1
{
public:
	Character3();
	~Character3();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();
private:
	SDL_Texture * texture_; // the SDL_Texture 
    //SDL_Rect source_rectangle_[8]; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;
	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};

class Character4 //화장실1
{
public:
	Character4();
	~Character4();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();



private:
	SDL_Texture * texture_; // the SDL_Texture 
	//SDL_Rect source_rectangle_[8]; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};
class Character5  //홀2
{
public:
	Character5();
	~Character5();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();



private:
	SDL_Texture * texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_[8]; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	
	SDL_Texture* s_texture_; //  SDL_Texture variable
	SDL_Rect s_source_rectangle_;
	SDL_Rect s_destination_rectangle_;
	
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;

	

	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};
class Character6 //룸2
{
public:
	Character6();
	~Character6();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();

private:
	SDL_Texture * texture_; // the SDL_Texture 
	 // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;

	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};
class Character7 //화장실2
{
public:
	Character7();
	~Character7();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();



private:
	SDL_Texture * texture_; // the SDL_Texture 
							// the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};
class Character8 //룸3
{
public:
	Character8();
	~Character8();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();



private:
	SDL_Texture * texture_; // the SDL_Texture 
							// the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* g_texture_; //  SDL_Texture variable
	SDL_Rect g_source_rectangle_;
	SDL_Rect g_destination_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};

class Character10// 무비2
{
public:
	Character10();
	~Character10();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();
	


private:
	SDL_Texture * texture_; // the SDL_Texture 
							// the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};

class Character11// 룸4
{
public:
	Character11();
	~Character11();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();
	void key_event_false();
	void destination_redef();
	

private:
	SDL_Texture * texture_; // the SDL_Texture 
							// the rectangle for source image
	//SDL_Rect destination_rectangle_; // for destination
	//SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;

	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};

class Character12// 휴게실
{
public:
	Character12();
	~Character12();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();

private:
	
	SDL_Texture * texture_1; // the SDL_Texture 
							// the rectangle for source image
	SDL_Rect destination_rectangle_1; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;

	SDL_Texture* hint2_texture_; //  SDL_Texture variable
	SDL_Rect hint2_source_rectangle_;
	SDL_Rect hint2_destination_rectangle_;

	SDL_Texture *door;
	SDL_Rect door_rect;
	SDL_Rect d;

	SDL_Texture *water;
	SDL_Rect water_rect;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};

class Character13//창고
{
public:
	Character13();
	~Character13();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();

private:
	SDL_Texture * texture_; // the SDL_Texture 			// the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};

class Character14//스토어
{
public:
	Character14();
	~Character14();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();

private:
	SDL_Texture * texture_; // the SDL_Texture 			// the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect c_rectangle_;
	SDL_Texture* hint1_texture_; //  SDL_Texture variable
	SDL_Rect hint1_source_rectangle_;
	SDL_Rect hint1_destination_rectangle_;
	/*
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;
	*/
	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};
class Character15 //인벤토리
{
public:
	Character15();
	~Character15();
	//Stage1(); ~Stage1(); 

	void HandleEvents();
	void Location_false();
	void Location_true();
	void Update();
	void Render();

private:
	SDL_Texture * texture_; // the SDL_Texture 			// the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	SDL_Rect c_rectangle_;
	SDL_Texture* s1_texture_; //  SDL_Texture variable

	SDL_Rect s1_destination_rectangle_;

	SDL_Texture* s2_texture_; //  SDL_Texture variable

	SDL_Rect s2_destination_rectangle_;
	SDL_Texture* s3_texture_; //  SDL_Texture variable

	SDL_Rect s3_destination_rectangle_;
	SDL_Texture* s4_texture_; //  SDL_Texture variable

	SDL_Rect s4_destination_rectangle_;

	SDL_Texture* i_texture_;
	SDL_Rect i_destination_rectangle_;

	SDL_Rect i2_destination_rectangle_;
	SDL_Rect i3_destination_rectangle_;
	SDL_Rect i4_destination_rectangle_;
	SDL_Rect i5_destination_rectangle_;
	SDL_Rect i6_destination_rectangle_;

	SDL_Rect h1_destination_rectangle_;
	SDL_Rect h2_destination_rectangle_;
	SDL_Rect h3_destination_rectangle_;
	SDL_Texture* bg_texture_; //  SDL_Texture variable
	SDL_Rect bg_source_rectangle_;
	SDL_Rect bg_destination_rectangle_;

	//int c_move_index;

	double character_x_;
	double character_y_;
	bool character_go_left_;
	bool character_go_right_;
	bool character_go_up_;
	bool character_go_down_;
	//	int character_x_;
	//int character_y_;

	//bool arr[60][80];
	bool character[60][80]; //따로 class 만들어서 하면 될듯
};
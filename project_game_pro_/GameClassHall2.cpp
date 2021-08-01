#include "GameClassHall2.h"
#include "GameClassPhase.h"
#include "GameClass_character.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_ttf.h"
#include <atlstr.h>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
static bool arr[60][80];
int h2_move_index;
extern int g_frame_time_ms;
SDL_Rect source_rectangle_h2[12];
extern int key_cnt;
int hint1_cnt=0;
int hint1_render=0;
int hint2_render = 0;
extern int inventory_cnt;
TTF_Font *game_font1;
SDL_Texture *statue;
SDL_Rect statue_rect;
SDL_Rect s;

SDL_Texture *warehouse;
SDL_Rect warehouse_rect;
SDL_Rect w;


extern bool red_mon;
extern bool red_dis;
extern bool check_red;
Hall2::Hall2()
{


	SDL_Surface* bg_surface = IMG_Load("../Resources/hall_2.png");

	bg_destination_rectangle_.x = bg_source_rectangle_.x = 0;
	bg_destination_rectangle_.y = bg_source_rectangle_.y = 0;
	bg_destination_rectangle_.w = bg_source_rectangle_.w = bg_surface->w;
	bg_destination_rectangle_.h = bg_source_rectangle_.h = bg_surface->h;

	bg_texture_ = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);


	arr[60][80] = false;

	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (i == 0 || i == 59 || j == 0 || j == 79)
				arr[i][j] = true;

			if (i > 9 && i <20 && j > 29 && j < 50) //i==y j==x라고 생각하면 편험
				arr[i][j] = true;

		}
	}
	

}
Character5::Character5()
{
	//stage1_cnt++;

	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;

	character[60][80] = false;


	//처음 시작할 떄 만 !! 
	/*if (stage1_cnt > 1)
	{
	character_x_ = save_stage1_x;
	character_y_ = save_stage1_y;
	}
	else*/
	{
		character_x_ = 380;
		character_y_ = 460;
	}

	game_font1 = TTF_OpenFont("../Resources/PFStardust.ttf", 25);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font1, CW2A(L"내 검이 필요하오..", CP_UTF8), white);
	SDL_Surface *tmp_surface2 = TTF_RenderUTF8_Blended(game_font1, CW2A(L"문이 잠겨있다..   ", CP_UTF8), white);
	statue_rect.x = 0;
	statue_rect.y = 0;
	statue_rect.w = tmp_surface1->w;
	statue_rect.h = tmp_surface1->h;
	statue = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
	SDL_FreeSurface(tmp_surface1);
	
	
	warehouse_rect.x = 0;
	warehouse_rect.y = 0;
	warehouse_rect.w = tmp_surface2->w;
	warehouse_rect.h = tmp_surface2->h;

	warehouse = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
	SDL_FreeSurface(tmp_surface2);
	
	TTF_CloseFont(game_font1);


	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/mon.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface); //character's texture 
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_h2[0].w, &source_rectangle_h2[0].h); //png img 

																							   //이딴 식으로 해야함
	source_rectangle_h2[0].x = 0;
	source_rectangle_h2[0].y = 200;
	source_rectangle_h2[0].w = 70;
	source_rectangle_h2[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_h2[i].x += source_rectangle_h2[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_h2[i].y = 200;
		source_rectangle_h2[i].w = 70;
		source_rectangle_h2[i].h = 100;
		


	}

	destination_rectangle_.x = (int)character_x_;
	destination_rectangle_.y = (int)character_y_;
	destination_rectangle_.w = 40;// source_rectangle_[0].w;// / 5;
	destination_rectangle_.h =60;//source_rectangle_[0].h; // / 9;

								   //destination_rectangle_.x를 대체할 것이 무엇인가~~?

	c_rectangle_.x = destination_rectangle_.x / 10;
	c_rectangle_.y = destination_rectangle_.y / 10;
	c_rectangle_.w = destination_rectangle_.w / 10;
	c_rectangle_.h = destination_rectangle_.h / 10;

	// character의 좌표
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
									  
	h2_move_index = 0;

	SDL_Surface* s_surface = IMG_Load("../Resources/statue.png");
	SDL_SetColorKey(s_surface, 1, SDL_MapRGB(s_surface->format, 255, 255, 255));
	s_texture_ = SDL_CreateTextureFromSurface(g_renderer, s_surface);

	SDL_FreeSurface(s_surface);

	s_source_rectangle_.x = 0;
	s_source_rectangle_.y = 0;
	s_source_rectangle_.w = 800;
	s_source_rectangle_.h = 600;

	s_destination_rectangle_.x = 0;
	s_destination_rectangle_.y = 0;
	s_destination_rectangle_.w = 800;
	s_destination_rectangle_.h = 600;

	SDL_QueryTexture(s_texture_, NULL, NULL, &s_source_rectangle_.w, &s_source_rectangle_.h);

	SDL_Surface* hint1_surface = IMG_Load("../Resources/hint_1.png");
	SDL_SetColorKey(hint1_surface, 1, SDL_MapRGB(hint1_surface->format, 255, 255, 255));
	hint1_texture_ = SDL_CreateTextureFromSurface(g_renderer, hint1_surface);

	SDL_FreeSurface(hint1_surface);

	hint1_source_rectangle_.x = 0;
	hint1_source_rectangle_.y = 0;
	hint1_source_rectangle_.w = 800;
	hint1_source_rectangle_.h = 600;

	hint1_destination_rectangle_.x = 0;
	hint1_destination_rectangle_.y = 0;
	hint1_destination_rectangle_.w = 800;
	hint1_destination_rectangle_.h = 600;

	SDL_QueryTexture(hint1_texture_, NULL, NULL, &hint1_source_rectangle_.w, &hint1_source_rectangle_.h);


}
Character5::~Character5()
{
	SDL_DestroyTexture(texture_);
}

Hall2::~Hall2()
{
	SDL_DestroyTexture(bg_texture_);
}

void Hall2::Update()
{

}

void Character5::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character5::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}



void Character5::Update()
{
	red_mon = true;
	red_dis = false;

	

	if (character_go_left_)
	{
		if (h2_move_index < 2)
			h2_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();


	

		h2_move_index++;

		if (h2_move_index >3)
			h2_move_index = 2;
	
	}
	else if (character_go_right_)
	{
		if (h2_move_index < 6)
			h2_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();

		h2_move_index++;
		if (h2_move_index >7)
			h2_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (h2_move_index < 10)
			h2_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;

		Location_true();
		h2_move_index++;
		if (h2_move_index >11)
			h2_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		Location_true();

		h2_move_index++;
		if (h2_move_index >1)
			h2_move_index = 0;
	}

	//x
	for (int i = 0; i < 60; i++)
	{
		if (character[i][0] == true)
		{
			//x랑 y를 바꿔서 생각해야해

			Location_false();
			character_x_ += 10;
			destination_rectangle_.x = (int)character_x_;
			c_rectangle_.x = destination_rectangle_.x / 10;
		}
		if (character[i][79] == true)
		{

			Location_false();
			character_x_ -= 10.;
			destination_rectangle_.x = (int)character_x_;
			c_rectangle_.x = destination_rectangle_.x / 10;
		}

		// 네모 피하기
		
		// 왼벽 피하기
		if (i > 8 && i < 25)
		{
			if (character[i][3] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		
		
		// 왼벽 피하기
		if (i > 25 && i < 35)
		{
			if (character[i][1] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		// 왼벽 피하기
		if (i > 35 && i < 41)
		{
			if (character[i][4] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		// 왼벽 피하기
		if (i > 41 && i < 51)
		{
			if (character[i][1] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		// 왼벽 피하기
		if (i > 51 && i < 55)
		{
			if (character[i][4] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}

		// 오른벽 피하기
		if (i > 8 && i < 25)
		{
			if (character[i][76] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		//오른벽 피하기
		if (i > 25 && i < 37)
		{
			if (character[i][79] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		//오른벽 피하기
		if (i > 37 && i < 45)
		{
			if (character[i][76] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		//오른벽 피하기
		if (i > 45 && i < 59)
		{
			if (character[i][79] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		if (i > 4 && i < 14)
		{
			if (character[i][49] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
	
	}

	//y
	for (int i = 0; i < 80; i++)
	{
		if (character[0][i] == true)
		{
			Location_false();
			character_y_ += 10.;
			destination_rectangle_.y = (int)character_y_;
			c_rectangle_.y = destination_rectangle_.y / 10;
		}
		else if (character[59][i] == true)
		{

			Location_false();
			character_y_ -= 10.;
			destination_rectangle_.y = (int)character_y_;
			c_rectangle_.y = destination_rectangle_.y / 10;
		}

		
		//벽장 피하기
		if (i > 0 && i < 48)
		{
			if (character[8][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		//벽 피하기
		if (i > 76 && i < 79)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}

		//아래벽 피하기
		if (i > 76 && i < 79)
		{
			if (character[26][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		//아래벽 피하기
		if (i > 0 && i <= 34)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		//아래벽 피하기
		if (i >=48 && i <= 79)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		//아래벽 피하기
		if (i > 76 && i < 79)
		{
			if (character[36][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		//아래벽 피하기
		if (i > 4 && i < 75)
		{
			if (character[59][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		if (i > 47 && i < 79)
		{
			if (character[13][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
	}

	//대화창
	if (character_x_ >= 570 && character_x_ <= 610 && character_y_ <= 170 && character_y_ >= 139) {
		hint2_render = 1;
		if (hint1_cnt > 1) {
			hint1_cnt = 0;
			hint2_render = 0;
		}
	}
  
	if (character_x_ >= 350 && character_x_ <= 420 && character_y_ <= 320 && character_y_ >= 319) {
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
	
	}
	
	if (character_x_ >= 350 && character_x_ <= 420 && character_y_ <= 330 && character_y_ >= 319) {
		hint1_render = 1;

		if (hint1_cnt > 1) {
			hint1_cnt = 0;
			hint1_render = 0;
		}
	}
	if (character_x_ >= 350 && character_x_ <= 420 && character_y_ <= 290 && character_y_ >= 289) {
		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
	}

}


void Hall2::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);


	
}

void Character5::Render()
{
	s.x = 130;
	s.y = 450;
	s.w = statue_rect.w;
	s.h = statue_rect.h;

	

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_h2[h2_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	if (character_x_ >= 330 && character_x_ <= 460 && character_y_ <= 300) {
		SDL_RenderCopy(g_renderer, s_texture_, &s_source_rectangle_, &s_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (hint1_render == 1 && hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		
		SDL_RenderCopy(g_renderer, statue, 0, &s);
		SDL_RenderPresent(g_renderer);
	}
	if (hint2_render == 1 && hint1_cnt ==1 &&key_cnt==0 ) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, warehouse, 0, &s);
		SDL_RenderPresent(g_renderer);
	}
}

void Hall2::HandleEvents()
{
}

void Character5::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:
			// If the left arrow key is pressed. 
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				character_go_left_ = true;
				if (hint2_render == 1 && hint1_cnt == 1&&key_cnt==0) {
					character_go_left_ = false;
				}
				if ( hint1_render == 1 && hint1_cnt == 1) {
					character_go_left_ = false;
				}
				{

					for (int i = 0; i < 7; i++) {
						for (int j = 41; j < 45; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Room3;
							}

						}
					}
				}
				{

					for (int i = 0; i < 7; i++) {
						for (int j = 25; j < 30; j++) {
							if (character[j][i] == true)
							{
								
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Lounge;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (hint2_render == 1 && hint1_cnt == 1 && key_cnt == 0) {
					character_go_right_ = false;
				}
				if (hint1_render == 1 && hint1_cnt == 1) {
					character_go_right_ = false;
				}
				
					
				{

					for (int i = 71; i < 80; i++) {
						for (int j = 26; j < 31; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Toilet2;
							}

						}
					}
				}
				{

					for (int i = 71; i < 80; i++) {
						for (int j = 45; j < 51; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Room4;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (hint2_render == 1 && hint1_cnt == 1 && key_cnt == 0) {
					character_go_up_ = false;
				}
				if ( hint1_render == 1 && hint1_cnt == 1) {
					character_go_up_ = false;
				}
				{

					for (int i = 57; i < 61; i++) {
						for (int j = 13; j < 17; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								
								//g_current_game_phase = PHASE_Warehouse;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;

				if (hint2_render == 1 && hint1_cnt == 1 && key_cnt == 0) {
					character_go_down_ = false;
				}
				if (hint1_render == 1 && hint1_cnt == 1) {
					character_go_down_ = false;
				}
				{

					for (int i = 34; i < 46; i++) {
						for (int j = 54; j < 60; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Hall1;
							}

						}
					}
				}
				
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (character_x_ >= 570 && character_x_ <= 610 && character_y_ <= 140 && character_y_ >= 139) {
					hint1_cnt++;
					hint1_render = 0;
				}
				if (character_x_ >= 350 && character_x_ <= 420 && character_y_ <= 330 && character_y_ >= 319) {
					hint1_cnt++;
					hint2_render = 0;
				}
				if (character_x_ >= 570 && character_x_ <= 610 && character_y_ <= 140 && character_y_ >= 139 && key_cnt >= 1)
				{
					g_current_game_phase = PHASE_Warehouse;
					hint2_render = 0;
					hint1_render = 0;
				}

			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 5;
				g_current_game_phase = PHASE_Inventory;

			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				character_go_left_ = false;
				{

					for (int i = 0; i < 7; i++) {
						for (int j = 41; j < 46; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Room3;
							}

						}
					}
				}
				{

					for (int i = 0; i < 7; i++) {
						for (int j = 25; j < 30; j++) {
							if (character[j][i] == true)
							{

								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Lounge;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = false;
				{

					for (int i = 71; i < 80; i++) {
						for (int j = 26; j < 31; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;

								g_current_game_phase = PHASE_Toilet2;
							}

						}
					}
					{

						for (int i = 71; i < 80; i++) {
							for (int j = 46; j < 51; j++) {
								if (character[j][i] == true)
								{
									//	stage1_cnt = true;

									/*Location_false();
									character_x_ -= 20.;
									destination_rectangle_.x = (int)character_x_;
									c_rectangle_.x = destination_rectangle_.x / 10;
									Location_true();*/

									//save_stage2_x = destination_rectangle_.x;
									//save_stage2_y = destination_rectangle_.y;
									//phase_2();
									character_go_left_ = false;
									character_go_right_ = false;
									character_go_up_ = false;
									character_go_down_ = false;
									g_current_game_phase = PHASE_Room4;
								}

							}
						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = false;
				{

					for (int i = 57; i < 61; i++) {
						for (int j = 13; j < 22; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								//g_current_game_phase = PHASE_Warehouse;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = false;
				{

					for (int i = 34; i < 46; i++) {
						for (int j = 54; j < 60; j++) {
							if (character[j][i] == true)
							{
								//	stage1_cnt = true;

								/*Location_false();
								character_x_ -= 20.;
								destination_rectangle_.x = (int)character_x_;
								c_rectangle_.x = destination_rectangle_.x / 10;
								Location_true();*/

								//save_stage2_x = destination_rectangle_.x;
								//save_stage2_y = destination_rectangle_.y;
								//phase_2();
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Hall1;
							}

						}
					}
				}
			}
			
			
			break;


		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				//g_current_game_phase = PHASE_Inventory;
			}
			break;

		default:
			break;
		}
	}
}
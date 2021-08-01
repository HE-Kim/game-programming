#include "GameClassRoom3.h"
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
int r3_move_index;
extern int g_frame_time_ms;
extern int inventory_cnt;

int p_hint1_cnt = 0;
int p_hint1_render = 0;
int p_hint2_render = 0;
int p_hint3_render = 0;

TTF_Font *game_font_p;
SDL_Texture *man;
SDL_Rect man_rect;
SDL_Rect m;

SDL_Texture *girl;
SDL_Rect girl_rect;
SDL_Texture *glass;
SDL_Rect glass_rect;

SDL_Rect source_rectangle_r3[12];

Room3::Room3()
{
	SDL_Surface* bg_surface = IMG_Load("../Resources/room_3.png");

	bg_destination_rectangle_.x = bg_source_rectangle_1.x = 0;
	bg_destination_rectangle_.y = bg_source_rectangle_1.y = 0;
	bg_destination_rectangle_.w = bg_source_rectangle_1.w = bg_surface->w;
	bg_destination_rectangle_.h = bg_source_rectangle_1.h = bg_surface->h;

	bg_texture_ = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	//arr[60][80] = false;

	/*for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (i == 0 || i == 59 || j == 0 || j == 79)
				arr[i][j] = true;

			if (i > 9 && i <20 && j > 29 && j < 50) //i==y j==x라고 생각하면 편험
				arr[i][j] = true;

		}
	}*/

}
Character8::Character8()
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
		character_x_ = 700;
		character_y_ = 180;
	}
	game_font_p = TTF_OpenFont("../Resources/PFStardust.ttf", 25);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font_p, CW2A(L"앞방에서 누가 떠드는군.", CP_UTF8), white);
	SDL_Surface *tmp_surface2 = TTF_RenderUTF8_Blended(game_font_p, CW2A(L"집에 두고온 물건이 있는데...", CP_UTF8), white);
	SDL_Surface *tmp_surface3 = TTF_RenderUTF8_Blended(game_font_p, CW2A(L"유리가 열리지 않는다", CP_UTF8), white);
	man_rect.x = 0;
	man_rect.y = 0;
	man_rect.w = tmp_surface1->w;
	man_rect.h = tmp_surface1->h;
	man = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
	SDL_FreeSurface(tmp_surface1);


	girl_rect.x = 0;
	girl_rect.y = 0;
	girl_rect.w = tmp_surface2->w;
	girl_rect.h = tmp_surface2->h;

	girl = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
	SDL_FreeSurface(tmp_surface2);

	glass_rect.x = 0;
	glass_rect.y = 0;
	glass_rect.w = tmp_surface3->w;
	glass_rect.h = tmp_surface3->h;

	glass = SDL_CreateTextureFromSurface(g_renderer, tmp_surface3);
	SDL_FreeSurface(tmp_surface3);
	TTF_CloseFont(game_font_p);

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


	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/mon.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface); //character's texture 
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_r3[0].w, &source_rectangle_r3[0].h); //png img 

																							   //이딴 식으로 해야함
	source_rectangle_r3[0].x = 0;
	source_rectangle_r3[0].y = 200;
	source_rectangle_r3[0].w = 70;
	source_rectangle_r3[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_r3[i].x += source_rectangle_r3[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_r3[i].y = 200;
		source_rectangle_r3[i].w = 70;
		source_rectangle_r3[i].h = 100;



	}

	destination_rectangle_.x = (int)character_x_;
	destination_rectangle_.y = (int)character_y_;
	destination_rectangle_.w = 40;// source_rectangle_1[0].w;// / 5;
	destination_rectangle_.h = 60;//source_rectangle_1[0].h; // / 9;

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
																					   
	r3_move_index = 0;
	
	SDL_Surface* g_surface = IMG_Load("../Resources/glass.png");
	SDL_SetColorKey(g_surface, 1, SDL_MapRGB(g_surface->format, 255, 255, 255));
	g_texture_ = SDL_CreateTextureFromSurface(g_renderer, g_surface);

	SDL_FreeSurface(g_surface);

	g_source_rectangle_.x = 0;
	g_source_rectangle_.y = 0;
	g_source_rectangle_.w = 800;
	g_source_rectangle_.h = 600;

	g_destination_rectangle_.x = 0;
	g_destination_rectangle_.y = 0;
	g_destination_rectangle_.w = 800;
	g_destination_rectangle_.h = 600;

	SDL_QueryTexture(g_texture_, NULL, NULL, &g_source_rectangle_.w, &g_source_rectangle_.h);

	arr[60][80] = false;
    
}
Character8::~Character8()
{
	SDL_DestroyTexture(texture_);
}

Room3::~Room3()
{
	SDL_DestroyTexture(bg_texture_);
}

void Room3::Update()
{

}

void Character8::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character8::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}



void Character8::Update()
{
	/*for (int i = 50; i < 56; i++)
	{
	if (character[i][2] == true)
	{
	stage2_cnt = true;

	/*Location_false();
	character_x_ += 10.;
	destination_rectangle_.x = (int)character_x_;
	c_rectangle_.x = destination_rectangle_.x / 10;
	Location_true();
	//save_stage1_x = destination_rectangle_.x;
	//save_stage1_y= destination_rectangle_.y;

	//g_current_game_phase = PHASE_STAGE2;
	phase_1();
	}
	}*/


	// 확인하기
	/*if (stage1_cnt == true)
	{
	/*character_x_ = save_stage1_x;
	character_y_ = save_stage1_y;
	stage1_cnt = 0;

	Location_false();
	character_x_= 50.;
	destination_rectangle_.x = (int)character_x_;
	c_rectangle_.x = destination_rectangle_.x / 10;
	Location_true();
	stage1_cnt = false;
	}*/

	

	if (character_go_left_)
	{
		if (r3_move_index < 2)
			r3_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();



		r3_move_index++;

		if (r3_move_index >3)
			r3_move_index = 2;
		

	}
	else if (character_go_right_)
	{
		if (r3_move_index < 6)
			r3_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();

		r3_move_index++;
		if (r3_move_index >7)
			r3_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (r3_move_index < 10)
			r3_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;

		Location_true();
		r3_move_index++;
		if (r3_move_index >11)
			r3_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		Location_true();

		r3_move_index++;
		if (r3_move_index >1)
			r3_move_index = 0;
	}

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
			character_x_ -= 10;
			destination_rectangle_.x = (int)character_x_;
			c_rectangle_.x = destination_rectangle_.x / 10;
		}

		
		if (i > 24 && i < 47)
		{
			if (character[i][9] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		if (i > 10 && i < 23)
		{
			if (character[i][1] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		if (i > 10 && i < 17)
		{
			if (character[i][76] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		if (i > 17 && i < 27)
		{
			if (character[i][79] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		if (i > 27 && i < 59)
		{
			if (character[i][76] == true)
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
			character_y_ += 10;
			destination_rectangle_.y = (int)character_y_;
			c_rectangle_.y = destination_rectangle_.y / 10;
		}
		else if (character[59][i] == true)
		{

			Location_false();
			character_y_ -= 10;
			destination_rectangle_.y = (int)character_y_;
			c_rectangle_.y = destination_rectangle_.y / 10;
		}

		
		//윗벽 피하기
		if (i > 0 && i < 75)
		{
			if (character[10][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		//아래벽 피하기
		if (i > 2 && i < 9)
		{
			if (character[25][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		//아래벽 피하기
		if (i > 1 && i < 75)
		{
			if (character[49][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
	}
	//대화창
	if (character_x_ >= 230 && character_x_ <= 310 && character_y_ <= 110 && character_y_ >= 0) {
		p_hint1_render = 1;
		p_hint2_render = 0;
		p_hint3_render = 0;
		if (p_hint1_cnt > 1) {
			p_hint1_cnt = 0;
			p_hint1_render = 0;
		}
	}
	if (character_x_ >= 400 && character_x_ <= 500 && character_y_ >= 0 && character_y_ <= 110) {
		p_hint1_render = 0;
		p_hint2_render = 1;
		p_hint3_render = 0;
		if (p_hint1_cnt > 1) {
			p_hint1_cnt = 0;
			p_hint2_render = 0;
		}
	}
	
	
	
	
	
	
	//폭탄전시 피하기
	if (character_x_ >= 420 && character_x_ <= 600 && character_y_ <= 360 && character_y_ >= 359) {
		p_hint1_render = 0;
		p_hint2_render = 0;
		p_hint3_render = 1;
		if (p_hint1_cnt > 1) {
			p_hint1_cnt = 0;
			p_hint3_render = 0;
		}
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		
	}
	if (character_x_ >= 420 && character_x_ <= 600 && character_y_ <= 330 && character_y_ >= 329) {
		p_hint1_render = 0;
		p_hint2_render = 0;
		p_hint3_render = 1;
		if (p_hint1_cnt > 1) {
			p_hint1_cnt = 0;
			p_hint3_render = 0;
		}
		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		
	}

}


void Room3::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_1, &bg_destination_rectangle_);


}

void Character8::Render()
{
	m.x = 130;
	m.y = 450;
	m.w = man_rect.w;
	m.h = man_rect.h;

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_r3[r3_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	
	if (character_x_ >= 420 && character_x_ <= 600 && character_y_ <= 360) {
		SDL_RenderCopy(g_renderer, g_texture_, &g_source_rectangle_, &g_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (p_hint1_render == 1 && p_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, man, 0, &m);
		SDL_RenderPresent(g_renderer);
	}
	if (p_hint2_render == 1 && p_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, girl, 0, &m);
		SDL_RenderPresent(g_renderer);
	}
	if (p_hint3_render == 1 && p_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, glass, 0, &m);
		SDL_RenderPresent(g_renderer);
	}
}

void Room3::HandleEvents()
{
}

void Character8::HandleEvents()
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
				if (p_hint1_render == 1 && p_hint1_cnt == 1 && p_hint2_render == 0) {
					character_go_left_ = false;
				}
				if (p_hint2_render == 1 && p_hint1_cnt == 1 && p_hint1_render == 0) {
					character_go_left_ = false;
				}
				if (p_hint3_render == 1 && p_hint1_cnt == 1 && p_hint1_render == 0) {
					character_go_left_ = false;
				}
				//for (int i = 50; i < 56; i++)
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (p_hint1_render == 1 && p_hint1_cnt == 1 && p_hint2_render == 0) {
					character_go_right_ = false;
				}
				if (p_hint2_render == 1 && p_hint1_cnt == 1 && p_hint1_render == 0) {
					character_go_right_ = false;
				}
				if (p_hint3_render == 1 && p_hint1_cnt == 1 && p_hint1_render == 0) {
					character_go_right_ = false;
				}
				{

					for (int i = 72; i < 80; i++) {
						for (int j = 18; j < 23; j++) {
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
								g_current_game_phase = PHASE_Hall2;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (p_hint1_render == 1 && p_hint1_cnt == 1 && p_hint2_render == 0) {
					character_go_up_ = false;
				}
				if (p_hint2_render == 1 && p_hint1_cnt == 1 && p_hint1_render == 0) {
					character_go_up_ = false;
				}
				if (p_hint3_render == 1 && p_hint1_cnt == 1 && p_hint1_render == 0) {
					character_go_up_ = false;
				}
				{

					for (int i = 4; i < 14; i++) {
						for (int j = 9; j < 17; j++) {
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
								g_current_game_phase = PHASE_Movie2;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;
				if (p_hint1_render == 1 && p_hint1_cnt == 1 && p_hint2_render == 0) {
					character_go_down_ = false;
				}
				if (p_hint2_render == 1 && p_hint1_cnt == 1 && p_hint1_render == 0) {
					character_go_down_ = false;
				}
				if (p_hint3_render == 1 && p_hint1_cnt == 1 && p_hint1_render == 0) {
					character_go_down_ = false;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (character_x_ >= 230 && character_x_ <= 310 && character_y_ <= 110 && character_y_ >= 0) {
					p_hint1_cnt++;
					p_hint2_render = 0;
					p_hint3_render = 0;
				}
				if (character_x_ >= 400 && character_x_ <= 500 && character_y_ >= 0 && character_y_ <= 110) {
					p_hint1_cnt++;
					p_hint1_render = 0;
					p_hint3_render = 0;
				}
				if (character_x_ >= 420 && character_x_ <= 600 && character_y_ <= 370 && character_y_ >= 350) {
					p_hint1_cnt++;
					p_hint1_render = 0;
					p_hint2_render = 0;
				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 8;
				g_current_game_phase = PHASE_Inventory;

			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				character_go_left_ = false;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = false;
				{

					for (int i = 72; i < 80; i++) {
						for (int j = 18; j < 23; j++) {
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
								g_current_game_phase = PHASE_Hall2;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = false;
				{

					for (int i = 4; i < 14; i++) {
						for (int j = 9; j < 17; j++) {
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
								g_current_game_phase = PHASE_Movie2;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = false;
			}
			
			break;


		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				//   g_current_game_phase = PHASE_ENDING;
			}
			break;

		default:
			break;
		}
	}
}
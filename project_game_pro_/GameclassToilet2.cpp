#include "GameClassToilet2.h"
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
int t2_move_index;
extern int g_frame_time_ms;
extern int inventory_cnt;

TTF_Font *game_font_t2;
SDL_Texture *toilet2;
SDL_Rect toilet2_rect;
SDL_Rect t2;
int t2_hint1_cnt = 0;
int t2_hint1_render = 0;
SDL_Rect source_rectangle_t2[12];
int key_cnt = 0;

Toilet2::Toilet2()
{
	

	SDL_Surface* bg_surface = IMG_Load("../Resources/toilet_2.png");

	bg_destination_rectangle_.x = bg_source_rectangle_1.x = 0;
	bg_destination_rectangle_.y = bg_source_rectangle_1.y = 0;
	bg_destination_rectangle_.w = bg_source_rectangle_1.w = bg_surface->w;
	bg_destination_rectangle_.h = bg_source_rectangle_1.h = bg_surface->h;

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
Character7::Character7()
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
		character_x_ = 200;
		character_y_ = 340;
	}
	game_font_t2 = TTF_OpenFont("../Resources/PFStardust.ttf", 25);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font_t2, CW2A(L"열쇠를 획득했다", CP_UTF8), white);
	
	toilet2_rect.x = 0;
	toilet2_rect.y = 0;
	toilet2_rect.w = tmp_surface1->w;
	toilet2_rect.h = tmp_surface1->h;
	toilet2 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
	SDL_FreeSurface(tmp_surface1);

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

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_t2[0].w, &source_rectangle_t2[0].h); //png img 

																								//이딴 식으로 해야함
	source_rectangle_t2[0].x = 0;
	source_rectangle_t2[0].y = 200;
	source_rectangle_t2[0].w = 70;
	source_rectangle_t2[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_t2[i].x += source_rectangle_t2[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_t2[i].y = 200;
		source_rectangle_t2[i].w = 70;
		source_rectangle_t2[i].h = 100;


		

	}

	destination_rectangle_.x = (int)character_x_;
	destination_rectangle_.y = (int)character_y_;
	destination_rectangle_.w = 40;// source_rectangle_t2[0].w;// / 5;
	destination_rectangle_.h = 60;//source_rectangle_t2[0].h; // / 9;

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
	

																					  
	t2_move_index = 0;
}
Character7::~Character7()
{
	SDL_DestroyTexture(texture_);
}

Toilet2::~Toilet2()
{
	SDL_DestroyTexture(bg_texture_);
}

void Toilet2::Update()
{

}

void Character7::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character7::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}



void Character7::Update()
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
		if (t2_move_index < 2)
			t2_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();


	

		t2_move_index++;

		if (t2_move_index >3)
			t2_move_index = 2;
	

	}
	else if (character_go_right_)
	{
		if (t2_move_index < 6)
			t2_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();

		t2_move_index++;
		if (t2_move_index >7)
			t2_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (t2_move_index < 10)
			t2_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;

		Location_true();
		t2_move_index++;
		if (t2_move_index >11)
			t2_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		Location_true();

		t2_move_index++;
		if (t2_move_index >1)
			t2_move_index = 0;
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

		// 왼벽 피하기
		if (i > 22 && i < 31)
		{
			if (character[i][16] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}// 왼벽 피하기
		if (i >31 && i <41)
		{
			if (character[i][9] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		if (i > 41 && i < 56)
		{
			if (character[i][16] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		if (i > 46 && i < 56)
		{
			if (character[i][51] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		// 오른벽 피하기
		if (i > 22 && i < 56)
		{
			if (character[i][73] == true)
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
		if (i > 0 && i < 35)
		{
			if (character[8][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		//윗벽 피하기
		if (i > 17 && i < 73)
		{
			if (character[21][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		//아래벽 피하기
		if (i > 52 && i < 73)
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
		if (i > 16 && i < 52)
		{
			if (character[47][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		if (i > 10 && i < 16)
		{
			if (character[31][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		if (i > 10 && i < 16)
		{
			if (character[41][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
	}

	// 대화창
	if (character_x_ >= 440 && character_x_ <= 490 && character_y_ <= 250 && character_y_ >= 170) {
		t2_hint1_render = 1;
		if (t2_hint1_cnt > 1) {
			t2_hint1_cnt = 0;
			t2_hint1_render = 0;
		}
	}
	


}


void Toilet2::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_1, &bg_destination_rectangle_);


}

void Character7::Render()
{
	t2.x = 130;
	t2.y = 450;
	t2.w = toilet2_rect.w;
	t2.h = toilet2_rect.h;

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_t2[t2_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);

	if (t2_hint1_render == 1 && t2_hint1_cnt == 1&& key_cnt==1) {
		
			SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
			SDL_RenderPresent(g_renderer);
			SDL_RenderCopy(g_renderer, toilet2, 0, &t2);
			SDL_RenderPresent(g_renderer);
		
	}
}

void Toilet2::HandleEvents()
{
}

void Character7::HandleEvents()
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
				if (t2_hint1_render == 1 && t2_hint1_cnt == 1&& key_cnt==1) {
					character_go_left_ = false;
				}
				//for (int i = 50; i < 56; i++)
				{

					for (int j = 31; j < 36; j++) {
						for (int i = 8; i < 17; i++) {
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
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (t2_hint1_render == 1 && t2_hint1_cnt == 1 && key_cnt == 1) {
					character_go_right_ = false;
				}

			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (t2_hint1_render == 1 && t2_hint1_cnt == 1 && key_cnt == 1) {
					character_go_up_ = false;
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;
				if (t2_hint1_render == 1 && t2_hint1_cnt == 1 && key_cnt == 1) {
					character_go_down_ = false;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
		
				if (character_x_ >= 440 && character_x_ <= 490 && character_y_ <= 250 && character_y_ >= 170) {
					t2_hint1_cnt++;
					key_cnt++;
				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 7;
				g_current_game_phase = PHASE_Inventory;

			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				character_go_left_ = false;
				{

					for (int j = 31; j < 36; j++) {
						for (int i = 8; i < 17; i++) {
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
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = false;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = false;
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
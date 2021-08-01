#include "GameClassRoom2.h"
#include "GameClassPhase.h"
#include "GameClass_character.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_ttf.h"
#include <atlstr.h>
#include "SDL_mixer.h"


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
static bool arr[60][80];
int r2_move_index;
extern int g_frame_time_ms;
extern int water_cnt;
extern int inventory_cnt;
TTF_Font *game_font_r2;
SDL_Texture *buddha;
SDL_Rect buddha_rect;
SDL_Rect b;

SDL_Texture *buddha_s;
SDL_Rect buddha_s_rect;
int r2_hint1_cnt = 0;
int r2_hint1_render = 0;
int buddha_cnt = 0;


extern int sword1_cnt;
extern int sword2_cnt;
extern int sword3_cnt;
extern int sword4_cnt;
extern bool collect_sword;

SDL_Rect source_rectangle_6[12]; //오른쪽 반짝이 xx-> 이거를 class에서 꺼내면 됨



Room2::Room2()
{

	
	
	SDL_Surface* bg_surface = IMG_Load("../Resources/room_2.png");

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
Character6::Character6()
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
	
	
	character_x_ = 80;
	character_y_ = 150;


	// For Texture
	game_font_r2 = TTF_OpenFont("../Resources/PFStardust.ttf", 25);
	SDL_Color white = { 255, 255, 255, 0 };
	
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font_r2, CW2A(L"목이 마르도다.. ", CP_UTF8), white);
	SDL_Surface *tmp_surface2 = TTF_RenderUTF8_Blended(game_font_r2, CW2A(L"검 조각을 주겠다", CP_UTF8), white);
	buddha_rect.x = 0;
	buddha_rect.y = 0;
	buddha_rect.w = tmp_surface1->w;
	buddha_rect.h = tmp_surface1->h;
	buddha = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
	SDL_FreeSurface(tmp_surface1);

	buddha_s_rect.x = 0;
	buddha_s_rect.y = 0;
	buddha_s_rect.w = tmp_surface2->w;
	buddha_s_rect.h = tmp_surface2->h;
	buddha_s = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
	SDL_FreeSurface(tmp_surface2);

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


	SDL_Surface* temp_surface = IMG_Load("../Resources/mon.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface); //character's texture 
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_6[0].w, &source_rectangle_6[0].h); //png img 

																								//이딴 식으로 해야함
	source_rectangle_6[0].x = 0;
	source_rectangle_6[0].y = 200;
	source_rectangle_6[0].w = 70;
	source_rectangle_6[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_6[i].x += source_rectangle_6[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_6[i].y = 200;
		source_rectangle_6[i].w = 70;
		source_rectangle_6[i].h = 100;


	}

	destination_rectangle_.x = (int)character_x_;
	destination_rectangle_.y = (int)character_y_;
	destination_rectangle_.w = 50;// source_rectangle_[0].w;// / 5;
	destination_rectangle_.h = 80;//source_rectangle_[0].h; // / 9;

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


	r2_move_index = 0;
}
Character6::~Character6()
{
	SDL_DestroyTexture(texture_);
}

Room2::~Room2()
{
	SDL_DestroyTexture(bg_texture_);
}

void Room2::Update()
{
	if (sword1_cnt >= 1 && sword2_cnt >= 1 && sword3_cnt >= 1 && sword4_cnt >= 1)
		collect_sword = true;
	if (collect_sword == true) {
		g_current_game_phase = PHASE_Ending;
		
	}

}

void Character6::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character6::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}




void Character6::Update()
{
	

	if (character_go_left_)
	{
		if (r2_move_index < 2)
			r2_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();


		
		r2_move_index++;

		if (r2_move_index >3)
			r2_move_index = 2;
		

	}
	else if (character_go_right_)
	{
		if (r2_move_index < 6)
			r2_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();

		r2_move_index++;
		if (r2_move_index >7)
			r2_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (r2_move_index < 10)
			r2_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;

		Location_true();
		r2_move_index++;
		if (r2_move_index >11)
			r2_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		Location_true();

		r2_move_index++;
		if (r2_move_index >1)
			r2_move_index = 0;
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
			character_x_ -= 10;
			destination_rectangle_.x = (int)character_x_;
			c_rectangle_.x = destination_rectangle_.x / 10;
		}

		// 네모 피하기
		if (i > 0 && i < 14)
		{
			if (character[i][2] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		if (i >=22 && i <= 36)
		{
			if (character[i][68] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		if (i >= 22 && i <= 47)
		{
			if (character[i][4] == true)
			{
				Location_false();
				character_x_ += 10.;
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
		if (i > 0 && i < 79)
		{
			if (character[7][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		//아래벽 피하기
		if (i > 0 && i <= 68)
		{
			if (character[36][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		//아래벽 피하기
		if (i > 0 && i <= 68)
		{
			if (character[23][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
	}
	// 대화창
	if (character_x_ >= 460 && character_x_ <= 580 && character_y_ <= 510 && character_y_ >= 280) {
		r2_hint1_render = 1;

		if (r2_hint1_cnt > 1) {
			r2_hint1_cnt = 0;
			r2_hint1_render = 0;
		}
	}
	
}


void Room2::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);

}

void Character6::Render()
{
	b.x = 130;
	b.y = 450;
	b.w = buddha_rect.w;
	b.h = buddha_rect.h;

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_6[r2_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	if (r2_hint1_render == 1 && r2_hint1_cnt == 1&&water_cnt==0) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, buddha, 0, &b);
		SDL_RenderPresent(g_renderer);
	}
	if (r2_hint1_render == 1 && r2_hint1_cnt == 1&& water_cnt>=1) {

		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, buddha_s, 0, &b);
		SDL_RenderPresent(g_renderer);
	}
	
}

void Room2::HandleEvents()
{
}

void Character6::HandleEvents()
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
				if (r2_hint1_render == 1 && r2_hint1_cnt == 1) {
					character_go_left_ = false;
				}
				{

					for (int i = 2; i < 8; i++) {
						for (int j = 13; j < 18; j++) {
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
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (r2_hint1_render == 1 && r2_hint1_cnt == 1) {
					character_go_right_ = false;
				}
				
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (r2_hint1_render == 1 && r2_hint1_cnt == 1) {
					character_go_up_ = false;
				}
				
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;
				if (r2_hint1_render == 1 && r2_hint1_cnt == 1) {
					character_go_down_ = false;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (character_x_ >= 460 && character_x_ <= 580 && character_y_ <= 510 && character_y_ >= 280) {
					r2_hint1_cnt++;
					if (water_cnt >= 1) {
						sword3_cnt++;
					}
				
				}
				
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 6;
				g_current_game_phase = PHASE_Inventory;

			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				character_go_left_ = false;
				{

					for (int i = 2; i < 8; i++) {
						for (int j = 13; j < 18; j++) {
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
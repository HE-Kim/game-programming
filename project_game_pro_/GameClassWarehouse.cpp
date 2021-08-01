#include "GameClassWarehouse.h"
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
int w_move_index;
extern int g_frame_time_ms;
TTF_Font *game_font_w;
SDL_Texture *sword4;
SDL_Rect sword4_rect;
SDL_Rect s4;

int w_hint1_cnt = 0;
int w_hint1_render = 0;
extern int inventory_cnt;

SDL_Rect source_rectangle_w[12]; //오른쪽 반짝이 xx-> 이거를 class에서 꺼내면 됨

extern int sword1_cnt;
extern int sword2_cnt;
extern int sword3_cnt;
extern int sword4_cnt;
extern bool collect_sword;
Warehouse::Warehouse()
{


	SDL_Surface* bg_surface = IMG_Load("../Resources/warehouse.png");

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
Character13::Character13()
{
	//stage1_cnt++;

	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;

	character[60][80] = false;


	character_x_ = 380;
	character_y_ = 510;



	game_font_w = TTF_OpenFont("../Resources/PFStardust.ttf", 25);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font_w, CW2A(L"검 조각을 획득했다", CP_UTF8), white);
	
	sword4_rect.x = 0;
	sword4_rect.y = 0;
	sword4_rect.w = tmp_surface1->w;
	sword4_rect.h = tmp_surface1->h;
	sword4 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
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

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_w[0].w, &source_rectangle_w[0].h); //png img 

																								//이딴 식으로 해야함
	source_rectangle_w[0].x = 0;
	source_rectangle_w[0].y = 200;
	source_rectangle_w[0].w = 70;
	source_rectangle_w[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_w[i].x += source_rectangle_w[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_w[i].y = 200;
		source_rectangle_w[i].w = 70;
		source_rectangle_w[i].h = 100;

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


																					 
	w_move_index = 0;
}
Character13::~Character13()
{
	SDL_DestroyTexture(texture_);
}

Warehouse::~Warehouse()
{
	SDL_DestroyTexture(bg_texture_);
}

void Warehouse::Update()
{
	if (sword1_cnt >= 1 && sword2_cnt >= 1 && sword3_cnt >= 1 && sword4_cnt >= 1)
		collect_sword = true;
	if (collect_sword == true) {
		g_current_game_phase = PHASE_Ending;
		

	}
}

void Character13::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character13::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}




void Character13::Update()
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
		if (w_move_index < 2)
			w_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();



		w_move_index++;

		if (w_move_index >3)
			w_move_index = 2;
		

	}
	else if (character_go_right_)
	{
		if (w_move_index < 6)
			w_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();

		w_move_index++;
		if (w_move_index >7)
			w_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (w_move_index < 10)
			w_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;

		Location_true();
		w_move_index++;
		if (w_move_index >11)
			w_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		Location_true();

		w_move_index++;
		if (w_move_index >1)
			w_move_index = 0;
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

		// 네모1 피하기
		if (i >= 0 && i <= 40)
		{
			if (character[i][7] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][15] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][27] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][35] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][47] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][55] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][67] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		
		//오른벽
		if (i >= 0 && i <= 59)
		{
			if (character[i][77] == true)
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
		if (i >=7 && i <=12)
		{
			if (character[40][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		//아래벽 피하기
		if (i >=27 && i <= 32)
		{
			if (character[40][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		if (i >= 47 && i <= 52)
		{
			if (character[40][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
			
		}
		if (i >= 67 && i <= 72)
		{
			if (character[40][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}
		if (i >=0 && i <= 79)
		{
			if (character[4][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
			if (character[57][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}

		}

	}
	// 이동하기
	if (character_x_ >= 155 && character_x_ <= 180 && character_y_ <= 140 && character_y_ >= 120) {
		w_hint1_render = 1;
		
		if (w_hint1_cnt > 1) {
			w_hint1_cnt = 0;
			w_hint1_render = 0;
		}
	}

}


void Warehouse::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);


	
}

void Character13::Render()
{
	s4.x = 130;
	s4.y = 450;
	s4.w = sword4_rect.w;
	s4.h = sword4_rect.h;
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_w[w_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);

	if (w_hint1_render == 1 && w_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, sword4, 0, &s4);
		SDL_RenderPresent(g_renderer);
	}
}

void Warehouse::HandleEvents()
{
}

void Character13::HandleEvents()
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
				if (w_hint1_render == 1 && w_hint1_cnt == 1) {
					character_go_left_ = false;
				}
				
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (w_hint1_render == 1 && w_hint1_cnt == 1) {
					character_go_right_ = false;
				}
				
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (w_hint1_render == 1 && w_hint1_cnt == 1) {
					character_go_up_ = false;
				}

			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;
				if (w_hint1_render == 1 && w_hint1_cnt == 1) {
					character_go_down_ = false;
				}
				{

					for (int i = 36; i <44; i++) {
						for (int j = 53; j < 59; j++) {
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
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (character_x_ >= 155 && character_x_ <= 180 && character_y_ <= 140 && character_y_ >= 120) {
					w_hint1_cnt++;
					sword4_cnt++;
				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 12;
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
				
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = false;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = false;
				{

					for (int i = 36; i <44; i++) {
						for (int j = 53; j < 59; j++) {
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
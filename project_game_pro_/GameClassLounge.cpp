#include "GameClassLounge.h"
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
int L1_move_index;
extern int g_frame_time_ms;
TTF_Font *game_font_l;

int l_hint1_cnt=0;
int l_hint1_render=0;
int l_hint2_render=0;
int l_hint3_render = 0;
int water_cnt = 0;
extern int inventory_cnt;

SDL_Rect source_rectangle_L1[12]; //오른쪽 반짝이 xx-> 이거를 class에서 꺼내면 됨



Lounge::Lounge()
{


	SDL_Surface* bg_surface = IMG_Load("../Resources/Lounge.png");

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
Character12::Character12()
{
	//stage1_cnt++;

	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;

	character[60][80] = false;


	character_x_ = 690;
	character_y_ = 430;

	game_font_l = TTF_OpenFont("../Resources/PFStardust.ttf", 25);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font_l, CW2A(L"문이 잠겨있다", CP_UTF8), white);
	SDL_Surface *tmp_surface2 = TTF_RenderUTF8_Blended(game_font_l, CW2A(L"물 한잔 획득!", CP_UTF8), white);
	door_rect.x = 0;
	door_rect.y = 0;
	door_rect.w = tmp_surface1->w;
	door_rect.h = tmp_surface1->h;
	door = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
	SDL_FreeSurface(tmp_surface1);


	water_rect.x = 0;
	water_rect.y = 0;
	water_rect.w = tmp_surface2->w;
	water_rect.h = tmp_surface2->h;

	water = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
	SDL_FreeSurface(tmp_surface2);

	TTF_CloseFont(game_font_l);


	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/mon.png");
	texture_1 = SDL_CreateTextureFromSurface(g_renderer, temp_surface); //character's texture 
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_1, NULL, NULL, &source_rectangle_L1[0].w, &source_rectangle_L1[0].h); //png img 

																								//이딴 식으로 해야함
	source_rectangle_L1[0].x = 0;
	source_rectangle_L1[0].y = 200;
	source_rectangle_L1[0].w = 70;
	source_rectangle_L1[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_L1[i].x += source_rectangle_L1[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_L1[i].y = 200;
		source_rectangle_L1[i].w = 70;
		source_rectangle_L1[i].h = 100;

	}

	destination_rectangle_1.x = (int)character_x_;
	destination_rectangle_1.y = (int)character_y_;
	destination_rectangle_1.w = 50;// source_rectangle_[0].w;// / 5;
	destination_rectangle_1.h = 80;//source_rectangle_[0].h; // / 9;

								  //destination_rectangle_.x를 대체할 것이 무엇인가~~?

	c_rectangle_.x = destination_rectangle_1.x / 10;
	c_rectangle_.y = destination_rectangle_1.y / 10;
	c_rectangle_.w = destination_rectangle_1.w / 10;
	c_rectangle_.h = destination_rectangle_1.h / 10;

	// character의 좌표
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h


																					  
	L1_move_index = 0;
	
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

	SDL_Surface* hint2_surface = IMG_Load("../Resources/lounge_hint.png");
	
	hint2_texture_ = SDL_CreateTextureFromSurface(g_renderer, hint2_surface);

	SDL_FreeSurface(hint2_surface);

	hint2_source_rectangle_.x = 0;
	hint2_source_rectangle_.y = 0;
	hint2_source_rectangle_.w = 800;
	hint2_source_rectangle_.h = 600;

	hint2_destination_rectangle_.x = 0;
	hint2_destination_rectangle_.y = 0;
	hint2_destination_rectangle_.w = 800;
	hint2_destination_rectangle_.h = 600;

	SDL_QueryTexture(hint1_texture_, NULL, NULL, &hint2_source_rectangle_.w, &hint2_source_rectangle_.h);
}
Character12::~Character12()
{
	SDL_DestroyTexture(texture_1);
}

Lounge::~Lounge()
{
	SDL_DestroyTexture(bg_texture_);
}

void Lounge::Update()
{

}

void Character12::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character12::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}




void Character12::Update()
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
		if (L1_move_index < 2)
			L1_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_1.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_1.x / 10;
		Location_true();


	

		L1_move_index++;

		if (L1_move_index >3)
			L1_move_index = 2;
	

	}
	else if (character_go_right_)
	{
		if (L1_move_index < 6)
			L1_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_1.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_1.x / 10;
		Location_true();

		L1_move_index++;
		if (L1_move_index >7)
			L1_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (L1_move_index < 10)
			L1_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_1.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_1.y / 10;

		Location_true();
		L1_move_index++;
		if (L1_move_index >11)
			L1_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_1.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_1.y / 10;
		Location_true();

		L1_move_index++;
		if (L1_move_index >1)
			L1_move_index = 0;
	}

	//x
	for (int i = 0; i < 60; i++)
	{
		if (character[i][0] == true)
		{
			//x랑 y를 바꿔서 생각해야해

			Location_false();
			character_x_ += 10;
			destination_rectangle_1.x = (int)character_x_;
			c_rectangle_.x = destination_rectangle_1.x / 10;
		}
		if (character[i][79] == true)
		{

			Location_false();
			character_x_ -= 10;
			destination_rectangle_1.x = (int)character_x_;
			c_rectangle_.x = destination_rectangle_1.x / 10;
		}

		// 네모1 피하기
		if (i >= 0 && i <= 40)
		{
			if (character[i][33] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_1.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_1.x / 10;
			}	
		}
		if (i >= 55&& i <= 59)
		{
			if (character[i][24] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_1.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_1.x / 10;
			}
		}
		//오른벽
		if (i >= 0 && i <= 59)
		{
			if (character[i][77] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_rectangle_1.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_1.x / 10;
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
			destination_rectangle_1.y = (int)character_y_;
			c_rectangle_.y = destination_rectangle_1.y / 10;
		}
		else if (character[59][i] == true)
		{

			Location_false();
			character_y_ -= 10;
			destination_rectangle_1.y = (int)character_y_;
			c_rectangle_.y = destination_rectangle_1.y / 10;
		}

		//윗벽 피하기
		if (i >= 33 && i <= 77)
		{
			if (character[11][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_1.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_1.y / 10;
			}
		}
		//윗벽 피하기
		if (i >= 0 && i <= 31)
		{
			if (character[39][i] == true)
			{
				Location_false();
				character_y_ += 10.;
				destination_rectangle_1.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_1.y / 10;
			}
		}
		//아래벽 피하기
		if (i >= 0 && i <= 24)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_1.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_1.y / 10;
			}
		}

	}
	// 대화창
	if (character_x_ >= 90 && character_x_ <= 130 && character_y_ <= 440 && character_y_ >= 400) {
		l_hint1_render = 1;
		
		if (l_hint1_cnt > 1) {
			l_hint1_cnt = 0;
			l_hint1_render = 0;
		}
	}
	if (character_x_ >= 0 && character_x_ <= 70 && character_y_ <= 520 && character_y_ >= 460) {
		l_hint2_render = 1;
		
		if (l_hint1_cnt > 1) {
			l_hint1_cnt = 0;
			l_hint2_render = 0;
		}
	}
	if (character_x_ >= 480 && character_x_ <= 630 && character_y_ <= 140 && character_y_ >= 90) {
		l_hint3_render = 1;
	
		if (l_hint1_cnt > 1) {
			l_hint1_cnt = 0;
			l_hint3_render = 0;
		}
	}

}


void Lounge::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);


}

void Character12::Render()
{
	d.x = 130;
	d.y = 450;
	d.w = door_rect.w;
	d.h = door_rect.h;
	
	SDL_RenderCopy(g_renderer, texture_1, &source_rectangle_L1[L1_move_index], &destination_rectangle_1);
	SDL_RenderPresent(g_renderer);
	
	if (l_hint1_render == 1 && l_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, door, 0, &d);
		SDL_RenderPresent(g_renderer);
	}
	if (l_hint2_render == 1 && l_hint1_cnt == 1&& water_cnt==1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, water, 0, &d);
		SDL_RenderPresent(g_renderer);
	}
	if (l_hint3_render == 1 && l_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint2_texture_, &hint2_source_rectangle_, &hint2_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
}

void Lounge::HandleEvents()
{
}

void Character12::HandleEvents()
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
				if (l_hint1_render == 1 && l_hint1_cnt == 1 && l_hint2_render == 0) {
					character_go_left_ = false;
				}
				if (l_hint2_render == 1 && l_hint1_cnt == 1 && l_hint1_render == 0&&water_cnt==1) {
					character_go_left_ = false;
				}
				if (l_hint3_render == 1 && l_hint1_cnt == 1 && l_hint1_render == 0) {
					character_go_left_ = false;
				}

				
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (l_hint1_render == 1 && l_hint1_cnt == 1 && l_hint2_render == 0) {
					character_go_right_ = false;
				}
				if (l_hint2_render == 1 && l_hint1_cnt == 1 && l_hint1_render == 0 && water_cnt == 1) {
					character_go_right_ = false;
				}
				if (l_hint3_render == 1 && l_hint1_cnt == 1 && l_hint1_render == 0) {
					character_go_right_ = false;
				}
				{

					for (int i = 70; i <79; i++) {
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
								g_current_game_phase = PHASE_Hall2;
							}

						}
					}
				}


			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (l_hint1_render == 1 && l_hint1_cnt == 1 && l_hint2_render == 0) {
					character_go_up_ = false;
				}
				if (l_hint2_render == 1 && l_hint1_cnt == 1 && l_hint1_render == 0 && water_cnt == 1) {
					character_go_up_ = false;
				}
				if (l_hint3_render == 1 && l_hint1_cnt == 1 && l_hint1_render == 0) {
					character_go_up_ = false;
				}

			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;
				if (l_hint1_render == 1 && l_hint1_cnt == 1 && l_hint2_render == 0) {
					character_go_down_ = false;
				}
				if (l_hint2_render == 1 && l_hint1_cnt == 1 && l_hint1_render == 0 && water_cnt == 1) {
					character_go_down_ = false;
				}
				if (l_hint3_render == 1 && l_hint1_cnt == 1 && l_hint1_render == 0) {
					character_go_down_ = false;
				}
				
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (character_x_ >= 90 && character_x_ <= 130 && character_y_ <= 440 && character_y_ >= 400) {
					l_hint1_cnt++;
					l_hint2_render = 0;
					l_hint3_render = 0;
				}
				if (character_x_ >= 0 && character_x_ <= 70 && character_y_ <= 520 && character_y_ >= 460) {
					l_hint1_cnt++;
					l_hint1_render = 0;
					l_hint3_render = 0;
					water_cnt++;
				}
				if (character_x_ >= 480 && character_x_ <= 630 && character_y_ <= 140 && character_y_ >= 90) {
					l_hint1_cnt++;
					l_hint1_render = 0;
					l_hint2_render = 0;
					
				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 11;
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

					for (int i = 70; i <79; i++) {
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
								g_current_game_phase = PHASE_Hall2;
							}

						}
					}
				}


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

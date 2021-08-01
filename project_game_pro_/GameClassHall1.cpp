#include "GameClassHall1.h"
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
int h1_move_index;
extern int g_frame_time_ms;



SDL_Rect source_rectangle_h1[12]; //오른쪽 반짝이 xx-> 이거를 class에서 꺼내면 됨



SDL_Texture *info;
SDL_Rect info_rect;
int info_cnt = 0;
int h1_hint1_cnt = 0;
int h1_hint1_render = 0;

int inventory_cnt = 0;

TTF_Font *game_font_h1;


// soubd
Mix_Chunk *bg_sound_;
extern Mix_Chunk *i_sound_;
Hall1::Hall1()
{


	SDL_Surface* bg_surface = IMG_Load("../Resources/hall_1.png");

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
	
	Mix_VolumeMusic(128);

	bg_sound_ = Mix_LoadWAV("../Resources/game.mp3");
	if (bg_sound_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	Mix_PlayChannel(-1, bg_sound_, 0);

}

Character::Character()
{
	//if (i_sound_)		Mix_FreeChunk(i_sound_);
	//stage1_cnt++;

	character_go_left_ = false;
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
		character_x_ = 440;
		character_y_ = 440;
	}
	// For Texture
	game_font_h1 = TTF_OpenFont("../Resources/PFStardust.ttf", 25);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font_h1, CW2A(L"안내책차를 획득했다!", CP_UTF8), white);
	
	info_rect.x = 0;
	info_rect.y = 0;
	info_rect.w = tmp_surface1->w;
	info_rect.h = tmp_surface1->h;
	info = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
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




	SDL_Surface* temp_surface1 = IMG_Load("../Resources/mon.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface1); //character's texture 
	SDL_FreeSurface(temp_surface1);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_h1[0].w, &source_rectangle_h1[0].h); //png img 

																							   //이딴 식으로 해야함
	source_rectangle_h1[0].x = 0;
	source_rectangle_h1[0].y = 200;
	source_rectangle_h1[0].w = 70;
	source_rectangle_h1[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_h1[i].x += source_rectangle_h1[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_h1[i].y = 200;
		source_rectangle_h1[i].w = 70;
		source_rectangle_h1[i].h = 100;


		
	}

	destination_rectangle_.x = (int)character_x_;
	destination_rectangle_.y = (int)character_y_;
	destination_rectangle_.w = 40;// source_rectangle_[0].w;// / 5;
	destination_rectangle_.h = 60;//source_rectangle_[0].h; // / 9;

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


	h1_move_index = 0;

	SDL_Surface* f_surface = IMG_Load("../Resources/fountain.png");
	SDL_SetColorKey(f_surface, 1, SDL_MapRGB(f_surface->format, 255, 255, 255));
	f_texture_ = SDL_CreateTextureFromSurface(g_renderer, f_surface);

	SDL_FreeSurface(f_surface);

	f_source_rectangle_.x = 0;
	f_source_rectangle_.y = 0;
	f_source_rectangle_.w = 800;
	f_source_rectangle_.h = 600;

	f_destination_rectangle_.x = 0;
	f_destination_rectangle_.y = 0;
	f_destination_rectangle_.w = 800;
	f_destination_rectangle_.h = 600;

	SDL_QueryTexture(f_texture_, NULL, NULL, &f_source_rectangle_.w, &f_source_rectangle_.h);

}


Character::~Character()
{
	SDL_DestroyTexture(texture_);
}

Hall1::~Hall1()
{
	SDL_DestroyTexture(bg_texture_);
}

void Hall1::Update()
{

}

void Character::key_event_false()
{
	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;
}

void Character::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
	
	
}

void Character::destination_redef()
{
	destination_rectangle_.y = (int)character_y_;
	c_rectangle_.y = destination_rectangle_.y / 10;
	destination_rectangle_.x = (int)character_x_;
	c_rectangle_.x = destination_rectangle_.x / 10;
}




void Character::Update()
{

	if (i_sound_)
		Mix_FreeChunk(i_sound_);

	if (character_go_left_)
	{
		if (h1_move_index < 2)
			h1_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_redef();
		Location_true();


		

		h1_move_index++;

		if (h1_move_index >3)
			h1_move_index = 2;
	

	}
	else if (character_go_right_)
	{
		if (h1_move_index < 6)
			h1_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_redef();
		Location_true();

		h1_move_index++;
		if (h1_move_index >7)
			h1_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (h1_move_index < 10)
			h1_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_redef();

		Location_true();
		h1_move_index++;
		if (h1_move_index >11)
			h1_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_redef();
		Location_true();

		h1_move_index++;
		if (h1_move_index >1)
			h1_move_index = 0;
	}

	//x
	for (int i = 0; i < 60; i++)
	{
		if (character[i][0] == true)
		{
			//x랑 y를 바꿔서 생각해야해

			Location_false();
			character_x_ += 10;
			destination_redef();;
		}
		if (character[i][79] ==true)
		{

			Location_false();
			character_x_ -= 10.;
			destination_redef();
		}

		
		// 인포 피하기
		if (i > 8 && i < 14)
		{
			if (character[i][45] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_redef();
			}
			if (character[i][36] == true)
			{

				Location_false();
				character_x_ -= 10.;
				destination_redef();
			}
		}
		
		// 왼벽 피하기
		if (i > 8 && i < 13)
		{
			if (character[i][3] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_redef();
			}

		}
		// 왼벽 피하기
		if (i > 13 && i < 23)
		{
			if (character[i][0] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_redef();
			}

		}
		// 왼벽 피하기
		if (i > 23 && i < 25)
		{
			if (character[i][4] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_redef();
			}

		}
		// 왼벽 피하기
		if (i > 25 && i < 35)
		{
			if (character[i][0] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_redef();
			}

		}
		// 왼벽 피하기
		if (i > 35 && i < 41)
		{
			if (character[i][4] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_redef();
			}

		}
		// 왼벽 피하기
		if (i > 41 && i < 51)
		{
			if (character[i][0] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_redef();
			}

		}
		// 왼벽 피하기
		if (i > 51 && i < 55)
		{
			if (character[i][4] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_redef();
			}

		}

		// 오른벽 피하기
		if (i > 8 && i < 25)
		{
			if (character[i][77] == true)
			{
				Location_false();
				character_x_ -= 10.;
				destination_redef();
			}

		}
		//오른벽 피하기
			if (i > 25 && i < 37)
			{
				if (character[i][79] == true)
				{
					Location_false();
					character_x_ -= 10.;
					destination_redef();
				}

			}
			//오른벽 피하기
			if (i > 37 && i < 45)
			{
				if (character[i][77] == true)
				{
					Location_false();
					character_x_ -= 10.;
					destination_redef();
				}

			}
			//오른벽 피하기
			if (i > 45 && i < 59)
			{
				if (character[i][79] == true)
				{
					Location_false();
					character_x_ -= 10.;
					destination_redef();
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
			destination_redef();
		}
		else if (character[59][i] == true)
		{

			Location_false();
			character_y_ -= 10.;
			destination_redef();
		}

		
		//인포 피하기
		if (i > 36 && i < 45)
		{
			if (character[14][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_redef();
			}
			if (character[9][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}
		}
		//인포 옆 벽 피하기
		if (i > 48 && i < 55)
		{
			if (character[14][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_redef();
			}
			if (character[9][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}
		}
		//인포 옆 벽 피하기
		if (i > 66 && i < 75)
		{
			if (character[14][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_redef();
			}
			if (character[9][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}
		}
		//벽장 피하기
		if (i > 0 && i < 35)
		{
			if (character[8][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_redef();
			}

		}
		//벽 피하기
		if (i > 76 && i < 79)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}

		}
		//아래벽 피하기
		if (i > 76 && i < 79)
		{
			if (character[26][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_redef();
			}

		}
		//아래벽 피하기
		if (i > 76 && i < 79)
		{
			if (character[36][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}

		}
		//아래벽 피하기
		if (i > 4 && i < 75)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}
		}
		
		
	}
	
	//분수 지나가기
	if (character_x_ >= 290 && character_x_ <= 470 && character_y_<= 330 && character_y_ >= 329) {
		Location_false();
		character_y_ += 10.;
		destination_redef();
	}
	if (character_x_ >= 290 && character_x_ <= 470 && character_y_ <= 320 && character_y_ >= 319) {
		Location_false();
		character_y_ -= 10.;
		destination_redef();
	}
	if (character_x_ >= 360 && character_x_ <= 420 && character_y_ <= 180 && character_y_ >= 140) {
		h1_hint1_render = 1;

		if (h1_hint1_cnt > 1) {
			h1_hint1_cnt = 0;
			h1_hint1_render = 0;
		}
	}
}



void Hall1::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);

	
}

void Character::Render()
{
	i.x = 130;
	i.y = 450;
	i.w = info_rect.w;
	i.h = info_rect.h;

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_h1[h1_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	if (h1_hint1_render == 1 && h1_hint1_cnt == 1&&info_cnt==1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, info, 0, &i);
		SDL_RenderPresent(g_renderer);
	}
	
	if (character_x_ >= 320 && character_x_ <= 470 && character_y_ <= 330) {
		SDL_RenderCopy(g_renderer, f_texture_, &f_source_rectangle_, &f_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	
}

void Hall1::HandleEvents()
{
}


void Character::HandleEvents()
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
				if (h1_hint1_render == 1 && h1_hint1_cnt == 1&&info_cnt==1) {
					character_go_left_ = false;
				}
				
				//for (int i = 50; i < 56; i++)
				{

					for (int i = 0; i < 6; i++) {
						for (int j = 41; j < 47; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Room1;
							}

						}
					}
				}
				{

					for (int i = 0; i < 6; i++) {
						for (int j = 19; j < 22; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Store;
							}

						}
					}
				}

			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (h1_hint1_render == 1 && h1_hint1_cnt == 1 && info_cnt == 1) {
					character_go_right_ = false;
				}
				{

					for (int i = 72; i < 79; i++) {
						for (int j = 25; j < 32; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Toilet1;
							}

						}
					}
					for (int i = 73; i < 79; i++) {
						for (int j = 45; j < 55; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Room2;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (h1_hint1_render == 1 && h1_hint1_cnt == 1 && info_cnt == 1) {
					character_go_up_ = false;
				}
				{

					for (int i = 57; i < 66; i++) {
						for (int j = 5; j < 12; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Hall2;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;
				if (h1_hint1_render == 1 && h1_hint1_cnt == 1 && info_cnt == 1) {
					character_go_down_ = false;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (character_x_ >= 360 && character_x_ <= 420 && character_y_ <= 180 && character_y_ >= 140) {
					h1_hint1_cnt++;
					info_cnt++;
				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 1;
				g_current_game_phase = PHASE_Inventory;
				

			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				character_go_left_ = false;
				{

					for (int i = 0; i < 5; i++) {
						for (int j = 41; j < 47; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Room1;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = false;
				{

					for (int i = 72; i < 79; i++) {
						for (int j = 25; j < 32; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Toilet1;
							}

						}
					}
					for (int i = 73; i < 79; i++) {
						for (int j = 45; j < 55; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Room2;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = false;
				{

					for (int i = 57; i < 66; i++) {
						for (int j = 5; j < 12; j++) {
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
								key_event_false();
								g_current_game_phase = PHASE_Hall2;
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
				//  g_current_game_phase = PHASE_Movie1;ㅋㅋㅋㅋ
			}
			break;

		default:
			break;
		}
	}
	//if (hall_cnt != 0)
	//	cnt_check();

}


#include "GameClassInventory.h"
#include "GameClassPhase.h"
#include "GameClass_character.h"
#include "SDL_image.h"
#include <iostream>

bool collect_sword;
//검을 다 모았는지에 대한 여부
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
static bool arr[60][80];
int i_move_index;
extern int g_frame_time_ms;
extern int sword1_cnt = 0;
extern int sword2_cnt = 0;
extern int sword3_cnt = 0;
extern int sword4_cnt = 0;
extern int inventory_cnt;
extern int info_cnt;
extern int water_cnt;
extern int item_cnt;
extern int key_cnt;
int health_cnt = 3;
SDL_Rect source_rectangle_v[12];
SDL_Rect i_source_rectangle_[7];
SDL_Rect s1_source_rectangle_;
SDL_Rect s2_source_rectangle_;
SDL_Rect s3_source_rectangle_;
SDL_Rect s4_source_rectangle_;

Inventory::Inventory()
{
	SDL_Surface* bg_surface = IMG_Load("../Resources/Inventory.png");
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
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 80; j++)
			std::cout << arr[i][j] << "";
		std::cout << std::endl;
	}

}
Character15::Character15()
{
	//stage1_cnt++;
	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;

	character[60][80] = false;


	character_x_ = 380;
	character_y_ = 510;

	SDL_Surface* s1_surface = IMG_Load("../Resources/sword_1.png");
	SDL_SetColorKey(s1_surface, 1, SDL_MapRGB(s1_surface->format, 255, 255, 255));
	s1_texture_ = SDL_CreateTextureFromSurface(g_renderer, s1_surface);

	SDL_FreeSurface(s1_surface);

	s1_source_rectangle_.x = 0;
	s1_source_rectangle_.y = 0;
	s1_source_rectangle_.w = 800;
	s1_source_rectangle_.h = 600;
	s1_destination_rectangle_.x = 0;
	s1_destination_rectangle_.y = 0;
	s1_destination_rectangle_.w = 800;
	s1_destination_rectangle_.h = 600;
	SDL_QueryTexture(s1_texture_, NULL, NULL, &s1_source_rectangle_.w, &s1_source_rectangle_.h);

	SDL_Surface* s2_surface = IMG_Load("../Resources/sword_2.png");
	SDL_SetColorKey(s2_surface, 1, SDL_MapRGB(s2_surface->format, 255, 255, 255));
	s2_texture_ = SDL_CreateTextureFromSurface(g_renderer, s2_surface);

	SDL_FreeSurface(s2_surface);

	s2_source_rectangle_.x = 0;
	s2_source_rectangle_.y = 0;
	s2_source_rectangle_.w = 800;
	s2_source_rectangle_.h = 600;
	s2_destination_rectangle_.x = 0;
	s2_destination_rectangle_.y = 0;
	s2_destination_rectangle_.w = 800;
	s2_destination_rectangle_.h = 600;
	SDL_QueryTexture(s1_texture_, NULL, NULL, &s2_source_rectangle_.w, &s2_source_rectangle_.h);

	SDL_Surface* s3_surface = IMG_Load("../Resources/sword_3.png");
	SDL_SetColorKey(s3_surface, 1, SDL_MapRGB(s3_surface->format, 255, 255, 255));
	s3_texture_ = SDL_CreateTextureFromSurface(g_renderer, s3_surface);

	SDL_FreeSurface(s3_surface);

	s3_source_rectangle_.x = 0;
	s3_source_rectangle_.y = 0;
	s3_source_rectangle_.w = 800;
	s3_source_rectangle_.h = 600;
	s3_destination_rectangle_.x = 0;
	s3_destination_rectangle_.y = 0;
	s3_destination_rectangle_.w = 800;
	s3_destination_rectangle_.h = 600;
	SDL_QueryTexture(s3_texture_, NULL, NULL, &s3_source_rectangle_.w, &s3_source_rectangle_.h);

	SDL_Surface* s4_surface = IMG_Load("../Resources/sword_4.png");
	SDL_SetColorKey(s4_surface, 1, SDL_MapRGB(s4_surface->format, 255, 255, 255));
	s4_texture_ = SDL_CreateTextureFromSurface(g_renderer, s4_surface);
	SDL_FreeSurface(s4_surface);
	s4_source_rectangle_.x = 0;
	s4_source_rectangle_.y = 0;
	s4_source_rectangle_.w = 800;
	s4_source_rectangle_.h = 600;
	s4_destination_rectangle_.x = 0;
	s4_destination_rectangle_.y = 0;
	s4_destination_rectangle_.w = 800;
	s4_destination_rectangle_.h = 600;
	SDL_QueryTexture(s4_texture_, NULL, NULL, &s4_source_rectangle_.w, &s4_source_rectangle_.h);

	SDL_Surface* i_surface = IMG_Load("../Resources/item.png");
	SDL_SetColorKey(i_surface, 1, SDL_MapRGB(i_surface->format, 255, 255, 255));
	i_texture_ = SDL_CreateTextureFromSurface(g_renderer, i_surface);
	SDL_FreeSurface(i_surface);
	SDL_QueryTexture(i_texture_, NULL, NULL, &i_source_rectangle_[0].w, &i_source_rectangle_[0].h);
	//이딴 식으로 해야함
	i_source_rectangle_[0].x = 0;
	i_source_rectangle_[0].y = 0;
	i_source_rectangle_[0].w = 100;
	i_source_rectangle_[0].h = 100;
	for (int i = 1; i < 8; i++)
	{
		i_source_rectangle_[i].x += i_source_rectangle_[i - 1].x + 100;  //여기다 계속 더해야해!!!
		i_source_rectangle_[i].y = 0;
		i_source_rectangle_[i].w = 100;
		i_source_rectangle_[i].h = 100;
	}
	i_destination_rectangle_.x = 440;
	i_destination_rectangle_.y = 320;
	i_destination_rectangle_.w = 80;
	i_destination_rectangle_.h = 80;

	i2_destination_rectangle_.x = 540;
	i2_destination_rectangle_.y = 320;
	i2_destination_rectangle_.w = 80;
	i2_destination_rectangle_.h = 80;

	i3_destination_rectangle_.x = 640;
	i3_destination_rectangle_.y = 320;
	i3_destination_rectangle_.w = 80;
	i3_destination_rectangle_.h = 80;

	i4_destination_rectangle_.x = 440;
	i4_destination_rectangle_.y = 420;
	i4_destination_rectangle_.w = 80;
	i4_destination_rectangle_.h = 80;

	i5_destination_rectangle_.x = 540;
	i5_destination_rectangle_.y = 420;
	i5_destination_rectangle_.w = 80;
	i5_destination_rectangle_.h = 80;

	i6_destination_rectangle_.x = 640;
	i6_destination_rectangle_.y = 420;
	i6_destination_rectangle_.w = 80;
	i6_destination_rectangle_.h = 80;

	//체력
	h1_destination_rectangle_.x = 470;
	h1_destination_rectangle_.y = 120;
	h1_destination_rectangle_.w = 60;
	h1_destination_rectangle_.h = 60;

	h2_destination_rectangle_.x = 550;
	h2_destination_rectangle_.y = 120;
	h2_destination_rectangle_.w = 60;
	h2_destination_rectangle_.h = 60;

	h3_destination_rectangle_.x = 630;
	h3_destination_rectangle_.y = 120;
	h3_destination_rectangle_.w = 60;
	h3_destination_rectangle_.h = 60;


	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/mon.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface); //character's texture 
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_v[0].w, &source_rectangle_v[0].h); //png img 																		//이딴 식으로 해야함
	source_rectangle_v[0].x = 750;
	source_rectangle_v[0].y = 750;
	source_rectangle_v[0].w = 150;
	source_rectangle_v[0].h = 150;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_v[i].x += source_rectangle_v[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_v[i].y = 300;
		source_rectangle_v[i].w = 70;
		source_rectangle_v[i].h = 100;

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

	i_move_index = 0;
}
Character15::~Character15()
{
	SDL_DestroyTexture(texture_);
}

Inventory::~Inventory()
{
	SDL_DestroyTexture(bg_texture_);
}

void Inventory::Update()
{

}

void Character15::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character15::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}




void Character15::Update()
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
		if (i_move_index < 2)
			i_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();


		std::cout << destination_rectangle_.x << " ";
		std::cout << destination_rectangle_.y << " ";
		//std::cout << source_rectangle_[i].w << " ";
		//std::cout << source_rectangle_[i].h << " ";
		std::cout << std::endl;

		i_move_index++;

		if (i_move_index >3)
			i_move_index = 2;
		/*
		for (int i = 0; i < 60; i++)
		{
		for (int j = 0; j < 80; j++)
		std::cout << character[i][j] << "";
		std::cout << std::endl;
		}
		*/

	}
	else if (character_go_right_)
	{
		if (i_move_index < 6)
			i_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();

		i_move_index++;
		if (i_move_index >7)
			i_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (i_move_index < 10)
			i_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;

		Location_true();
		i_move_index++;
		if (i_move_index >11)
			i_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		Location_true();

		i_move_index++;
		if (i_move_index >1)
			i_move_index = 0;
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
		if (i >= 7 && i <= 12)
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
		if (i >= 27 && i <= 32)
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
		if (i >= 0 && i <= 79)
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


}


void Inventory::Render()
{
	//std::cout << "render_stage1";
	//   std::cout << std::endl;

	//SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, 0);
	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);


	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	//SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	//SDL_RenderPresent(g_renderer); // draw to the screen
}

void Character15::Render()
{
	SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[6], &i_destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[5], &i2_destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	if (info_cnt >= 1) {
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[4], &i3_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (water_cnt >= 1) {
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[3], &i4_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (item_cnt >= 1) {
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[2], &i5_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (key_cnt >= 1) {
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[1], &i6_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (health_cnt == 1) {
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[0], &h1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	else if (health_cnt == 2) {
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[0], &h1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[0], &h2_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (health_cnt == 3) {
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[0], &h1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[0], &h2_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, i_texture_, &i_source_rectangle_[0], &h3_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_v[i_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	if (sword1_cnt >= 1) {
		SDL_RenderCopy(g_renderer, s1_texture_, &s1_source_rectangle_, &s1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (sword2_cnt >= 1) {
		SDL_RenderCopy(g_renderer, s2_texture_, &s2_source_rectangle_, &s2_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (sword3_cnt >= 1) {
		SDL_RenderCopy(g_renderer, s3_texture_, &s3_source_rectangle_, &s3_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
	if (sword4_cnt >= 1) {
		SDL_RenderCopy(g_renderer, s4_texture_, &s4_source_rectangle_, &s4_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}

}

void Inventory::HandleEvents()
{
}

void Character15::HandleEvents()
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
				{
					character_go_left_ = true;

				}

			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;

			}


			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;

			}


			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;

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
								//g_current_game_phase = PHASE_Hall2;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (character_x_ >= 155 && character_x_ <= 180 && character_y_ <= 140 && character_y_ >= 120) {

				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				if (inventory_cnt == 1) {
					g_current_game_phase = PHASE_Hall1;
				}
				if (inventory_cnt == 2) {
					g_current_game_phase = PHASE_Room1;
				}
				if (inventory_cnt == 3) {
					g_current_game_phase = PHASE_Movie1;
				}
				if (inventory_cnt == 4) {
					g_current_game_phase = PHASE_Toilet1;
				}
				if (inventory_cnt == 5) {
					g_current_game_phase = PHASE_Hall2;
				}
				if (inventory_cnt == 6) {
					g_current_game_phase = PHASE_Room2;
				}
				if (inventory_cnt == 7) {
					g_current_game_phase = PHASE_Toilet2;
				}
				if (inventory_cnt == 8) {
					g_current_game_phase = PHASE_Room3;
				}
				if (inventory_cnt == 9) {
					g_current_game_phase = PHASE_Movie2;
				}
				if (inventory_cnt == 10) {
					g_current_game_phase = PHASE_Room4;
				}
				if (inventory_cnt == 11) {
					g_current_game_phase = PHASE_Lounge;
				}
				if (inventory_cnt == 12) {
					g_current_game_phase = PHASE_Warehouse;
				}
				if (inventory_cnt == 13) {
					g_current_game_phase = PHASE_Store;
				}
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
								//g_current_game_phase = PHASE_Hall2;
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
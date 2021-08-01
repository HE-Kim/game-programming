#include "GameClassMovie1.h"
#include "GameClassPhase.h"
#include "GameClass_character.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_mixer.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
static bool arr[60][80];
int m1_move_index;
extern int g_frame_time_ms;
int m_hint1_cnt = 0;
int m_hint1_render = 0;
extern int inventory_cnt;
int check_cnt_movie_1;
extern int check_room_1;

SDL_Rect source_rectangle_3[12]; //������ ��¦�� xx-> �̰Ÿ� class���� ������ ��

extern Mix_Chunk *i_sound_;

Movie1::Movie1()
{
	
	check_cnt_movie_1 = 0;
	SDL_Surface* bg_surface = IMG_Load("../Resources/movie_1.png");

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

			if (i > 9 && i <20 && j > 29 && j < 50) //i==y j==x��� �����ϸ� ����
				arr[i][j] = true;

		}
	}
	
}
Character3::Character3()
{
	//stage1_cnt++;

	if (i_sound_)
		Mix_FreeChunk(i_sound_);

	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;

	character[60][80] = false;


	//ó�� ������ �� �� !! 
	/*if (stage1_cnt > 1)
	{
	character_x_ = save_stage1_x;
	character_y_ = save_stage1_y;
	}
	else*/
	{
		character_x_ = 660;
		character_y_ = 440;
	}




	// For Texture

	SDL_Surface* hint1_surface = IMG_Load("../Resources/1592.png");
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

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_3[0].w, &source_rectangle_3[0].h); //png img 

																							  //�̵� ������ �ؾ���
	source_rectangle_3[0].x = 0;
	source_rectangle_3[0].y = 200;
	source_rectangle_3[0].w = 70;
	source_rectangle_3[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_3[i].x += source_rectangle_3[i - 1].x + 70;  //����� ��� ���ؾ���!!!
		source_rectangle_3[i].y = 200;
		source_rectangle_3[i].w = 70;
		source_rectangle_3[i].h = 100;


		

	}

	destination_rectangle_.x = (int)character_x_;
	destination_rectangle_.y = (int)character_y_;
	destination_rectangle_.w = 40;// source_rectangle_[0].w;// / 5;
	destination_rectangle_.h = 60;//source_rectangle_[0].h; // / 9;

								  //destination_rectangle_.x�� ��ü�� ���� �����ΰ�~~?

	c_rectangle_.x = destination_rectangle_.x / 10;
	c_rectangle_.y = destination_rectangle_.y / 10;
	c_rectangle_.w = destination_rectangle_.w / 10;
	c_rectangle_.h = destination_rectangle_.h / 10;

	// character�� ��ǥ
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h


																					   
	m1_move_index = 0;
}
Character3::~Character3()
{
	SDL_DestroyTexture(texture_);
}

Movie1::~Movie1()
{
	SDL_DestroyTexture(bg_texture_);
}

void Movie1::Update()
{

}

void Character3::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character3::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}



void Character3::Update()
{

	if (check_room_1 == 0)
		check_room_1 = 1;
	else if (check_cnt_movie_1 == 1)
		check_room_1 = 3;



	if (character_go_left_)
	{
		if (m1_move_index < 2)
			m1_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();


		

		m1_move_index++;

		if (m1_move_index >3)
			m1_move_index = 2;
	

	}
	else if (character_go_right_)
	{
		if (m1_move_index < 6)
			m1_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();

		m1_move_index++;
		if (m1_move_index >7)
			m1_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (m1_move_index < 10)
			m1_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;

		Location_true();
		m1_move_index++;
		if (m1_move_index >11)
			m1_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		Location_true();

		m1_move_index++;
		if (m1_move_index >1)
			m1_move_index = 0;
	}

	//x
	for (int i = 0; i < 60; i++)
	{
		if (character[i][0] == true)
		{
			//x�� y�� �ٲ㼭 �����ؾ���

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

		// �׸�1 ���ϱ�
		if (i > 34 && i < 43)
		{
			if (character[i][20] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][7] == true)
			{

				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		// �׸�2 ���ϱ�
		if (i > 34 && i < 43)
		{
			if (character[i][42] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][30] == true)
			{

				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		// �׸�3 ���ϱ�
		if (i > 34 && i < 43)
		{
			if (character[i][62] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][46] == true)
			{

				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		// ��ũ�����ϱ�
		if (i > 12 && i < 23)
		{
			if (character[i][55] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
			if (character[i][17] == true)
			{

				Location_false();
				character_x_ -= 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		if (i > 5 && i < 57)
		{
			if (character[i][73] == true)
			{

				Location_false();
				character_x_ -= 10;
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

		//�׸�1 ���ϱ�
		if (i > 7 && i < 20)
		{
			if (character[42][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
			if (character[35][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		//�׸�2 ���ϱ�
		if (i > 30 && i < 43)
		{
			if (character[42][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
			if (character[35][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		//�׸�3 ���ϱ�
		if (i > 46 && i < 63)
		{
			if (character[42][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
			if (character[35][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		if (i > 0 && i < 64)
		{
			if (character[53][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		// ��ũ�����ϱ�
		if (i > 17 && i < 55)
		{
			if (character[23][i] == true)
			{
				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
			if (character[12][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		if (i > 0 && i < 73)
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
	// ��Ʈ
	if (character_x_ >= 180 && character_x_ <= 490 && character_y_ <= 250 && character_y_ >= 120) {
		m_hint1_render = 1;
		if (m_hint1_cnt > 1) {
			m_hint1_cnt = 0;
			m_hint1_render = 0;
		}
	}


}


void Movie1::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);


	
}

void Character3::Render()
{
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_3[m1_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	if (m_hint1_render == 1 && m_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
	}
}

void Movie1::HandleEvents()
{
}

void Character3::HandleEvents()
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
				if (m_hint1_render == 1 && m_hint1_cnt == 1) {
					character_go_left_ = false;
				}
				//for (int i = 50; i < 56; i++)
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (m_hint1_render == 1 && m_hint1_cnt == 1) {
					character_go_right_ = false;
				}
				
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (m_hint1_render == 1 && m_hint1_cnt == 1) {
					character_go_up_ = false;
				}
				
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;
				if (m_hint1_render == 1 && m_hint1_cnt == 1) {
					character_go_down_ = false;
				}
				{

					for (int i = 64; i < 72; i++) {
						for (int j = 50; j < 55; j++) {
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
								g_current_game_phase = PHASE_Room1;
							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (character_x_ >= 180 && character_x_ <= 490 && character_y_ <= 250 && character_y_ >= 120) {
					m_hint1_cnt++;
				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 3;
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

					for (int i = 64; i < 72; i++) {
						for (int j = 50; j < 55; j++) {
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
								g_current_game_phase = PHASE_Room1;
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
				g_current_game_phase = PHASE_Movie1;
			}
			break;

		default:
			break;
		}
	}
}
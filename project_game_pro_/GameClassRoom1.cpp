#include "GameClassRoom1.h"
#include "GameClassPhase.h"
#include "GameClass_character.h"
#include "SDL_image.h"
#include "GameClassMonster.h"
#include <iostream>
#include "SDL_ttf.h"
#include <atlstr.h>
#include "SDL_mixer.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
static bool arr[60][80];
int r1_move_index;
extern int g_frame_time_ms;
extern int water_cnt;
extern int inventory_cnt;
extern bool collect_sword;
int r1_hint1_cnt = 0;
int r1_hint1_render = 0;
int r1_hint2_render = 0;
int r1_hint3_render = 0;

TTF_Font *game_font_r1;
SDL_Texture *r1_hint1;
SDL_Rect r1_hint1_rect;
SDL_Rect r1_hint;

SDL_Texture *r1_hint2;
SDL_Rect r1_hint2_rect;
SDL_Texture *r1_hint3;
SDL_Rect r1_hint3_rect;

SDL_Rect source_rectangle_2[12];
SDL_Rect source_rectangle_m1[8];//오른쪽 반짝이 xx-> 이거를 class에서 꺼내면 됨
SDL_Rect c_rectangle_; // 
SDL_Rect m_rectangle_; // 
SDL_Rect coor_;

SDL_Rect destination_rectangle_;

bool character[60][80];
static int mon_arr[60][80];
static int m_move_index;

static bool com_cnt;

int check_room_1;
extern int check_cnt_movie_1;

static double character_x_ ;
static double character_y_ ;

extern int health_cnt;

bool sound_test;

extern int sword1_cnt;
extern int sword2_cnt;
extern int sword3_cnt;
extern int sword4_cnt;

Mix_Chunk *m_sound_;
Room1::Room1()
{
	sound_test = false;
	com_cnt = false;
	SDL_Surface* bg_surface = IMG_Load("../Resources/room_1.png");

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
	check_room_1 = 0;


	m_sound_ = Mix_LoadWAV("../Resources/monster.mp3");
	if (m_sound_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}

}
Character2::Character2()
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
	character_x_ = 720;
	character_y_ = 120;



	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/mon.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface); //character's texture 
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_2[0].w, &source_rectangle_2[0].h); //png img 

																								//이딴 식으로 해야함
	source_rectangle_2[0].x = 0;
	source_rectangle_2[0].y = 200;
	source_rectangle_2[0].w = 70;
	source_rectangle_2[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_2[i].x += source_rectangle_2[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_2[i].y = 200;
		source_rectangle_2[i].w = 70;
		source_rectangle_2[i].h = 100;


	

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


	game_font_r1 = TTF_OpenFont("../Resources/arose.ttf", 25);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font_r1, CW2A(L"야옹!                            ", CP_UTF8), white);
	SDL_Surface *tmp_surface2 = TTF_RenderUTF8_Blended(game_font_r1, CW2A(L"야옹!                            ", CP_UTF8), white);
	SDL_Surface *tmp_surface3 = TTF_RenderUTF8_Blended(game_font_r1, CW2A(L"검 조각을 찾으러 왔군. 여기있다!", CP_UTF8), white);
	r1_hint1_rect.x = 0;
	r1_hint1_rect.y = 0;
	r1_hint1_rect.w = tmp_surface1->w;
	r1_hint1_rect.h = tmp_surface1->h;
	r1_hint1 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
	SDL_FreeSurface(tmp_surface1);


	r1_hint2_rect.x = 0;
	r1_hint2_rect.y = 0;
	r1_hint2_rect.w = tmp_surface2->w;
	r1_hint2_rect.h = tmp_surface2->h;

	r1_hint2 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
	SDL_FreeSurface(tmp_surface2);

	r1_hint3_rect.x = 0;
	r1_hint3_rect.y = 0;
	r1_hint3_rect.w = tmp_surface3->w;
	r1_hint3_rect.h = tmp_surface3->h;

	r1_hint3 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface3);
	SDL_FreeSurface(tmp_surface3);
	TTF_CloseFont(game_font_r1);
	r1_move_index = 0;
}

Monster1::Monster1()
{
	SDL_Surface* m_temp_surface1 = IMG_Load("../Resources/mon.png");
	m_texture_ = SDL_CreateTextureFromSurface(g_renderer, m_temp_surface1); //character's texture 
	SDL_FreeSurface(m_temp_surface1);

	SDL_QueryTexture(m_texture_, NULL, NULL, &source_rectangle_m1[0].w, &source_rectangle_m1[0].h); //png img 

	mon_x_ = 720;
	mon_y_ = 120;
	//이딴 식으로 해야함
	source_rectangle_m1[0].x = 0;
	source_rectangle_m1[0].y = 100;
	source_rectangle_m1[0].w = 65;
	source_rectangle_m1[0].h = 100;

	for (int i = 1; i < 8; i++)
	{
		source_rectangle_m1[i].x += source_rectangle_m1[i - 1].x + 65;  //여기다 계속 더해야해!!!
		source_rectangle_m1[i].y = 100;
		source_rectangle_m1[i].w = 65;
		source_rectangle_m1[i].h = 100;
	}

	m_destination_rectangle_.x = (int)mon_x_;
	m_destination_rectangle_.y = (int)mon_y_;
	m_destination_rectangle_.w = 50;
	m_destination_rectangle_.h = 80;

	mon_arr[60][80] = 0;

	m_rectangle_.x = m_destination_rectangle_.x / 10;
	m_rectangle_.y = m_destination_rectangle_.y / 10;
	m_rectangle_.w = m_destination_rectangle_.w / 10;
	m_rectangle_.h = m_destination_rectangle_.h / 10;

	// 1= down 2 =left 3= right 4= up
	mon_arr[m_rectangle_.y][m_rectangle_.x] = true; //x,y
	mon_arr[m_rectangle_.y][m_rectangle_.x + m_rectangle_.w] = true; //x+h,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x] = true;//x+w,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x + m_rectangle_.w] = true;//x+w, y+h

	key_false();
	m_move_index = 0;
}
Monster1::~Monster1()
{
	SDL_DestroyTexture(m_texture_);
}
Room1::~Room1()
{
	SDL_DestroyTexture(bg_texture_);
}
Character2::~Character2()
{
	SDL_DestroyTexture(texture_);
}

void Room1::Update()
{
	if (sword1_cnt >= 1 && sword2_cnt >= 1 && sword3_cnt >= 1 && sword4_cnt >= 1)
		collect_sword = true;

	if (collect_sword == true) {
		g_current_game_phase = PHASE_Ending;
		
	}

}
void Character2::key_event_false()
{
	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;
}
void Character2::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character2::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
	mon_arr[c_rectangle_.y][c_rectangle_.x] = true;
}

void Character2::destination_redef()
{
	destination_rectangle_.y = (int)character_y_;
	c_rectangle_.y = destination_rectangle_.y / 10;
	destination_rectangle_.x = (int)character_x_;
	c_rectangle_.x = destination_rectangle_.x / 10;
}

void Monster1::key_false()
{
	mon_go_left_ = false;
	mon_go_right_ = false;
	mon_go_up_ = false;
	mon_go_down_ = false;
}

void Monster1::m_destination_redef()
{
	m_destination_rectangle_.y = (int)mon_y_;
	m_rectangle_.y = m_destination_rectangle_.y / 10;
	m_destination_rectangle_.x = (int)mon_x_;
	m_rectangle_.x = m_destination_rectangle_.x / 10;
}

void Monster1::m_Location_false()
{
	mon_arr[m_rectangle_.y][m_rectangle_.x] = false; //x,y
	mon_arr[m_rectangle_.y][m_rectangle_.x + m_rectangle_.w] = false; //x+h,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x] = false;//x+w,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x + m_rectangle_.w] = false;//x+w, y+h
}
void Monster1::m_Location_true()
{
	mon_arr[m_rectangle_.y][m_rectangle_.x] = true; //x,y
	mon_arr[m_rectangle_.y][m_rectangle_.x + m_rectangle_.w] = true; //x+h,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x] = true;//x+w,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x + m_rectangle_.w] = true;//x+w, y+h

																					 //mon_arr[c_rectangle_.y][c_rectangle_.x] = true;

}


void Character2::Update()
{


	if (character_go_left_)
	{
		if (r1_move_index < 2)
			r1_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_redef();
		Location_true();




		r1_move_index++;

		if (r1_move_index >3)
			r1_move_index = 2;


	}
	else if (character_go_right_)
	{
		if (r1_move_index < 6)
			r1_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_redef();
		Location_true();

		r1_move_index++;
		if (r1_move_index >7)
			r1_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (r1_move_index < 10)
			r1_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_redef();

		Location_true();
		r1_move_index++;
		if (r1_move_index >11)
			r1_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_redef();
		Location_true();

		r1_move_index++;
		if (r1_move_index >1)
			r1_move_index = 0;
	}

	//x
	for (int i = 0; i < 60; i++)
	{
		if (character[i][0] == true)
		{
			//x랑 y를 바꿔서 생각해야해

			Location_false();
			character_x_ += 10;
			destination_redef();
		}
		if (character[i][79] == true)
		{

			Location_false();
			character_x_ -= 10;
			destination_redef();
		}

		// 네모 피하기
		if (i >= 24 && i <= 32)
		{

			if (character[i][14] == true)
			{

				Location_false();
				character_x_ -= 10;
				destination_redef();
			}
		}
		if (i >= 54 && i <= 59)
		{

			if (character[i][8] == true)
			{

				Location_false();
				character_x_ -= 10;
				destination_redef();
			}
			if (character[i][28] == true)
			{

				Location_false();
				character_x_ += 10;
				destination_redef();
			}
			if (character[i][36] == true)
			{

				Location_false();
				character_x_ -= 10;
				destination_redef();
			}
			if (character[i][56] == true)
			{

				Location_false();
				character_x_ += 10;
				destination_redef();
			}

		}
		if (i >= 49 && i <= 59) {
			if (character[i][64] == true)
			{

				Location_false();
				character_x_ -= 10;
				destination_redef();
			}

		}
		if (i >= 0 && i <= 10) {
			if (character[i][14] == true)
			{

				Location_false();
				character_x_ += 10;
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
			character_y_ += 10;
			destination_redef();
		}
		else if (character[59][i] == true)
		{

			Location_false();
			character_y_ -= 10;
			destination_redef();
		}

		//네모 피하기
		if (i >= 14 && i <= 76)
		{
			if (character[25][i] == true)
			{

				Location_false();
				character_y_ -= 10;
				destination_redef();
			}
			if (character[32][i] == true)
			{

				Location_false();
				character_y_ += 10;
				destination_redef();
			}
		}



		//윗벽 피하기
		if (i > 0 && i < 75)
		{
			if (character[5][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_redef();
			}
		}
		//아랫벽 피하기
		if (i >= 8 && i <= 28)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}
		}
		//아랫벽 피하기
		if (i >= 36 && i <= 56)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}
		}
		if (i >= 64 && i <= 74)
		{
			if (character[50][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_redef();
			}
		}


	}
	// 대화창
	if (character_x_ >= 170 && character_x_ <= 220 && character_y_ <= 70 && character_y_ >= 50) {
		r1_hint1_render = 1;
		r1_hint2_render = 0;
		r1_hint3_render = 0;
		if (r1_hint1_cnt > 1) {
			r1_hint1_cnt = 0;
			r1_hint1_render = 0;
		}
	}
	if (character_x_ >= 510 && character_x_ <= 560 && character_y_ >= 50 && character_y_ <= 70) {
		r1_hint1_render = 0;
		r1_hint2_render = 1;
		r1_hint3_render = 0;
		if (r1_hint1_cnt > 1) {
			r1_hint1_cnt = 0;
			r1_hint2_render = 0;
		}
	}
	if (character_x_ >= 590 && character_x_ <= 680 && character_y_ >= 325 && character_y_ <= 340) {
		r1_hint1_render = 0;
		r1_hint2_render = 0;
		r1_hint3_render = 1;
		if (r1_hint1_cnt > 1) {
			r1_hint1_cnt = 0;
			r1_hint3_render = 0;
		}
	}
}
void Monster1::Update()
{
	if (check_room_1 != 1)
	{
		if (sound_test == true)
		{
			
			sound_test = false;
		}
		return;
	}
	check_cnt_movie_1 = 1;

	
	Mix_PlayChannel(-1, m_sound_, 0);
	sound_test = true;

	for (int i = -5; i <= 5; i++)
	{
		if (m_rectangle_.x + i == c_rectangle_.x && m_rectangle_.y + i == c_rectangle_.y)
		{
			character_x_ = 720;
			character_y_ = 120;
			destination_rectangle_.y = (int)character_y_;
			destination_rectangle_.x = (int)character_x_;
			//Location_true();

			check_room_1 = 5;
			Mix_FreeChunk(m_sound_);
			//디짐
			//여기서 하트 -1
			health_cnt -= 1;
			g_current_game_phase = PHASE_Hall1;
		}
	}

	pre_update();


	{
		if (mon_go_right_)
		{
			if (m_move_index < 4)
				m_move_index = 4;
			m_Location_false();

			mon_x_ += 6.;
			m_destination_redef();
			m_Location_true();

			m_move_index++;

			if (m_move_index >5)
				m_move_index = 4;
		}
		else if (mon_go_left_)
		{
			if (m_move_index < 2)
				m_move_index = 2;
			m_Location_false();
			mon_x_ -= 6.;
			m_destination_redef();
			m_Location_true();

			m_move_index++;

			if (m_move_index >3)
				m_move_index = 2;
		}
		if (mon_go_up_)
		{
			if (m_move_index < 6)
				m_move_index = 6;
			m_Location_false();
			mon_y_ -= 6.;
			m_destination_redef();
			m_Location_true();

			m_move_index++;

			if (m_move_index >7)
				m_move_index = 6;


		}
		else if (mon_go_down_)
		{
			m_Location_false();

			mon_y_ += 6.;
			m_destination_redef();
			m_Location_true();

			m_move_index++;

			if (m_move_index >1)
				m_move_index = 0;

		}
	}
}

void Room1::Render()
{
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);

}

void Character2::Render()
{
	r1_hint.x = 130;
	r1_hint.y = 450;
	r1_hint.w = r1_hint1_rect.w;
	r1_hint.h = r1_hint1_rect.h;
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_2[r1_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	if (r1_hint1_render == 1 && r1_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, r1_hint1, 0, &r1_hint);
		SDL_RenderPresent(g_renderer);
	}
	if (r1_hint2_render == 1 && r1_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, r1_hint2, 0, &r1_hint);
		SDL_RenderPresent(g_renderer);
	}
	if (r1_hint3_render == 1 && r1_hint1_cnt == 1 && sword2_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, r1_hint3, 0, &r1_hint);
		SDL_RenderPresent(g_renderer);
	}
}
void Monster1::Render()
{
	if (check_room_1 != 1)
	{
		return;
	}
	//어떻게 그려질지
	SDL_RenderCopy(g_renderer, m_texture_, &source_rectangle_m1[m_move_index], &m_destination_rectangle_);
	SDL_RenderPresent(g_renderer);
}
void Room1::HandleEvents()
{
}
void Monster1::pre_update()
{

	if (com_cnt == true)
	{
		if (coor_.x == m_rectangle_.x &&coor_.y == m_rectangle_.y)
		{
			com_cnt = false;
		}
	}
	if (m_rectangle_.x < 10 && m_rectangle_.y > 20 && m_rectangle_.y < 34)//&& m_rectangle_.x > c_rectangle_.x )//&& com_cnt == true)
	{

		if (m_rectangle_.y <= c_rectangle_.y)
		{
			key_false();
			mon_go_down_ = true;
			return;
		}
		else if (m_rectangle_.y > c_rectangle_.y)
		{
			key_false();
			mon_go_up_ = true;
			return;
		}

	}
	if (m_rectangle_.y == 17 && m_rectangle_.x > 10)//&& m_rectangle_.x < 80) //윗벽 
	{
		//key_false();
		coor_.x = 10;
		coor_.y = 17;
		//com_cnt = true;
		//mon_go_left_ = true;

	
	}
	else if (m_rectangle_.y == 32 && m_rectangle_.x > 10)//&& m_rectangle_.x < 80) //아랫벽
	{

		coor_.x = 8;
		coor_.y = 32;

	}


	if (m_rectangle_.y >= c_rectangle_.y && m_rectangle_.x <= c_rectangle_.x && com_cnt == true)
	{
		
		coor_.x = c_rectangle_.x;
		coor_.y = c_rectangle_.y;
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////
	if (abs(coor_.x - m_rectangle_.x) < abs(coor_.y - m_rectangle_.y))
	{
		if (coor_.x < m_rectangle_.x)
		{
			key_false();
			mon_go_left_ = true;
		}
		else if (coor_.x > m_rectangle_.x)
		{
			key_false();
			mon_go_right_ = true;
		}
		else if (coor_.y > m_rectangle_.y)
		{
			key_false();
			mon_go_down_ = true;

		}
		else if (coor_.y < m_rectangle_.y)
		{
			key_false();
			mon_go_up_ = true;
		}
	}
	else
	{
		if (coor_.y < m_rectangle_.y)
		{
			key_false();
			mon_go_up_ = true;
		}
		else if (coor_.y > m_rectangle_.y)
		{
			key_false();
			mon_go_down_ = true;

		}
		else if (coor_.x > m_rectangle_.x)
		{
			key_false();
			mon_go_right_ = true;
		}
		else if (coor_.x < m_rectangle_.x)
		{
			key_false();
			mon_go_left_ = true;
		}
	}
	if (com_cnt == false)
	{
		coor_.x = c_rectangle_.x;
		coor_.y = c_rectangle_.y;
	}


}

void Character2::HandleEvents()
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
				if (r1_hint1_render == 1 && r1_hint1_cnt == 1) {
					character_go_left_ = false;
				}
				if (r1_hint2_render == 1 && r1_hint1_cnt == 1) {
					character_go_left_ = false;
				}
				if (r1_hint3_render == 1 && r1_hint1_cnt == 1 && sword2_cnt == 1) {
					character_go_left_ = false;
				}
				//for (int i = 50; i < 56; i++)
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;

				if (r1_hint1_render == 1 && r1_hint1_cnt == 1) {
					character_go_right_ = false;
				}
				if (r1_hint2_render == 1 && r1_hint1_cnt == 1) {
					character_go_right_ = false;
				}
				if (r1_hint3_render == 1 && r1_hint1_cnt == 1 && sword2_cnt == 1) {
					character_go_right_ = false;
				}
				{
					if (character[10][74] == true || character[11][74] == true || character[10][73] == true || character[11][73] == true || character[10][75] == true || character[11][75] == true || character[9][73] == true || character[9][74] == true)
					{

						character_go_left_ = false;
						character_go_right_ = false;
						character_go_up_ = false;
						character_go_down_ = false;
						g_current_game_phase = PHASE_Hall1;
					}
				}

			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (r1_hint1_render == 1 && r1_hint1_cnt == 1) {
					character_go_up_ = false;
				}
				if (r1_hint2_render == 1 && r1_hint1_cnt == 1) {
					character_go_up_ = false;
				}
				if (r1_hint3_render == 1 && r1_hint1_cnt == 1 && sword2_cnt == 1) {
					character_go_up_ = false;
				}
				{

					for (int i = 4; i < 12; i++) {
						for (int j = 9; j < 17; j++) {
							if (character[j][i] == true)
							{
								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Movie1;
							}

						}
					}
				}

			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;

				if (r1_hint1_render == 1 && r1_hint1_cnt == 1) {
					character_go_down_ = false;
				}
				if (r1_hint2_render == 1 && r1_hint1_cnt == 1) {
					character_go_down_ = false;
				}
				if (r1_hint3_render == 1 && r1_hint1_cnt == 1 && sword2_cnt == 1) {
					character_go_down_ = false;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (character_x_ >= 170 && character_x_ <= 220 && character_y_ <= 70 && character_y_ >= 50) {
					r1_hint1_cnt++;
					r1_hint2_render = 0;
					r1_hint3_render = 0;
				}
				if (character_x_ >= 510 && character_x_ <= 560 && character_y_ >= 50 && character_y_ <= 70) {
					r1_hint1_cnt++;
					r1_hint1_render = 0;
					r1_hint3_render = 0;
				}
				if (character_x_ >= 590 && character_x_ <= 680 && character_y_ >= 325 && character_y_ <= 340) {
					r1_hint1_cnt++;
					r1_hint1_render = 0;
					r1_hint2_render = 0;
					sword2_cnt++;
				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 2;
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
					if (character[10][74] == true || character[11][74] == true || character[10][73] == true || character[11][73] == true || character[10][75] == true || character[11][75] == true || character[9][73] == true || character[9][74] == true)
					{

						character_go_left_ = false;
						character_go_right_ = false;
						character_go_up_ = false;
						character_go_down_ = false;
						g_current_game_phase = PHASE_Hall1;
					}
				}

			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = false;
				{

					for (int i = 4; i < 12; i++) {
						for (int j = 9; j < 17; j++) {
							if (character[j][i] == true)
							{

								character_go_left_ = false;
								character_go_right_ = false;
								character_go_up_ = false;
								character_go_down_ = false;
								g_current_game_phase = PHASE_Movie1;
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
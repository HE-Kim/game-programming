#include "GameClassRoom4.h"
#include "GameClassPhase.h"
#include "GameClass_character.h"
#include "GameClassMonster.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_ttf.h"
#include <atlstr.h>
#include "SDL_mixer.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
static bool arr[60][80];
int r4_move_index;
extern int g_frame_time_ms;
int r4_hint1_cnt = 0;
int r4_hint1_render = 0;
int r4_hint2_render = 0;
int r4_hint3_render = 0;
int r4_hint4_render = 0;
int r4_hint5_render = 0;
extern int inventory_cnt;
TTF_Font *game_font_r4;
SDL_Texture *r4_hint1;
SDL_Rect r4_hint1_rect;
SDL_Rect r4_hint;

SDL_Texture *r4_hint2;
SDL_Rect r4_hint2_rect;
SDL_Texture *r4_hint3;
SDL_Rect r4_hint3_rect;
SDL_Texture *r4_hint4;
SDL_Rect r4_hint4_rect;
SDL_Texture *r4_hint5;
SDL_Rect r4_hint5_rect;

int item_cnt = 0;
SDL_Rect source_rectangle_r4[12];

static SDL_Rect source_rectangle_m1[4];

static SDL_Rect c_rectangle_; // 
static SDL_Rect coor_;
static SDL_Rect destination_rectangle_;
static int mon_arr[60][80];
static int m_move_index;

static bool com_cnt;
extern int health_cnt;
extern int sword1_cnt;
extern int sword2_cnt;
extern int sword3_cnt;
extern int sword4_cnt;
extern bool collect_sword;
bool red_dis;
bool red_mon;
bool check_red;//오른쪽 반짝이 xx-> 이거를 class에서 꺼내면 됨

static double character_x_;
static double character_y_;

Mix_Chunk *m_sound_1;
Room4::Room4()
{

	check_red = true;
	com_cnt = false;
	SDL_Surface* bg_surface = IMG_Load("../Resources/room_4.png");

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
	red_dis = false;
	red_mon = false;

	
}
Character11::Character11()
{
	//stage1_cnt++;

	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;

	character[60][80] = false;


	character_x_ = 100;
	character_y_ = 140;





	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/mon.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface); //character's texture 
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_r4[0].w, &source_rectangle_r4[0].h); //png img 

																								//이딴 식으로 해야함
	source_rectangle_r4[0].x = 0;
	source_rectangle_r4[0].y = 200;
	source_rectangle_r4[0].w = 70;
	source_rectangle_r4[0].h = 100;

	for (int i = 1; i < 12; i++)
	{
		source_rectangle_r4[i].x += source_rectangle_r4[i - 1].x + 70;  //여기다 계속 더해야해!!!
		source_rectangle_r4[i].y = 200;
		source_rectangle_r4[i].w = 70;
		source_rectangle_r4[i].h = 100;

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

	r4_move_index = 0;

	game_font_r4 = TTF_OpenFont("../Resources/PFStardust.ttf", 25);
	
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface *tmp_surface1 = TTF_RenderUTF8_Blended(game_font_r4, CW2A(L"화장실 세번째 칸이야....          ", CP_UTF8), white);
	SDL_Surface *tmp_surface2 = TTF_RenderUTF8_Blended(game_font_r4, CW2A(L"검 조각을 물어가는 걸 봤어 낄낄낄 ", CP_UTF8), white);
	SDL_Surface *tmp_surface3 = TTF_RenderUTF8_Blended(game_font_r4, CW2A(L"아무것도 없다                     ", CP_UTF8), white);
	SDL_Surface *tmp_surface4 = TTF_RenderUTF8_Blended(game_font_r4, CW2A(L"비녀를 획득했다                   ", CP_UTF8), white);
	SDL_Surface *tmp_surface5 = TTF_RenderUTF8_Blended(game_font_r4, CW2A(L"검 조각을 획득했다                ", CP_UTF8), white);
	r4_hint1_rect.x = 0;
	r4_hint1_rect.y = 0;
	r4_hint1_rect.w = tmp_surface1->w;
	r4_hint1_rect.h = tmp_surface1->h;
	r4_hint1 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
	SDL_FreeSurface(tmp_surface1);


	r4_hint2_rect.x = 0;
	r4_hint2_rect.y = 0;
	r4_hint2_rect.w = tmp_surface2->w;
	r4_hint2_rect.h = tmp_surface2->h;
	r4_hint2 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
	SDL_FreeSurface(tmp_surface2);

	r4_hint3_rect.x = 0;
	r4_hint3_rect.y = 0;
	r4_hint3_rect.w = tmp_surface3->w;
	r4_hint3_rect.h = tmp_surface3->h;
	r4_hint3 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface3);
	SDL_FreeSurface(tmp_surface3);
	
	r4_hint4_rect.x = 0;
	r4_hint4_rect.y = 0;
	r4_hint4_rect.w = tmp_surface4->w;
	r4_hint4_rect.h = tmp_surface4->h;
	r4_hint4 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface4);
	SDL_FreeSurface(tmp_surface4);
	
	r4_hint5_rect.x = 0;
	r4_hint5_rect.y = 0;
	r4_hint5_rect.w = tmp_surface5->w;
	r4_hint5_rect.h = tmp_surface5->h;
	r4_hint5 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface5);
	SDL_FreeSurface(tmp_surface5);
	
	TTF_CloseFont(game_font_r4);

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
Character11::~Character11()
{
	SDL_DestroyTexture(texture_);
}
Monster2::Monster2()
{
	SDL_Surface* m_temp_surface1 = IMG_Load("../Resources/mon.png");
	m_texture_ = SDL_CreateTextureFromSurface(g_renderer, m_temp_surface1); //character's texture 
	SDL_FreeSurface(m_temp_surface1);

	SDL_QueryTexture(m_texture_, NULL, NULL, &source_rectangle_m1[0].w, &source_rectangle_m1[0].h); //png img 

	mon_x_ = 680;
	mon_y_ = 460;
	//이딴 식으로 해야함
	source_rectangle_m1[0].x = 0;
	source_rectangle_m1[0].y = 0;
	source_rectangle_m1[0].w = 60;
	source_rectangle_m1[0].h = 100;

	for (int i = 1; i < 4; i++)
	{
		source_rectangle_m1[i].x += source_rectangle_m1[i - 1].x + 60;  //여기다 계속 더해야해!!!
		source_rectangle_m1[i].y = 0;
		source_rectangle_m1[i].w = 60;
		source_rectangle_m1[i].h = 100;
	}

	m_destination_rectangle_.x = (int)mon_x_;
	m_destination_rectangle_.y = (int)mon_y_;
	m_destination_rectangle_.w = 65;
	m_destination_rectangle_.h = 90;

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
Monster2::~Monster2()
{
	SDL_DestroyTexture(m_texture_);
}
Room4::~Room4()
{
	SDL_DestroyTexture(bg_texture_);
}

void Room4::Update()
{
	if (sword1_cnt >= 1 && sword2_cnt >= 1 && sword3_cnt >= 1 && sword4_cnt >= 1)
		collect_sword = true;
	if (collect_sword == true) {
		g_current_game_phase = PHASE_Ending;
	

	}
}
void Character11::key_event_false()
{
	character_go_left_ = false;
	character_go_right_ = false;
	character_go_up_ = false;
	character_go_down_ = false;
}

void Character11::Location_false()
{
	character[c_rectangle_.y][c_rectangle_.x] = false; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = false; //x,y+h
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = false;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = false;//x+w, y+h
}
void Character11::Location_true()
{
	character[c_rectangle_.y][c_rectangle_.x] = true; //x,y
	character[c_rectangle_.y][c_rectangle_.x + c_rectangle_.w] = true; //x+h,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x] = true;//x+w,y
	character[c_rectangle_.y + c_rectangle_.h][c_rectangle_.x + c_rectangle_.w] = true;//x+w, y+h
}
void Character11::destination_redef()
{
	destination_rectangle_.y = (int)character_y_;
	c_rectangle_.y = destination_rectangle_.y / 10;
	destination_rectangle_.x = (int)character_x_;
	c_rectangle_.x = destination_rectangle_.x / 10;
}
void Monster2::key_false()
{
	mon_go_left_ = false;
	mon_go_right_ = false;
	mon_go_up_ = false;
	mon_go_down_ = false;
}
void Monster2::m_destination_redef()
{
	m_destination_rectangle_.y = (int)mon_y_;
	m_rectangle_.y = m_destination_rectangle_.y / 10;
	m_destination_rectangle_.x = (int)mon_x_;
	m_rectangle_.x = m_destination_rectangle_.x / 10;
}
void Monster2::m_Location_false()
{
	mon_arr[m_rectangle_.y][m_rectangle_.x] = false; //x,y
	mon_arr[m_rectangle_.y][m_rectangle_.x + m_rectangle_.w] = false; //x+h,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x] = false;//x+w,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x + m_rectangle_.w] = false;//x+w, y+h
}
void Monster2::m_Location_true()
{
	mon_arr[m_rectangle_.y][m_rectangle_.x] = true; //x,y
	mon_arr[m_rectangle_.y][m_rectangle_.x + m_rectangle_.w] = true; //x+h,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x] = true;//x+w,y
	mon_arr[m_rectangle_.y + m_rectangle_.h][m_rectangle_.x + m_rectangle_.w] = true;//x+w, y+h

																					 //mon_arr[c_rectangle_.y][c_rectangle_.x] = true;

}

void Character11::Update()
{
	

	if (character_go_left_)
	{
		if (r4_move_index < 2)
			r4_move_index = 2;


		Location_false();
		character_x_ -= 10;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();



		r4_move_index++;

		if (r4_move_index >3)
			r4_move_index = 2;
	
	}
	else if (character_go_right_)
	{
		if (r4_move_index < 6)
			r4_move_index = 6;

		Location_false();
		character_x_ += 10.;
		destination_rectangle_.x = (int)character_x_;
		c_rectangle_.x = destination_rectangle_.x / 10;
		Location_true();

		r4_move_index++;
		if (r4_move_index >7)
			r4_move_index = 6;
	}
	else if (character_go_up_)
	{
		if (r4_move_index < 10)
			r4_move_index = 10;


		Location_false();
		character_y_ -= 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;

		Location_true();
		r4_move_index++;
		if (r4_move_index >11)
			r4_move_index = 10;
	}
	else if (character_go_down_)
	{
		Location_false();
		character_y_ += 10.;
		destination_rectangle_.y = (int)character_y_;
		c_rectangle_.y = destination_rectangle_.y / 10;
		Location_true();

		r4_move_index++;
		if (r4_move_index >1)
			r4_move_index = 0;
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
		if (i >= 21 && i <= 33)
		{
			if (character[i][58] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}
		}
		//왼벽
		if (i >= 0 && i <= 59)
		{
			if (character[i][3] == true)
			{
				Location_false();
				character_x_ += 10.;
				destination_rectangle_.x = (int)character_x_;
				c_rectangle_.x = destination_rectangle_.x / 10;
			}

		}
		//오른벽
		if (i >= 0 && i <= 59)
		{
			if (character[i][75] == true)
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
		if (i > 0 && i < 79)
		{
			if (character[6][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		//아래벽 피하기
		if (i > 3 && i <= 75)
		{
			if (character[55][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		if (i >= 3 && i <= 59)
		{
			if (character[22][i] == true)
			{

				Location_false();
				character_y_ -= 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
			if (character[33][i] == true)
			{

				Location_false();
				character_y_ += 10.;
				destination_rectangle_.y = (int)character_y_;
				c_rectangle_.y = destination_rectangle_.y / 10;
			}
		}
		
	}
	// 대화창
	
	if (character_x_ >= 240 && character_x_ <= 255 && character_y_ <= 70 && character_y_ >= 60) {
		r4_hint1_render = 1;
	
		if (r4_hint1_cnt > 1) {
			r4_hint1_cnt = 0;
			r4_hint1_render = 0;
		}
	}
	if (character_x_ >= 360 && character_x_ <= 420 && character_y_ <= 80 && character_y_ >= 60) {
		r4_hint2_render = 1;
		
		if (r4_hint1_cnt > 1) {
			r4_hint1_cnt = 0;
			r4_hint2_render = 0;
		}
	}
	if (character_x_ >= 690 && character_x_ <= 710 && character_y_ <= 80 && character_y_ >= 60) {
		
		r4_hint3_render = 1;
		
		if (r4_hint1_cnt > 1) {
			r4_hint1_cnt = 0;
			r4_hint3_render = 0;
		}
	}
	if (character_x_ >= 340 && character_x_ <= 400 && character_y_ <= 360 && character_y_ >= 340) {
		
		r4_hint4_render = 1;
		
		if (r4_hint1_cnt > 1) {
			r4_hint1_cnt = 0;
			r4_hint4_render = 0;
		}
	}
	if (character_x_ >= 680 && character_x_ <= 690 && character_y_ <= 480 && character_y_ >= 460) {
	
		r4_hint5_render = 1;
		if (r4_hint1_cnt > 1) {
			r4_hint1_cnt = 0;
			r4_hint5_render = 0;
		}
	}



}
void Monster2::red_mon_init()
{
	m_Location_false();

	mon_x_ = 680;
	mon_y_ = 460;
	m_destination_redef();
	m_Location_true();

	m_sound_1 = Mix_LoadWAV("../Resources/monster.mp3");
	if (m_sound_1 == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	Mix_PlayChannel(-1, m_sound_1, 0);
}

bool ck_mon = false;
void Monster2::Update()
{

	if (red_mon == true)
	{

		//mon_x_ = 680;
		//mon_y_ = 460;
		red_mon = false;
		red_mon_init();
		
	}
	if (c_rectangle_.y == 33 && c_rectangle_.x > 57)
	{
		red_dis = true;
	}
	if (red_dis == false)
	{
		ck_mon = true;
		return;
	}

	if (ck_mon == false)
	{// 여기
		
	}

	pre_update();


	{
		if (mon_go_right_)
		{
			m_Location_false();

			mon_x_ += 5.;
			m_destination_redef();
			m_Location_true();

			m_move_index = 2;
		}
		else if (mon_go_left_)
		{

			m_Location_false();
			mon_x_ -= 5.;
			m_destination_redef();
			m_Location_true();

			m_move_index = 1;
		}
		if (mon_go_up_)
		{

			m_Location_false();
			mon_y_ -= 5.;
			m_destination_redef();
			m_Location_true();

			m_move_index = 3;


		}
		else if (mon_go_down_)
		{
			m_Location_false();

			mon_y_ += 5.;
			m_destination_redef();
			m_Location_true();

			m_move_index = 0;
		}
	}
}
void Monster2::Render()
{
	
	if (check_red != false)
	{
		if(m_sound_1)
			Mix_FreeChunk(m_sound_1);
		return;
	}
	for (int i = -5; i <= 5; i++)
	{
		if (m_rectangle_.x + i == c_rectangle_.x && m_rectangle_.y + i == c_rectangle_.y)
		{
			character_x_ = 100;
			character_y_ = 140;
			destination_rectangle_.y = (int)character_y_;
			destination_rectangle_.x = (int)character_x_;
			if (m_sound_1)
				Mix_FreeChunk(m_sound_1);
			health_cnt -= 1;
			g_current_game_phase = PHASE_Hall1;
		}
	}

	SDL_RenderCopy(g_renderer, m_texture_, &source_rectangle_m1[m_move_index], &m_destination_rectangle_);
	SDL_RenderPresent(g_renderer);

}
void Monster2::pre_update()
{
	

	if (m_rectangle_.x > 58 && m_rectangle_.y > 20 && m_rectangle_.y < 30)//&& m_rectangle_.x > c_rectangle_.x )//&& com_cnt == true)
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



	if (m_rectangle_.y == 16 && m_rectangle_.x <58)//&& m_rectangle_.x < 80) //윗벽 
	{
		//key_false();
		coor_.x = 60;
		coor_.y = 16;
		//com_cnt = true;
		//mon_go_left_ = true;

		
	}
	else if (m_rectangle_.y == 30 && m_rectangle_.x <58)//&& m_rectangle_.x < 80) //아랫벽
	{

		coor_.x = 60;
		coor_.y = 40;
		
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
void Room4::Render()
{
	
	SDL_RenderCopy(g_renderer, bg_texture_, &bg_source_rectangle_, &bg_destination_rectangle_);


}

void Character11::Render()
{
	r4_hint.x = 130;
	r4_hint.y = 450;
	r4_hint.w = r4_hint1_rect.w;
	r4_hint.h = r4_hint1_rect.h;

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_r4[r4_move_index], &destination_rectangle_);
	SDL_RenderPresent(g_renderer);
	if (r4_hint1_render == 1 && r4_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, r4_hint1, 0, &r4_hint);
		SDL_RenderPresent(g_renderer);
	}
	if (r4_hint2_render == 1 && r4_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, r4_hint2, 0, &r4_hint);
		SDL_RenderPresent(g_renderer);
	}
	if (r4_hint3_render == 1 && r4_hint1_cnt == 1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, r4_hint3, 0, &r4_hint);
		SDL_RenderPresent(g_renderer);
	}
	if (r4_hint4_render == 1 && r4_hint1_cnt == 1&& item_cnt==1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);

		SDL_RenderCopy(g_renderer, r4_hint4, 0, &r4_hint);
		SDL_RenderPresent(g_renderer);
	}
	if (r4_hint5_render == 1 && r4_hint1_cnt == 1&&sword1_cnt==1) {
		SDL_RenderCopy(g_renderer, hint1_texture_, &hint1_source_rectangle_, &hint1_destination_rectangle_);
		SDL_RenderPresent(g_renderer);
		SDL_RenderCopy(g_renderer, r4_hint5, 0, &r4_hint);
		SDL_RenderPresent(g_renderer);
	}
}

void Room4::HandleEvents()
{
}

void Character11::HandleEvents()
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
				if (r4_hint1_render == 1 && r4_hint1_cnt == 1) {
					character_go_left_ = false;
				}
				if (r4_hint2_render == 1 && r4_hint1_cnt == 1) {
					character_go_left_ = false;
				}
				if (r4_hint3_render == 1 && r4_hint1_cnt == 1) {
					character_go_left_ = false;
				}
				if (r4_hint4_render == 1 && r4_hint1_cnt == 1 && item_cnt==1) {
					character_go_left_ = false;
				}
				if (r4_hint5_render == 1 && r4_hint1_cnt == 1&&sword1_cnt==1) {
					character_go_left_ = false;
				}
				{

					for (int i = 2; i < 8; i++) {
						for (int j = 10; j < 16; j++) {
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

								if (m_sound_1)
									Mix_FreeChunk(m_sound_1);

								g_current_game_phase = PHASE_Hall2;
							}

						}
					}
				}
				
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				character_go_right_ = true;
				if (r4_hint1_render == 1 && r4_hint1_cnt == 1) {
					character_go_right_ = false;
				}
				if (r4_hint2_render == 1 && r4_hint1_cnt == 1) {
					character_go_right_ = false;
				}
				if (r4_hint3_render == 1 && r4_hint1_cnt == 1) {
					character_go_right_ = false;
				}
				if (r4_hint4_render == 1 && r4_hint1_cnt == 1 && item_cnt == 1) {
					character_go_right_ = false;
				}
				if (r4_hint5_render == 1 && r4_hint1_cnt == 1 && sword1_cnt == 1) {
					character_go_right_ = false;
				}

			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				character_go_up_ = true;
				if (r4_hint1_render == 1 && r4_hint1_cnt == 1) {
					character_go_up_ = false;
				}
				if (r4_hint2_render == 1 && r4_hint1_cnt == 1) {
					character_go_up_ = false;
				}
				if (r4_hint3_render == 1 && r4_hint1_cnt == 1) {
					character_go_up_ = false;
				}
				if (r4_hint4_render == 1 && r4_hint1_cnt == 1 && item_cnt == 1) {
					character_go_up_ = false;
				}
				if (r4_hint5_render == 1 && r4_hint1_cnt == 1 && sword1_cnt == 1) {
					character_go_up_ = false;
				}

			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				character_go_down_ = true;
				if (r4_hint1_render == 1 && r4_hint1_cnt == 1) {
					character_go_down_ = false;
				}
				if (r4_hint2_render == 1 && r4_hint1_cnt == 1) {
					character_go_down_ = false;
				}
				if (r4_hint3_render == 1 && r4_hint1_cnt == 1) {
					character_go_down_ = false;
				}
				if (r4_hint4_render == 1 && r4_hint1_cnt == 1 && item_cnt == 1) {
					character_go_down_ = false;
				}
				if (r4_hint5_render == 1 && r4_hint1_cnt == 1 && sword1_cnt == 1) {
					character_go_down_ = false;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (character_x_ >= 240 && character_x_ <= 255 && character_y_ <= 70 && character_y_ >= 60) {
					r4_hint1_cnt++;
					r4_hint1_render = 1;
					r4_hint2_render = 0;
					r4_hint3_render = 0;
					r4_hint4_render = 0;
					r4_hint5_render = 0;
				}
				if (character_x_ >= 360 && character_x_ <= 420 && character_y_ <= 80 && character_y_ >= 60) {
					r4_hint1_cnt++;
					r4_hint1_render = 0;
					r4_hint2_render = 1;
					r4_hint3_render = 0;
					r4_hint4_render = 0;
					r4_hint5_render = 0;
				}
				if (character_x_ >= 690 && character_x_ <= 710 && character_y_ <= 80 && character_y_ >= 60) {
					r4_hint1_cnt++;
					r4_hint1_render = 0;
					r4_hint2_render = 0;
					r4_hint3_render = 1;
					r4_hint4_render = 0;
					r4_hint5_render = 0;
				}
				if (character_x_ >= 340 && character_x_ <= 400 && character_y_ <= 360 && character_y_ >= 340) {
					r4_hint1_cnt++;
					r4_hint1_render = 0;
					r4_hint2_render = 0;
					r4_hint3_render = 0;
					r4_hint4_render = 1;
					r4_hint5_render = 0;
					item_cnt++;
				}
				if (character_x_ >= 680 && character_x_ <= 690 && character_y_ <= 480 && character_y_ >= 460) {
					r4_hint1_cnt++;
					r4_hint1_render = 0;
					r4_hint2_render = 0;
					r4_hint3_render = 0;
					r4_hint4_render = 0;
					r4_hint5_render = 1;
					sword1_cnt++;
				}
			}
			else if (event.key.keysym.sym == SDLK_d) {
				character_go_left_ = false;
				character_go_right_ = false;
				character_go_up_ = false;
				character_go_down_ = false;
				inventory_cnt = 10;
				g_current_game_phase = PHASE_Inventory;

			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				character_go_left_ = false;
				{

					for (int i = 2; i < 8; i++) {
						for (int j = 10; j < 16; j++) {
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

								if (check_red == true)
									check_red = false;
								else
									check_red = true;

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
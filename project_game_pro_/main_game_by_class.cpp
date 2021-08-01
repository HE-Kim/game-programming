
#include "SDL.h"
#include <iostream>
#include "GameClassPhase.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
//#include "GameClassIntro.h"
#include "GameClassHall1.h"
#include "GameClassHall2.h"
#include "GameClassRoom1.h"
#include "GameClassMovie1.h"
#include "GameClassToilet1.h"
//#include "GameClassEnding.h"
#include "GameClass_character.h"
#include "GameClassRoom2.h"
#include "GameClassToilet2.h"
#include "GameClassRoom3.h"
#include "GameClassRoom4.h"
#include "GameClassMovie2.h"
#include "GameClassLounge.h"
#include "GameClassWarehouse.h"
#include "GameClassMonster.h"
#include "GameClassStore.h"
#include "GameClassInventory.h"
#include "GameClassStory1.h"
#include "GameClassStory2.h"
#include "GameClassRule.h"
#include "GameClassIntro.h"
#include "GameClassEnding.h"
/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
int g_frame_time_ms = 40;

bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen);
void CleanWindow();

bool stage1_cnt = false;
bool stage2_cnt = false;


// Game Phases
int g_current_game_phase;

int main(int argc, char* argv[])
{
	InitializeWindow("Game By Class", 100, 100, 800, 600, false);
	TTF_Init();

	int audio_rate = 44100;//MIX_DEFAULT_FREQUENCY;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	int audio_channels = 2;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0)
	{
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		Mix_CloseAudio();
	}
	else
	{
		// For debug
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		printf("Opened audio at %d Hz %d bit %s\n", audio_rate,
			(audio_format & 0xFF),
			(audio_channels > 2) ? "surround" :
			(audio_channels > 1) ? "stereo" : "mono");

	}

//	Intro intro;
	Rule Rule;
	Story1 Story1;
	Story2 Story2;
	Intro Intro;
	Ending Ending;
	Hall1 Hall1;
	Hall2 Hall2;
	Room1 Room1;
	Room2 Room2;
	Room3 Room3;
	Room4 Room4;
	Movie1 Movie1;
	Movie2 Movie2;
	Toilet1 Toilet1;
	Toilet2 Toilet2;
	Lounge Lounge;
	Warehouse Warehouse;
	Store Store;
	Inventory Inventory;

	Monster1 Monster1;
	Monster2 Monster2;

	Character character;
	Character2 character_2;
	Character3 character_3;
	Character4 character_4;
	Character5 character_5;
	Character6 character_6;
	Character7 character_7;
	Character8 character_8;
	Character10 character_10;
	Character11 character_11;
	Character12 character_12;
	Character13 character_13;
	Character14 character_14;
	Character15 character_15;

//	Ending ending;

	g_current_game_phase = PHASE_Intro;

	while ( g_flag_running )
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if ( cur_time_ms-g_last_time_ms < g_frame_time_ms )
			continue;

		/*if ( g_current_game_phase ==  PHASE_INTRO )
		{
			intro.HandleEvents();
			intro.Update();
			intro.Render();
		}*/
		if (g_current_game_phase == PHASE_Intro)
		{
			Intro.HandleEvents();
			//Intro.Update();
			Intro.Render();
		}
		if (g_current_game_phase == PHASE_Ending)
		{
			Ending.HandleEvents();
			//Intro.Update();
			Ending.Render();
		}
		if (g_current_game_phase == PHASE_Story1)
		{
			Story1.HandleEvents();
			//Intro.Update();
			Story1.Render();
		}
		if (g_current_game_phase == PHASE_Story2)
		{
			Story2.HandleEvents();
			//Intro.Update();
			Story2.Render();
		}
		if (g_current_game_phase == PHASE_Rule)
		{
			Rule.HandleEvents();
			//Intro.Update();
			Rule.Render();
		}
		if ( g_current_game_phase == PHASE_Hall1 )
		{

			Hall1.HandleEvents();
			character.HandleEvents();
			
			Hall1.Update();
			character.Update();
			//Monster1.Update();
		
			Hall1.Render();
			character.Render();
			//Monster1.Render();
			
			
			
			
		}
		if (g_current_game_phase == PHASE_Room1)
		{

			Room1.HandleEvents();
			character_2.HandleEvents();
			Room1.Update();
			character_2.Update();
			Monster1.Update();

			Room1.Render();
			character_2.Render();
			Monster1.Render();
		}
		else if (g_current_game_phase == PHASE_Movie1)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Movie1.HandleEvents();
			character_3.HandleEvents();
			Movie1.Update();
			character_3.Update();
			Movie1.Render();
			character_3.Render();

		}
		
		else if (g_current_game_phase == PHASE_Toilet1)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Toilet1.HandleEvents();
			character_4.HandleEvents();
			Toilet1.Update();
			character_4.Update();
			Toilet1.Render();
			character_4.Render();

		}
		else if (g_current_game_phase == PHASE_Hall2)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Hall2.HandleEvents();
			character_5.HandleEvents();
			Hall2.Update();
			character_5.Update();
			Hall2.Render();
			character_5.Render();

		}
		else if (g_current_game_phase == PHASE_Room2)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Room2.HandleEvents();
			character_6.HandleEvents();
			Room2.Update();
			character_6.Update();
			Room2.Render();
			character_6.Render();

		}
		else if (g_current_game_phase == PHASE_Toilet2)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Toilet2.HandleEvents();
			character_7.HandleEvents();
			Toilet2.Update();
			character_7.Update();
			Toilet2.Render();
			character_7.Render();

		}
		else if (g_current_game_phase == PHASE_Room3)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Room3.HandleEvents();
			character_8.HandleEvents();
			Room3.Update();
			character_8.Update();
			Room3.Render();
			character_8.Render();

		}
		
		else if (g_current_game_phase == PHASE_Movie2)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Movie2.HandleEvents();
			character_10.HandleEvents();
			Movie2.Update();
			character_10.Update();
			Movie2.Render();
			character_10.Render();

		}
		else if (g_current_game_phase == PHASE_Room4)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Room4.HandleEvents();
			character_11.HandleEvents();
			Room4.Update();
			character_11.Update();
			Monster2.Update();

			Room4.Render();
			character_11.Render();
			Monster2.Render();

		}

		else if (g_current_game_phase == PHASE_Lounge)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Lounge.HandleEvents();
			character_12.HandleEvents();
			Lounge.Update();
			character_12.Update();
			Lounge.Render();
			character_12.Render();

		}
		else if (g_current_game_phase == PHASE_Warehouse)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Warehouse.HandleEvents();
			character_13.HandleEvents();
			Warehouse.Update();
			character_13.Update();
			Warehouse.Render();
			character_13.Render();

		}
		else if (g_current_game_phase == PHASE_Store)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Store.HandleEvents();
			character_14.HandleEvents();
			Store.Update();
			character_14.Update();
			Store.Render();
			character_14.Render();

		}
		else if (g_current_game_phase == PHASE_Inventory)
		{
			//Stage2 stage2;
			//Character2 character_2;

			//std::cout << "main_stage2";
			//std::cout << std::endl;

			Inventory.HandleEvents();
			character_15.HandleEvents();
			Inventory.Render();
		    character_15.Update();
			Inventory.Update();
			character_15.Render();
		}
		
		/*
		else if ( g_current_game_phase == PHASE_ENDING )
		{
			ending.HandleEvents();
			ending.Update();
			ending.Render();
		}
		*/
		g_last_time_ms = cur_time_ms;
	}

	CleanWindow();
	TTF_Quit();


	return 0;
}



////////////////////////////////////
// Functions for the Window
bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		g_window = SDL_CreateWindow(title, xpos, ypos, 
			width, height, flags);

		if(g_window != 0) // window init success
		{
			std::cout << "window creation success\n";
			g_renderer = SDL_CreateRenderer(g_window, -1, 0);
			if(g_renderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(g_renderer, 
					255,255,255,255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	g_flag_running = true; // everything inited successfully, start the main loop

	return true;

}



void CleanWindow()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	SDL_Quit();
}
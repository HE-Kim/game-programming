#include "SDL_image.h"
#include <iostream>
#include <windows.h>
#include "GameClassRule.h"
#include "GameClassPhase.h"


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
SDL_Texture *rule;
SDL_Rect rule_rect;



Rule::Rule()
{
	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/rule.png");
	texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture, NULL, NULL, &source_rect.w, &source_rect.h);
	//텍스쳐에서 정보를 가져옵니다. 두번째 인수는 포맷, 세번째인수는 접근 관련, 네번째와
	//다섯번쨰는 가로, 세로 크기입니다. 만약 NULL을 인수로 넣으면 딱히 값을 저장하지 않지만 포인터를 전달하면 값을 저장합니다.
	destination_rect.x = source_rect.x = 0;
	destination_rect.y = source_rect.y = 0;
	destination_rect.w = source_rect.w;
	destination_rect.h = source_rect.h;





}

void Rule::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_RenderCopy(g_renderer, texture, &source_rect, &destination_rect);
	// draw to the screen



	SDL_RenderPresent(g_renderer);
}
Rule::~Rule()
{
	SDL_DestroyTexture(texture);

}

void Rule::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_current_game_phase = PHASE_Story1;
			}
			break;

		default:
			break;
		}
	}
}



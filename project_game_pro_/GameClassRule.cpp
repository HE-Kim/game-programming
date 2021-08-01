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
	//�ؽ��Ŀ��� ������ �����ɴϴ�. �ι�° �μ��� ����, ����°�μ��� ���� ����, �׹�°��
	//�ټ������� ����, ���� ũ���Դϴ�. ���� NULL�� �μ��� ������ ���� ���� �������� ������ �����͸� �����ϸ� ���� �����մϴ�.
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



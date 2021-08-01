#include "SDL_image.h"
#include <iostream>
#include <windows.h>
#include "GameClassStory2.h"
#include "GameClassPhase.h"


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
SDL_Texture *story2;
SDL_Rect story2_rect;



Story2::Story2()
{
	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/story2.png");
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

void Story2::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_RenderCopy(g_renderer, texture, &source_rect, &destination_rect);
	// draw to the screen



	SDL_RenderPresent(g_renderer);
}
Story2::~Story2()
{
	SDL_DestroyTexture(texture);

}

void Story2::HandleEvents()
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
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				g_current_game_phase = PHASE_Hall1;

			}
			break;

		default:
			break;
		}
	}
}

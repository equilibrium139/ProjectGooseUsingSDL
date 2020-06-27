#include <SDL.h>

#include <iostream>

#include <SDL.h>

#include "Logger.h"
#include "Texture.h"
#include "SDL_image.h"

struct SDL_Deleter {
	void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
	void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
	void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
};

// Unique Pointers
using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool quit = false;

int goose_x = 0;
int goose_y = 0;

const int goose_speed = 1;

void pollEvents(void);

int main(int argc, char* argv[])
{
	// SDL boilerplate, skip below for game loop

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not intialize. Error:\n" << SDL_GetError() << '\n';
		return 1;
	}

	WindowPtr window(SDL_CreateWindow("SDL Tutorial", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
	if (!window)
	{
		logSDLError("SDL_CreateWindow");
		SDL_Quit();
		return 1;
	}

	RendererPtr renderer(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (!renderer)
	{
		SDL_DestroyWindow(window.get());
		logSDLError("SDL_CreateRenderer");
		SDL_Quit();
		return 1;
	}

	// Initializing SDL_image at startup (optional)
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError("IMG_Init");
		SDL_Quit();
		return 1;
	}

	TexturePtr goose(loadTexture("Assets/goose_spritesheet.png", renderer.get()));
	int goose_spritesheet_w;
	int goose_spritesheet_h;
	SDL_QueryTexture(goose.get(), NULL, NULL, &goose_spritesheet_w, &goose_spritesheet_h);
	int goose_h = goose_spritesheet_h / 3;

	SDL_Rect goose_spritesheet_clips[3];
	for (int i = 0; i < 3; ++i)
	{
		goose_spritesheet_clips[i].x = 0;
		goose_spritesheet_clips[i].y = goose_h * i;
		goose_spritesheet_clips[i].w = goose_spritesheet_w;
		goose_spritesheet_clips[i].h = goose_h;
	}

	int use_clip = 0;

	bool mirrored = false;

	Uint32 time_since_anim_updated = 0;
	const Uint32 anim_update_interval = 200;
	Uint32 last_frame_time = SDL_GetTicks();
	Uint32 dt = 0;

	while (!quit)
	{
		pollEvents();

		dt = SDL_GetTicks() - last_frame_time;
		last_frame_time = SDL_GetTicks();

		time_since_anim_updated += dt;

		const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
		if (keyboard_state[SDL_SCANCODE_W])
		{
			goose_y -= goose_speed;
		}
		if (keyboard_state[SDL_SCANCODE_S])
		{
			goose_y += goose_speed;
		}
		if (keyboard_state[SDL_SCANCODE_A])
		{
			mirrored = true;
			goose_x -= goose_speed;
		}
		if (keyboard_state[SDL_SCANCODE_D])
		{
			mirrored = false;
			goose_x += goose_speed;
		}

		if (goose_y < 0)
		{
			goose_y = 0;
		}
		else if (goose_y + 50 > SCREEN_HEIGHT)
		{
			goose_y = SCREEN_HEIGHT - 50;
		}
		if (goose_x < 0)
		{
			goose_x = 0;
		}
		else if (goose_x + 50 > SCREEN_WIDTH)
		{
			goose_x = SCREEN_WIDTH - 50;
		}

		// update sprite
		if (time_since_anim_updated > anim_update_interval)
		{
			use_clip = (use_clip + 1) % 3;
			time_since_anim_updated = 0;
		}
		
		SDL_RenderClear(renderer.get());
		
		renderTexture(goose.get(), renderer.get(), &goose_spritesheet_clips[use_clip], goose_x, goose_y, 50, 50, mirrored);

		SDL_RenderPresent(renderer.get());
	}

	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void pollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		if (e.type == SDL_KEYDOWN) {
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
		}
	}
}
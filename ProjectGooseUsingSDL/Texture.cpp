#include "Texture.h"
#include "Logger.h"

#include <SDL_image.h>

SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, file);
	
	if (!texture)
	{
		logSDLError("CreateTextureFromSurface");
	}

	return texture;
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, bool mirrored)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	if (!mirrored)
	{
		SDL_RenderCopy(renderer, texture, NULL, &dst);
	}
	else
	{
		SDL_RenderCopyEx(renderer, texture, NULL, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h, bool mirrored)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	if (!mirrored)
	{
		SDL_RenderCopy(renderer, texture, NULL, &dst);
	}
	else
	{
		SDL_RenderCopyEx(renderer, texture, NULL, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, const SDL_Rect* src, int x, int y, bool mirrored)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

	if (!mirrored)
	{
		SDL_RenderCopy(renderer, texture, src, &dst);
	}
	else
	{
		SDL_RenderCopyEx(renderer, texture, src, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, const SDL_Rect* src, int dstX, int dstY, int dstW, int dstH, bool mirrored)
{
	SDL_Rect dst;
	dst.x = dstX;
	dst.y = dstY;
	dst.w = dstW;
	dst.h = dstH;

	if (!mirrored)
	{
		SDL_RenderCopy(renderer, texture, src, &dst);
	}
	else
	{
		SDL_RenderCopyEx(renderer, texture, src, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
}

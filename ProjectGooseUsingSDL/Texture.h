#pragma once

#include <SDL.h>

SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int dstX, int dstY, bool mirrored = false);
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int dstX, int dstY, int dstW, int dstH, bool mirrored = false);
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, const SDL_Rect* src, int dstX, int dstY, bool mirrored = false);
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, const SDL_Rect* src, int dstX, int dstY, int dstW, int dstH, bool mirrored = false);
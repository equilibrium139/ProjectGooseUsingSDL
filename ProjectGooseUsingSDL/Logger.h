#pragma once

#include <SDL.h>

#include <iostream>

inline void logSDLError(const char* function_name)
{
	std::cout << function_name << " error: " << SDL_GetError() << '\n';
}
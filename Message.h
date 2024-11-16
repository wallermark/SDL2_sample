#pragma once
#include <SDL.h>
#include <string>

inline void displayInformation(const std::string& title, const std::string& message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
}

inline void displayError(const std::string& title, const std::string& message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), NULL);
}

inline void fatalError(const std::string& title, const std::string& message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), NULL);
	exit(1);
}

#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <functional>

#include "Message.h"

class Button
{
public:
	Button(const std::string text,
		const unsigned int size,
		const unsigned int x,
		const unsigned int y,
		const SDL_Color& color,
		const SDL_Color& background,
		unsigned int padding,
		std::function<void()> action);
	~Button();

public:
	void handleEvent(const SDL_Event& e);
	void render(SDL_Renderer* gRenderer);

private:
	bool IsWithinBounds(int x, int y) const;

private:
	bool _valid;
	std::string _text;
	unsigned int _fontsize;
	SDL_Rect _rect;
	SDL_Rect _textrect;
	SDL_Color _color;
	SDL_Color _background;
	std::function<void()> _action;
	SDL_Surface* _surface;
	TTF_Font* _font;
};
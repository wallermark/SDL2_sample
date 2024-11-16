#include "Button.h"

Button::Button(const std::string text,
	const unsigned int fontsize,
	const unsigned int x,
	const unsigned int y,
	const SDL_Color& color,
	const SDL_Color& background,
	unsigned int padding,
	std::function<void()> action) :
	_valid(false),
	_text(text),
	_fontsize(fontsize),
	_color(color),
	_background(background),
	_action(action),
	_surface(NULL),
	_font(NULL)
{
	_font = TTF_OpenFont("FreeSans.ttf", _fontsize);
	if (_font == NULL) 	fatalError("Failed to open font", TTF_GetError());

	_surface = TTF_RenderText_Solid(_font, _text.c_str(), _color);

	// calculate the button size and rectangles
	int width, height;
	TTF_SizeText(_font, _text.c_str(), &width, &height);
	_textrect = { static_cast<int>(x + padding), static_cast<int>(y + padding), width,height };
	_rect = { static_cast<int>(x), static_cast<int>(y), width + (static_cast<int>(padding) * 2), height + (static_cast<int>(padding) * 2) };

	_valid = true;
}

void Button::render(SDL_Renderer* gRenderer)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, _surface);

	//Render red filled quad
	SDL_SetRenderDrawColor(gRenderer, _background.r, _background.g, _background.b, _background.a);
	SDL_RenderFillRect(gRenderer, &_rect);

	// Render the test
	SDL_RenderCopy(gRenderer, texture, NULL, &_textrect);

	SDL_DestroyTexture(texture);
}

void Button::handleEvent(const SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_LEFT &&
		IsWithinBounds(e.button.x, e.button.y))
	{
		std::invoke(_action);
	}
}

bool Button::IsWithinBounds(int x, int y) const {
	// Too far left
	if (x < _rect.x) return false;
	// Too far right
	if (x > _rect.x + _rect.w) return false;
	// Too high
	if (y < _rect.y) return false;
	// Too low
	if (y > _rect.y + _rect.h) return false;
	// Within bounds
	return true;
}

Button::~Button()
{
	free(_surface);
	free(_font);
}
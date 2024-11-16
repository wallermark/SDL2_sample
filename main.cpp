#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <string>
#include <cmath>
#include <functional>
#include <list>

#include "Message.h"
#include "Button.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


void buttonPressed()
{
	displayInformation("Button pressed", "Don't press this button again!");
}

int main(int argc, char* args[]) 
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		fatalError("Could not initialize sdl2", SDL_GetError());
	}

	if (TTF_Init() < 0 ) 
	{
		fatalError("Could not initialize TTF_Init", TTF_GetError());
	}

	// Create a window
	SDL_Window* window = NULL;
	window = SDL_CreateWindow(
		"Hello World",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL) 
	{
		fatalError("Could not create window", SDL_GetError());
	}

	//The window renderer
	SDL_Renderer* gRenderer = NULL;
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		fatalError("Renderer could not be created!", SDL_GetError());
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Red = { 255, 0, 0 };

	//create some buttons
	std::list<Button*> buttons;
	Button* button1 = new Button("Press me!", 20, 100, 100, White, Black, 5, buttonPressed);
	buttons.push_back(button1);
	Button* button2 = new Button("This is a button", 20, 100, 200, Black, Red, 5, buttonPressed);
	buttons.push_back(button2);

	//Event handler - while application is running
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//User presses a mouse button
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				for (auto button : buttons)
				{
					button->handleEvent(e);
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xee, 0xee, 0xee, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render red filled quad
		SDL_Rect fillRect = { 100 , 300 , 30 , 30 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect);

		//Render the buttons
		for (auto button : buttons)
		{
			button->render(gRenderer);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

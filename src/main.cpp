//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "dot.h"
#include "ltexture.h"
#include "ltimer.h"
#include "renderer.h"
#include "controller.h"


int main(int argc, char *args[])
{
	LTexture gDotTexture;
	Renderer RenderObj;

	//Start up SDL and create window
	if (!RenderObj.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!RenderObj.loadMedia(gDotTexture))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;

			//While application is running
			while (!quit)
			{
				Controller controller;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					controller.handleEvent(e, dot);
				}

				//Move the dot
				dot.move(RenderObj.getScreenWidth(), RenderObj.getScreenHeight());

				//Clear screen

				//RenderObj.Render(dot);

				SDL_SetRenderDrawColor(RenderObj.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(RenderObj.gRenderer);

				//Render objects
				dot.render(gDotTexture, RenderObj);

				//Update screen
				SDL_RenderPresent(RenderObj.gRenderer);
			}
		}
	}

	//Free resources and close SDL
	RenderObj.close(gDotTexture);

	return 0;
}
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
			
			//The timer for everything - may want to make a separate simulate() function to run the thread and initiate earlier
			LTimer Timer;

			//placing the timer function process in a separate thread
			//threads.emplace_back(std::thread(LTimer.spawnFrequency()));
		
			//The dots that will be moving around on the screen
			Dot dot(RenderObj.SCREEN_WIDTH/2,RenderObj.SCREEN_HEIGHT - 100,0,0);

			//level dummy value;
			int level = 1;

			//AstObj vector
			std::vector<Dot> AstVec{};

			//Loop for instantiating a bunch of Asteroids
			for (int i = 0; i < level; i++)
			{
				int origin = rand() % RenderObj.SCREEN_WIDTH;
				//std::cout << "origin is: " << origin << std::endl;
				AstVec.emplace_back(origin, 0, 0, 1);
				//std::cout << "AstVec id: " << &AstVec[i] << std::endl;
			}

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

				//Move the dot controlled by user
				dot.move(RenderObj.getScreenWidth(), RenderObj.getScreenHeight());
				

				for (int i = 0; i < Timer.getMax(); i++)
				{
					if(AstVec[i].getPosY() >= RenderObj.SCREEN_HEIGHT -20) {
						AstVec[i].setPosX(rand() % RenderObj.getScreenWidth());
						AstVec[i].setPosY(0);
					}
					//move the asteroids
					AstVec[i].move(RenderObj.getScreenWidth(), RenderObj.getScreenHeight());

					//Check for Collision
					if (RenderObj.CheckCollision(dot.Collider, AstVec[i].Collider)) {
						AstVec[i].setPosX(rand() % RenderObj.getScreenWidth());
						AstVec[i].setPosY(0);
						std::cout << "We've F'd UP!" << std::endl;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(RenderObj.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(RenderObj.gRenderer);

				//Render objects
				dot.render(gDotTexture, RenderObj);
				for (int i = 0; i < Timer.getMax(); i++)
				{
					//mov the asteroids
					AstVec[i].render(gDotTexture, RenderObj);
				}

				//Update screen
				SDL_RenderPresent(RenderObj.gRenderer);
			}

			//threads[0].join();
		}
	}

	//Free resources and close SDL
	RenderObj.close(gDotTexture);

	//Display temperature and asteroids avoided
	std::cout << "Final Temperature: " << std::endl;

	return 0;
}
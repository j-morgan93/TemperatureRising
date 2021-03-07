//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_thread.h>
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

			//Event handler
			SDL_Event e;
			
			//The timer for everything - may want to make a separate simulate() function to run the thread and initiate earlier
			LTimer Timer;

			Timer.simulate();

			//SDL_Thread *timerthread = SDL_CreateThread(LTimer::spawnMax, "Timerthread",Timer.quit);
		
			//The dots that will be moving around on the screen
			Dot dot(RenderObj.SCREEN_WIDTH/2,RenderObj.SCREEN_HEIGHT - 100,0,0);

			//level dummy value;
			int level = 1;

			//AstObj vector
			std::vector<Dot> AstVec{};

			//While application is running
			while (!Timer.getQuit())
			{
				Controller controller;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						Timer.setQuit();
					}

					//Handle input for the dot
					controller.handleEvent(e, dot);
				}
				if (AstVec.size() < Timer.getMax()) //Loop for instantiating a bunch of Asteroids
				{
					std::cout << "Smaller!" << std::endl;
					int origin = rand() % RenderObj.SCREEN_WIDTH;
					//std::cout << "origin is: " << origin << std::endl;
					AstVec.emplace_back(origin, 0, 0, 1);
					//std::cout << "AstVec id: " << &AstVec[i] << std::endl;
				}

				//Move the dot controlled by user
				dot.move(RenderObj.getScreenWidth(), RenderObj.getScreenHeight());
				//move the asteroids
				for (unsigned i = 0; i < AstVec.size(); i++)
				{
					AstVec[i].move(RenderObj.getScreenWidth(), RenderObj.getScreenHeight());
				}

				//check for out of bounds movement.
				std::vector<int> delv;
				for (unsigned i = 0; i < AstVec.size(); i++)
				{
					if(AstVec[i].getPosY() >= RenderObj.SCREEN_HEIGHT -20) {
						delv.push_back(i);
					}

					//Check for Collision
					if (RenderObj.CheckCollision(dot.Collider, AstVec[i].Collider)) {
						delv.push_back(i);
						std::cout << "We've F'd UP!" << std::endl;
					}
				}

				//delete the affect Asteroid bodies from the vector
				for (unsigned i=0; i< delv.size(); i++) {
					AstVec.erase(AstVec.begin() + delv[i]);
				}

				//Clear screen
				SDL_SetRenderDrawColor(RenderObj.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(RenderObj.gRenderer);

				//Render objects
				dot.render(gDotTexture, RenderObj);
				for (unsigned i = 0; i < AstVec.size(); i++)
				{
					//mov the asteroids
					AstVec[i].render(gDotTexture, RenderObj);
				}

				//Update screen
				SDL_RenderPresent(RenderObj.gRenderer);
			}
			//SDL_WaitThread(timerthread, NULL);
			//threads[0].join();
		}
	}

	//Free resources and close SDL
	RenderObj.close(gDotTexture);

	//Display temperature and asteroids avoided
	std::cout << "Final Temperature: " << std::endl;

	return 0;
}
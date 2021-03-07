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
	//Loading our textures and creating the Window-Renderer
	LTexture gAstTexture;
	LTexture gM2020Texture;
	Renderer RenderObj;

	//Start up SDL and create window
	if (!RenderObj.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media - you'll want to be careful of the load path.
		if (!RenderObj.loadMedia("/home/workspace/TemperatureRising/TemperatureRising/src/asteroid.bmp",gAstTexture))
		{
			printf("Failed to load media!\n");
		}
		if (!RenderObj.loadMedia("/home/workspace/TemperatureRising/TemperatureRising/src/m2020_1.bmp" ,gM2020Texture))
		{
			printf("Failed to load media!\n");
		}
		else
		{

			/* Initializing required components */
			//Event handler
			SDL_Event e;
			
			//The timer for everything - may want to make a separate simulate() function to run the thread and initiate earlier
			LTimer Timer;

			Timer.simulate();
		
			//The dots that will be moving around on the screen
			Dot dot(RenderObj.SCREEN_WIDTH/2,RenderObj.SCREEN_HEIGHT - 100,0,0);

			//AstObj vector
			std::vector<Dot> AstVec{};

			//Controller initialization
			Controller controller;

			//While application is running
			while (!Timer.getQuit())
			{
			
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

				//Loop for instantiating a bunch of Asteroids based on Max
				if (AstVec.size() < Timer.getMax()) 
				{
					
					int origin = rand() % RenderObj.SCREEN_WIDTH;
					AstVec.emplace_back(origin, 0, 0, 1);
					
				}

				//Move the dot controlled by user
				dot.move(RenderObj.getScreenWidth(), RenderObj.getScreenHeight());
				//move the asteroids
				for (unsigned i = 0; i < AstVec.size(); i++)
				{
					AstVec[i].move(RenderObj.getScreenWidth(), RenderObj.getScreenHeight());
				}

				//Check for out of bounds movement.
				std::vector<int> delv;
				for (unsigned i = 0; i < AstVec.size(); i++)
				{
					if(AstVec[i].getPosY() >= RenderObj.SCREEN_HEIGHT -20) {
						delv.push_back(i);
						Timer.setScore();
					}

					//Check for Collision
					if (RenderObj.CheckCollision(dot, AstVec[i])) {
						delv.push_back(i);
					}
				}

				//delete the affect Asteroid bodies from the vector
				for (unsigned i=0; i< delv.size(); i++) {
					AstVec.erase(AstVec.begin() + delv[i]);
				}

				//Clear screen
				SDL_SetRenderDrawColor(RenderObj.gRenderer, 0, 0, 0, 0);
				SDL_RenderClear(RenderObj.gRenderer);

				//Render objects
				dot.render(gM2020Texture, RenderObj);
				for (unsigned i = 0; i < AstVec.size(); i++)
				{
					//mov the asteroids
					AstVec[i].render(gAstTexture, RenderObj);
				}

				//Update screen
				SDL_RenderPresent(RenderObj.gRenderer);

				if (dot.getTemp() >= 250)
				{
					Timer.setQuit();
					std::cout << "Too Hot - We've Failed!" <<std::endl;					
				}
				
			}
			//Display temperature and asteroids avoided
			std::cout << "Final Temperature:  " << dot.getTemp() << " F , Score: " << Timer.getScore() << std::endl;
		}
	}

	//Free resources and close SDL
	RenderObj.close(gAstTexture);
	RenderObj.close(gM2020Texture);

	return 0;
}
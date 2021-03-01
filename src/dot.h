#ifndef DOT_H
#define DOT_H

#include<vector>
#include "SDL.h"
#include "ltimer.h"
#include "ltexture.h"
#include "renderer.h"

class LTexture;

class Renderer;

//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 2;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move(const int width, const int height);

		//Shows the dot on the screen
		void render(LTexture &gDotTexture, Renderer &RenderObj);

				//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

    private:

};

#endif
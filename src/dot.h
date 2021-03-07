#ifndef DOT_H
#define DOT_H

#include<vector>
#include "SDL.h"
#include "ltimer.h" //not needed, yet!
#include "ltexture.h"
#include "renderer.h"

//decided to forward declare here, oops!
class LTexture;
class Renderer;

//The dot that will move around on the screen
class Dot
{
    public:
		//Initializes the variables
		Dot(int mPosX, int mPosY, int mVelX, int mVelY);

		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 2;

		//modify the Dot properties
		void setPosX(int px) {mPosX = px;}
		void setPosY(int py) {mPosY = py;}
		void setVelX(int vx) {mVelX = vx;}
		void setVelY(int vy) {mVelY = vy;}

		//get the Dot properties
		int getPosX() {return mPosX;}
		int getPosY() {return mPosY;}
		int getVelX() {return mVelX;}
		int getVelY() {return mVelY;}

		//turn up the heat
		void tempup();

		//get temperature
		int gettemp() {return temp;}

		//Moves the dot
		void move(const int width, const int height);

		//Shows the dot on the screen
		void render(LTexture &gDotTexture, Renderer &RenderObj);

		//The Collision Box
		SDL_Rect Collider;

	private:

		//The X and Y offsets of the dot
		int mPosX=0;
		int mPosY=0;

		//The velocity of the dot
		int mVelX=0;
		int mVelY=0;

		//temperature
		int temp{-80};
};

#endif
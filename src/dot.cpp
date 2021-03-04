#include "dot.h"

Dot::Dot(int mPosX, int mPosY, int mVelX, int mVelY)
{
    //Initialize the offsets
    setPosX(mPosX);
    setPosY(mPosY);

    //Initialize the velocity
    setVelX(mVelX);
    setVelY(mVelY);

    //Sizing the box appropriately
    Collider.w = DOT_WIDTH;
    Collider.h = DOT_HEIGHT;
}


void Dot::move(const int width, const int height)
{
    //Move the dot left or right
    setPosX(getPosX() + getVelX());
    

    //If the dot went too far to the left or right
    if( ( getPosX() < 0 ) || ( getPosX() + DOT_WIDTH > width ) )
    {
        //Move back
        setPosX(getPosX() - getVelX());
    }

    //Set the Rectangle to Dot X value;
    Collider.x = mPosX;

    //Move the dot up or down
    setPosY(getPosY() + getVelY());

    //If the dot went too far up or down
    if( ( getPosY() < 0 ) || ( getPosY() + DOT_HEIGHT > height ) )
    {
        //Move back
        setPosY(getPosY() - getVelY());
    }

    //Set the Rectangle to Dot Y value;
    Collider.y = mPosY;
}

void Dot::render(LTexture &gDotTexture, Renderer &RenderObj)
{
    //Show the dot
	gDotTexture.render( mPosX, mPosY, RenderObj );
}

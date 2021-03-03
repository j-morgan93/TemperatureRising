#include "dot.h"

Dot::Dot(int mPosX, int mPosY, int mVelX, int mVelY)
{
    //Initialize the offsets
    setPosX(mPosX);
    setPosY(mPosY);

    //Initialize the velocity
    setVelX(mVelX);
    setVelY(mVelY);
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

    //Move the dot up or down
    setPosY(getPosY() + getVelY());

    //If the dot went too far up or down
    if( ( getPosY() < 0 ) || ( getPosY() + DOT_HEIGHT > height ) )
    {
        //Move back
        setPosY(getPosY() - getVelY());
    }
}

void Dot::render(LTexture &gDotTexture, Renderer &RenderObj)
{
    //Show the dot
	gDotTexture.render( mPosX, mPosY, RenderObj );
}

#include "dot.h"

Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Dot::move(const int width, const int height)
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > width ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > height ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Dot::render(LTexture &gDotTexture, Renderer &RenderObj)
{
    //Show the dot
	gDotTexture.render( mPosX, mPosY, RenderObj );
}

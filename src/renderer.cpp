#include "renderer.h"

bool Renderer::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "F'd Up!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Renderer::loadMedia(std::string path,LTexture &gDotTexture)
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gDotTexture.loadFromFile( path, this->gRenderer) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	return success;
}

void Renderer::close(LTexture &gDotTexture)
{
	//Free loaded images
	gDotTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Renderer::Render(Dot const dot) {

	  // Clear screen
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
}

bool Renderer::CheckCollision(Dot &a, Dot &b)
{
	//Construct tthe rectangle sides
	int lA, lB;
	int rA, rB;
	int tA, tB;
	int bA, bB;

	//define edges of A
	lA = a.Collider.x;
	rA = a.Collider.x + a.Collider.w;
	tA = a.Collider.y;
	bA =  a.Collider.y + a.Collider.h;

	//define edges of B
	lB = b.Collider.x;
	rB = b.Collider.x + b.Collider.w;
	tB = b.Collider.y;
	bB =  b.Collider.y + b.Collider.h;

	//checking for bouding boxes collision with the separating axis test(s).
	if (lA >= rB) {return false;}
	if (bA <= tB) {return false;}
	if (rA <= lB) {return false;}
	if (tA >= bB) {return false;}

	//std::cout<< "Collision! You F'd UP!" <<std::endl;
	a.tempup();

	return true;
}

//Updates the window title with vehicle temp and score
/*
void Renderer::UpdateTitle(int &a, int &t)
{
	std::string s = "Vehicle Temperature: "+std::to_string(a)+"F, Score: "+std::to_string(t);
	int n = s.length();

	char *carray[n+1];

	std::strcpy(*carray, s.c_str());

	const char title = &carray;

	SDL_SetWindowTitle(gWindow, title);

	return;
}
*/

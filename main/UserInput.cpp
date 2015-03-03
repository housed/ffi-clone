#include "UserInput.h"

SDL_Event event;

bool UserInput::keydown(int k)
{
	if( SDL_PollEvent( &event ) )
	{
		if( event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == k) return true;
		}
	}
	return false;
}
bool UserInput::keyup(int k)
{
	if( SDL_PollEvent( &event ) )
	{
		if( event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == k) return true;
		}
	}
	return false;
}
int UserInput::keyPress()
{
	if( SDL_PollEvent( &event ) )
	{
		if( event.type == SDL_KEYUP)
		{
			return event.key.keysym.sym;
		}
	}
}
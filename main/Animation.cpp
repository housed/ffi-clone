#include "Animation.h"

Animation::Animation(int f, int w, int fr, Entity *e)
{
	maxFrames = f;
	frameWidth = w;
	frameRate = fr;

	entity = e;
	entity->srcRect.w = frameWidth;
	currentFrame = 0;
	oldTime = SDL_GetTicks();
}
void Animation::doAnimation(SDL_Surface *screen, SDL_Rect p)
{
	if(oldTime + frameRate <= (int)SDL_GetTicks())
	{
		oldTime = SDL_GetTicks();
        currentFrame ++;
    }
	
	if (currentFrame >= maxFrames)
	{
		currentFrame = 0;
	}

	entity->srcRect.x = currentFrame*frameWidth;
	entity->srcRect.y = 0;

	SDL_BlitSurface( entity->surface, &entity->srcRect, screen, &p );
}
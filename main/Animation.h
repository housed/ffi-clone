#pragma once

#include "Entity.h"
#include <string>

class Animation
{
private:
	int currentFrame;
	long oldTime;

public:
	int maxFrames;
	int frameWidth;
	int frameRate;
	Entity *entity;

	Animation::Animation(int f, int w, int fr, Entity *e);
	void Animation::doAnimation(SDL_Surface *screen, SDL_Rect p);
};
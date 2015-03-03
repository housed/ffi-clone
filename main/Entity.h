#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Entity
{
public:
	SDL_Surface * surface;
	SDL_Rect rect;
	SDL_Rect srcRect;
	int w;
	int h;
	int inx;
	int iny;

	Entity::Entity();
	Entity::Entity(char * resourcePath);
	void Entity::SetSurfaceImage(char * resourcePath);
};
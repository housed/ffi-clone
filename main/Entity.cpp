#include "Entity.h"

Entity::Entity()
{
	surface = NULL;
}
Entity::Entity(char * resourcePath)
{
	surface = IMG_Load(resourcePath);
}

void Entity::SetSurfaceImage(char * resourcePath)
{
	surface = IMG_Load(resourcePath);
}
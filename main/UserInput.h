#pragma once

#include "SDL.h"
#include <string>
#include <vector>

class UserInput
{
public:
	
	bool UserInput::keydown(int k);
	bool UserInput::keyup(int k);
	int UserInput::keyPress();
};
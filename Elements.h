#pragma once
#include"Imager.h"

class Elements {
private:
	SDL_Rect elePos;
	SDL_Texture* ele;
	int eleX;
	int eleY;
	int eleW;
	int eleH;
	
public:
	Elements();


	void makeCopy();
};
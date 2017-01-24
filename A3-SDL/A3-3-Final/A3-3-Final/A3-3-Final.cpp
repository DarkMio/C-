// A3-3-Final.cpp : Defines the entry point for the console application.
//

#include "Drawable.h"
#undef main


int main()
{
	/*
	{
		SDL_Wrap::Surface y(10, 10);
		SDL_Wrap::Surface z(20, 20);
		z.blit(y, GUI::Rectangle(10, 10, 0, 0));
	}
	*/
	{
		GUI::Layout x;
		x.push_back(GUI::PixelSpace(10, 10, 0xFFFFFFFF));
		x.push_back(GUI::PixelSpace(25, 25, 0xFFFFFFFF));
		auto y = GUI::preferredSize(x);
		std::cout << "prefSize [" << std::get<0>(y) << "," << std::get<1>(y) << "]" << std::endl;
	}

	return 0;
}


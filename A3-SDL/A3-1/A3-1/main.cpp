#include <SDL.h>
#include <iostream>
#include "ApplicationWindow.h"

using namespace std;

#undef main

int main()
{
   
   try
   {
      SDL_Init(SDL_INIT_VIDEO );
	  ApplicationWindow window = ApplicationWindow();
	  window.run();
	  window.~ApplicationWindow();
      SDL_Quit();
   }

   catch ( std::runtime_error const& e )
   {
      std::cerr << "Caught exception: " << e.what() << std::endl;
   }
   catch (std::exception const& e) {
	   std::cerr << "Caught exception: " << e.what() << std::endl;
   }
}

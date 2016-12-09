

#include <SDL2/sdl.h>
#include <iostream>

using namespace std;

#undef main

int main()
{
   
   try
   {
      SDL_Init(SDL_INIT_VIDEO );
      cout << "Welcome to SDL World...." << endl;
      SDL_Quit();
   }

   catch ( std::runtime_error const& e )
   {
      std::cerr << "Caught exception: " << e.what() << std::endl;
   }
}

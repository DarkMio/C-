#include "Window.h"
#include "LayoutManager.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "AppComposite.h"
#undef main


int main() {
	AppComposite x;

	int i = 3000; // 3 seconds
	while (x.draw()) {
		// std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	/*
	SDL_Wrap::Window x(640, 480, "Twerkbot");
	GUI::HorizontalLayout mgr();
	*/
	std::cout << "Somehow it didn't crash yet." << std::endl;
	return 0;
}
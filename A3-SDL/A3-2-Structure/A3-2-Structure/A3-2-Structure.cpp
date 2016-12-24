#include "Window.h"
#include "LayoutManager.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "AppComposite.h"
#undef main


int main() {
	AppComposite x;

	int i = 30; // 3 seconds
	while (i-- > 0) {
		x.draw(); // gtfo - circumventing hacked CTORs.
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	/*
	SDL_Wrap::Window x(640, 480, "Twerkbot");
	GUI::HorizontalLayout mgr();
	*/
	std::cout << "Somehow it didn't crash yet." << std::endl;
	return 0;
}
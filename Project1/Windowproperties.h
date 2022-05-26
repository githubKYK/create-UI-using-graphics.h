#pragma once
#include "graphics.h"
#include "Mymath.h"

namespace MWD {
	const int WINDOW_COLOR = WHITE;

	const int WIDTH = percent(GetSystemMetrics(SM_CXSCREEN), 90);
	const int HEIGHT = percent(GetSystemMetrics(SM_CYSCREEN), 93);

	const int FONT1 = BOLD_FONT;
	const int FONT2 = COMPLEX_FONT;

	void clearScreen() {
		setbkcolor(WINDOW_COLOR);
		bar(0, 0, WIDTH, HEIGHT);
	}

	void initWindow(char* content) {
		initwindow(WIDTH, HEIGHT, content);
		clearScreen();
	}
}
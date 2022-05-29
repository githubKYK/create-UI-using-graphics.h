#pragma once
#include "Windowproperties.h"

void preIcon(const int& x, const int& y, const int& width, const int& color = BLACK, const int& bgColor = WHITE) {
	int r = x + width;
	int b = y + width;
	setfillstyle(SOLID_FILL, bgColor);
	bar(x, y, r, b);
	setcolor(color);
	setlinestyle(SOLID_LINE, SOLID_FILL, 2);

	int y3 = y + width / 2;

	line(r, y, x, y3);
	line(r, b, x, y3);

	rectangle(x, y, x + width, y + width);

}

void nextIcon(const int& x, const int& y, const int& width, const int& color = BLACK, const int& bgColor = WHITE) {
	int r = x + width;
	int b = y + width;
	setfillstyle(SOLID_FILL, bgColor);
	bar(x, y, r, b);
	setcolor(color);
	setlinestyle(SOLID_LINE, SOLID_FILL, 2);

	int y3 = y + width / 2;

	line(x, y,r, y3);
	line(x, b, r, y3);

	rectangle(x, y, x + width, y + width);

}

void textIcon(const int&x, const int& y, const int& width, char* text, const int& color = BLACK, const int& bgColor = WHITE) {
	int r = x + width;
	int b = y + width;
	setfillstyle(SOLID_FILL, bgColor);
	bar(x, y, r, b);
	setcolor(color);
	setbkcolor(bgColor);
	setlinestyle(SOLID_LINE, SOLID_FILL, 2);
	rectangle(x, y, x + width, y + width);

	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	settextstyle(MWD::FONT1, LEFT_RIGHT, 1);

	int w = width / 2;

	moveto(x + w, y + w + 2);
	settextstyle(MWD::FONT2, LEFT_TEXT, 1);
	outtext(text);

}
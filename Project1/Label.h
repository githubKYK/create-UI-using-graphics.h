#pragma once
#include "RootUI.h"

class Label :public RootUI {
public:
	Label();
	Label(const int&, const int&, const int&, const int&, char*);

	void setText(char*);
	void display();

private:
	char text[20];
	int textLen;
};

Label::Label():RootUI() {
	setText(const_cast<char*>("Label"));
}

Label::Label(const int& sX, const int& sY, const int& sW, const int& sH, char* sT):RootUI(sX, sY, sW, sH) {
	setText(sT);
}

void Label::setText(char* sT){
	strcpy_s(text, sT);
	textLen = 0;
	while(text[textLen++]){}
}

void Label::display() {
	drawBackground(x, y, xr, yb, normalBackgroundColor, SOLID_FILL);
	textProperties(normalTextColor, normalBackgroundColor, MWD::FONT2, LEFT_RIGHT, 1, CENTER_TEXT, VCENTER_TEXT);
	writeText(text, textLen, 0, x, y, width, height, CENTER_TEXT);
	drawBorder(x, y, xr, yb, normalBorderColor, borderSize);
}
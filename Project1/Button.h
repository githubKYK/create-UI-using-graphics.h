#pragma once
#include "RootUI.h"

class Button :public RootUI {
public:
	Button();
	Button(const int&, const int&, const int&, const int&, char*);

	void display(const int&, const int&, char*, int);
	void waitEvent(const int&, const int&, bool&);
	
	void setText(char*);

private:
	int displayStatus = NORMAL;
	char text[50];
	int textLen;
};

Button::Button():RootUI() {
	setText(const_cast<char*>("Button"));
}

Button::Button(const int& sX, const int& sY, const int& sW, const int& sH, char* sT):RootUI(sX, sY, sW, sH) {
	setText(sT);
}

void Button::setText(char* sT) {
	strcpy(text, sT);
	textLen = 0;
	while(text[textLen++]){}
}

void Button::display(const int& mode, const int& textMode = 0, char* textWrite = 0, int len = 0) {
	textWrite = textWrite ? textWrite : text;
	len = (len > 0) ? len : textLen;
	if (mode == NORMAL) {
		drawBackground(x, y, xr, yb, normalBackgroundColor, SOLID_FILL);
		textProperties(normalTextColor, normalBackgroundColor, MWD::FONT2, LEFT_RIGHT, 1, CENTER_TEXT, VCENTER_TEXT);
		writeText(textWrite, len, textMode, x, y, width, height, CENTER_TEXT);
		drawBorder(x, y, xr, yb, normalBorderColor, borderSize);
	}
	else if (mode == ACTIVE) {
		drawBackground(x, y, xr, yb, activeBackgroundColor, SOLID_FILL);
		textProperties(activeTextColor, activeBackgroundColor, MWD::FONT2, LEFT_RIGHT, 1, CENTER_TEXT, VCENTER_TEXT);
		writeText(textWrite, len, textMode, x, y, width, height, CENTER_TEXT);
		drawBorder(x, y, xr, yb, activeBorderColor, borderSize);
	}
}

void Button::waitEvent(const int& mouseX, const int& mouseY, bool& isClick) {
	if (displayStatus == NORMAL && mouseIn()) {
		display(ACTIVE);
		displayStatus = ACTIVE;
	}
	else if(displayStatus == ACTIVE && !mouseIn()) {
		display(NORMAL);
		displayStatus = NORMAL;
	}

	if (mouseClick()) {
		isClick = 1;
	}
	else {
		isClick = 0;
	}
}
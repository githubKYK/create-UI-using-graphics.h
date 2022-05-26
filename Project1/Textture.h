#pragma once
#include "RootUI.h"

class Textture : public RootUI {
public:
	Textture();
	Textture(const int&, const int&, const int&, const int&, char*);

	void setdefault();
	void display(const int&, const int&, char*, int);
	bool mouseIn(const int&, const int&);
	void enterText();
	void waitEvent();

	void setX(const int&);
	void setY(const int&);
	void setWidth(const int&);
	void setHeight(const int&);

	int normalTextColor, normalBackgroundColor, normalBorderColor;
	int activeTextColor, activeBackgroundColor, activeBorderColor;
	int borderSize;
	int textFont;
	char text[50];
	int textLen;

private:
	
};

Textture::Textture():RootUI() {

	setdefault();

	strcpy_s(text, const_cast<char*>("Button"));

	textLen = 6;
}

Textture::Textture(const int& setX, const int& setY, const int& setWidth, const int& setHeight, char* setText):RootUI(setX, setY, setWidth, setHeight) {

	setdefault();

	strcpy_s(text, setText);

	textLen = 0;

	while(text[textLen++]){}

}

void Textture::setX(const int& setx) {
	x = setx;
	xr = x + width;
}

void Textture::setY(const int& sety) {
	y = sety;
	yb = y + height;
}

void Textture::setWidth(const int& setwidth) {
	width = setwidth;
	xr = x + width;
}

void Textture::setHeight(const int& setheight) {
	height = setheight;
	yb = y + height;
}

void Textture::setdefault() {
	normalTextColor = WHITE;
	normalBackgroundColor = DARKGRAY;
	normalBorderColor = WHITE;

	activeTextColor = BLACK;
	activeBackgroundColor = LIGHTGRAY;
	activeBorderColor = BLUE;

	borderSize = 2;
	textFont = SANS_SERIF_FONT;
}

void Textture::display(const int& mode, const int& modeText, char* displayText = 0, int len = -1) {
	displayText = (displayText != 0) ? displayText : text;
	len = (len > 0) ? len : textLen;
	if (mode == NORMAL) {
		drawBackground(x, y, xr, yb, normalBackgroundColor, SOLID_FILL);
		textProperties(normalTextColor, normalBackgroundColor, MWD::FONT2, LEFT_RIGHT, 1, LEFT_TEXT, VCENTER_TEXT);
		writeText(displayText, len, modeText, x, y, width, height, LEFT_TEXT);
		drawBorder(x, y, xr, yb, normalBorderColor, borderSize);
	}
	else if (mode == ACTIVE) {
		drawBackground(x, y, xr, yb, activeBackgroundColor, SOLID_FILL);
		textProperties(activeTextColor, activeBackgroundColor, MWD::FONT2, LEFT_RIGHT, 1, LEFT_TEXT, VCENTER_TEXT);
		writeText(displayText, len, modeText, x, y, width, height, LEFT_TEXT);
		drawBorder(x, y, xr, yb, activeBorderColor, borderSize);
	}
}

bool Textture::mouseIn(const int& mx, const int& my) {
	return mx >= x && mx <= xr && my >= y && my <= yb;
}

void Textture::enterText() {
	display(ACTIVE, BACK);
	char temp[100];
	strcpy_s(temp, text);
	int tempLen = textLen;
	char c = 0;

	while (kbhit())
	{
		getch();
	}
	
	while (true) {
		if (kbhit()) {
			delay(1);
			c = getch();
			if (c == 13 || c == 27) {
				strcpy_s(text, temp);
				textLen = tempLen;
				display(NORMAL, FRONT);
				break;
			}
			else if (c == 8) {
				if (tempLen >= 2) {
					temp[tempLen - 2] = 0;
					tempLen--;
					display(ACTIVE, BACK, temp, tempLen);
				}
			}
			else if (c != 0) {
				temp[tempLen - 1] = c;
				temp[tempLen] = 0;
				tempLen++;
				display(ACTIVE, BACK, temp, tempLen);
			}
		}
		delay(1);
		//display(mode:quyet dinh mau chu, modeText, quyet dinh cach in ra chu, displayText: chu se duoc in ra, textLen: chieu dai cua chu)
	}
}

void Textture::waitEvent() {
	if (ismouseclick(0x0201)) {
		int mx = mousex();
		int my = mousey();
		if (mouseIn(mx, my)) {
			clearmouseclick(0x0201);
			enterText();
		}
	}
	
}

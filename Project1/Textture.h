#pragma once
#include "RootUI.h"

class Textture : public RootUI {
public:
	Textture();
	Textture(const int&, const int&, const int&, const int&, char*);

	void display(const int&, const int&, char*, int);
	void enterText();
	void waitEvent(const int&, const int&);

	void setText(char*);
	char* getText();

private:
	char text[500];
	int textLen;
};

Textture::Textture():RootUI() {
	setText(const_cast<char*>("Textture"));
}

Textture::Textture(const int& sX, const int& sY, const int& sW, const int& sH, char* sT):RootUI(sX, sY, sW, sH) {
	setText(sT);
}

void Textture::setText(char* sT) {
	strcpy_s(text, sT);
	textLen = 0;
	while (text[textLen++]) {}
}

char* Textture::getText() {
	return text;
}

void Textture::display(const int& mode, const int& textMode, char* textWrite = 0, int len = -1) {
	textWrite = (textWrite != 0) ? textWrite : text;
	len = (len > 0) ? len : textLen;
	if (mode == NORMAL) {
		drawBackground(x, y, xr, yb, normalBackgroundColor, SOLID_FILL);
		textProperties(normalTextColor, normalBackgroundColor, MWD::FONT2, LEFT_RIGHT, 1, LEFT_TEXT, VCENTER_TEXT);
		writeText(textWrite, len, textMode, x, y, width, height, LEFT_TEXT);
		drawBorder(x, y, xr, yb, normalBorderColor, borderSize);
	}
	else if (mode == ACTIVE) {
		drawBackground(x, y, xr, yb, activeBackgroundColor, SOLID_FILL);
		textProperties(activeTextColor, activeBackgroundColor, MWD::FONT2, LEFT_RIGHT, 1, LEFT_TEXT, VCENTER_TEXT);
		writeText(textWrite, len, textMode, x, y, width, height, LEFT_TEXT);
		drawBorder(x, y, xr, yb, activeBorderColor, borderSize);
	}
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

void Textture::waitEvent(const int& mouseX = 0, const int& mouseY = 0) {
	if (ismouseclick(0x0201)) {
		if (mouseIn()) {
			clearmouseclick(0x0201);
			enterText();
		}
	}
	
}

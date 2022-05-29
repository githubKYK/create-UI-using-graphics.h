#pragma once
#include <cstring>
#include "graphics.h"
#include "Windowproperties.h"

enum modeWriteText {
	FRONT,
	BACK
};

enum modeDisplay {
	NORMAL,
	HOVER,
	ACTIVE
};

class RootUI {
public:

	RootUI();
	RootUI(const int&, const int&, const int&, const int&);

	void textProperties(const int&, const int&, const int&, const int&, const int&, const int&, const int&);

	void writeText(char*, const int&, const int&, const int&, const int&, const int&, const int&, const int&);

	void enterText(char*, const int&);

	void drawBackground(const int&, const int&, const int&, const int&, const int&, const int&);

	void drawBorder(const int&, const int&, const int&, const int&, const int&, const int&);

	void setDefault();

	bool containPoint2(const int&, const int&);
	bool mouseIn();
	bool mouseClick();

	void setX(const int&);
	void setY(const int&);
	void setWidth(const int&);
	void setHeight(const int&);
	void setTextSize(const int&);
	void setTextFont(const int&);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getRight();
	int getBottom();
	int getTextSize();
	int getTextFont();

	int normalTextColor, normalBackgroundColor, normalBorderColor;
	int activeTextColor, activeBackgroundColor, activeBorderColor;
	int borderSize;
	int textFont;
	int textSize;

protected:

	int textDistanceTop = 4;
	int x, y, width, height, xr, yb;

};

RootUI::RootUI() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	xr = 0;
	yb = 0;
	
	setDefault();

}

RootUI::RootUI(const int& setX, const int& setY, const int& setWidth, const int& setHeight) {
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	xr = x + width;
	yb = y + height;

	setDefault();
}

void RootUI::setDefault() {
	normalTextColor = BLACK;
	normalBackgroundColor = LIGHTGRAY;
	normalBorderColor = BLACK;

	activeTextColor = BLACK;
	activeBackgroundColor = LIGHTGRAY;
	activeBorderColor = BLUE;

	borderSize = 2;
	textFont = SANS_SERIF_FONT;
	textSize = 1;
}

bool RootUI::containPoint2(const int& pointX, const int& pointY) {
	return pointX >= x && pointX <= xr && pointY >= y && pointY <= yb;
}

bool RootUI::mouseIn() {
	int mx = mousex();
	int my = mousey();
	return containPoint2(mx, my);
}

bool RootUI::mouseClick() {
	if (ismouseclick(0x0201)) {
		return mouseIn();
	}
	return 0;
}

void RootUI::setX(const int& setx) {
	x = setx;
	xr = x + width;
}

void RootUI::setY(const int& sety) {
	y = sety;
	yb = y + height;
}

void RootUI::setWidth(const int& setwidth) {
	width = setwidth;
	xr = x + width;
}

void RootUI::setHeight(const int& setheight) {
	height = setheight;
	yb = y + height;
}

void RootUI::setTextSize(const int& setTextSize) {
	textSize = setTextSize;
}

void RootUI::setTextFont(const int& setTextFont) {
	textFont = setTextFont;
}

int RootUI::getX() {
	return x;
}

int RootUI::getY() {
	return y;
}

int RootUI::getWidth() {
	return width;
}

int RootUI::getHeight() {
	return height;
}

int RootUI::getRight() {
	return xr;
}

int RootUI::getBottom() {
	return yb;
}

int RootUI::getTextSize() {
	return textSize;
}

int RootUI::getTextFont() {
	return textFont;
}

void RootUI::textProperties(const int& color, const int& backgroudColor, const int& font,const int& derection, const int& size, const int& horiz, const int& vertical) {
	settextjustify(horiz, vertical);
	settextstyle(font, derection, size);
	setcolor(color);
	setbkcolor(backgroudColor);
}

void RootUI::writeText(char* text, const int& textLen, const int& mode, const int& x, const int& y ,const int& width, const int& height, const int& horiz) {

	int charWidth = textwidth(const_cast<char*>("aA0 .")) / 5;
	int textWith = textwidth(text);
	int charLimit = width / charWidth - 1;

	/*cout << "with: " << widthLimit << '|' << "char width: " << charWidth << "text width: " << textWith << "|" << "max char: " << charLimit << '\n';*/

	if (textLen >= charLimit) {

		char textTemp[50] = { "" };

		if (mode == FRONT) {
			int i = 0;
			charLimit = charLimit > 0 ? charLimit : 1;
			charLimit -= 3;
			while (i < charLimit) {
				textTemp[i] = text[i];
				i++;
			}
			strcat_s(textTemp, i + 4, "...");
			charLimit += 3;
		}
		else if (mode == BACK) {
			charLimit = charLimit > 0 ? charLimit : 1;

			int idx = textLen - 1;
			int jdx = charLimit;

			for (size_t i = 0; i <= charLimit; i++) {
				textTemp[jdx--] = text[idx--];
			}

			strcat_s(textTemp, charLimit + 2, "_");
		}

		if (horiz == CENTER_TEXT) {
			moveto(x + width / 2, y + height / 2 + textDistanceTop);
		}
		else {
			moveto(x + 1, y + height / 2 + textDistanceTop);
		}

		outtext(textTemp);

	}
	else {
		if (horiz == CENTER_TEXT) {
			moveto(x + width / 2, y + height / 2 + textDistanceTop);
		}
		else {
			moveto(x, y + height / 2 + textDistanceTop);
		}

		if (mode == FRONT) {
			outtext(text);
		}
		else if (mode == BACK) {
			strcat_s(text, textLen + 1, "_");
			outtext(text);
		}
	}
}

void RootUI::enterText(char* text, const int& len) {

}

void RootUI::drawBackground(const int& left, const int& top, const int& right, const int& bottom, const int& color, const int& pattern) {
	setfillstyle(pattern, color);
	bar(left, top, right, bottom);
}

void RootUI::drawBorder(const int& left, const int& top, const int& right, const int& bottom, const int& color, const int& thickness){
	setlinestyle(SOLID_LINE, 0, thickness);
	setcolor(color);
	rectangle(left, top, right, bottom);
}
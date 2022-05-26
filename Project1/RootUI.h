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
}

RootUI::RootUI(const int& setX, const int& setY, const int& setWidth, const int& setHeight) {
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	xr = x + width;
	yb = y + height;
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
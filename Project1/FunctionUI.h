#pragma once

#include "graphics.h"
#include "Windowproperties.h"
#include <iostream>

enum ls {
	FRONT,
	BACK
};

int textDistanceTop = 4;

void textProperties(const int& color, const int& backgroudColor, const int& font, const int& derection, const int& size, const int& horiz, const int& vertical) {
	settextjustify(horiz, vertical);
	settextstyle(font, derection, size);
	setcolor(color);
	setbkcolor(backgroudColor);
}

void writeText(char* text, const int& textLen, const int& mode, const int& x, const int& y, const int& width, const int& height, const int& horiz) {

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

			//strcat_s(textTemp, charLimit + 2, "_");
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

void drawBackground(const int& left, const int& top, const int& right, const int& bottom, const int& color, const int& pattern) {
	setfillstyle(pattern, color);
	bar(left, top, right, bottom);
}

void drawBorder(const int& left, const int& top, const int& right, const int& bottom, const int& color, const int& thickness) {
	setlinestyle(SOLID_LINE, 0, thickness);
	setcolor(color);
	rectangle(left - 1, top - 1, right, bottom);
}
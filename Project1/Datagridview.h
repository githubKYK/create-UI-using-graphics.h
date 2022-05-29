#pragma once
#include "RootUI.h"
#include "Stringextern.h"
#include "Icon.h"
#include "Point.h"

using std::string;

#define MOUSE_IN_COL_NAME_ROW -1
#define MOUSE_IN_CAPTION_ROW -2
#define MOUSE_IN_PAGE_ROW -3
#define MOUSE_NOT_IN_DATAGRID -4

class Datagridview:public RootUI {
public:
	Datagridview();
	Datagridview(const int&, const int&, const int&, const int&, char*);

	void setCaption(const string&);
	void setCol(const string&, const string&, const string&);
	void addCol(const string&);
	void removeCol(const string&);
	void setColWidth(const string&, const string&);
	void updateColX();

	void setData(Array<string> &);
	void updatePageNum();
	void data_grid_view_setDefault();

	int mouseInRow();
	int mouseInCol();
	int indexData(const int&, const int&);
	string getData(const int&, const int&);
	int getRowY(const int&);

	void drawPageBar();
	void drawRim();
	void drawCaption();
	void drawColName();
	void drawData();
	void drawRowRim(const int&);
	void rowMode(const int&, const int&);
	void selectRow(const int&);
	void display();

	void waitEvent();

	void enterText(const int&, const int&);

private:
	int rowHeight = 50,
		numRow = 0;

	int crPage = 2,
		stInPageBar = 1,
		stXPageBar = 0,
		yPageBar = 0,
		numPage = 100;

	int bookmarkWidth = 26;

	char caption[50];
	int captionLen = 0;

	int rowActive = -1;
	bool isSelect = false;

	Array<string> col;
	Array<bool> colWMode;
	Array<int> colW;
	Array<int> colX;
	Array<string>* data;

	void setColWidthMode(const string&);

};

Datagridview::Datagridview() :RootUI() {
	data_grid_view_setDefault();
	setCaption("Caption");
}

Datagridview::Datagridview(const int& sX, const int& sY, const int& sW, const int& sH, char* setCap):RootUI(sX, sY, sW, sH){
	setCaption(setCap);
	int i = height / rowHeight;
	height = rowHeight * i;
	numRow = i - 3;

	yb = y + height;

	stXPageBar = x + ((width - bookmarkWidth * 12) >> 1);
	yPageBar = yb - (rowHeight - bookmarkWidth) / 2 - bookmarkWidth;

	activeBackgroundColor = RED;

}

void Datagridview::data_grid_view_setDefault() {
	rowHeight = 30;
	numRow = height / rowHeight - 2;
	textSize = 1;
}

#pragma region data and main logic
void Datagridview::setCaption(const string& setCap) {
	strcpy_s(caption, setCap.c_str());
	captionLen = 0;
	while (caption[captionLen++]) {}
}

void Datagridview::setCol(const string& setC, const string& sw, const string& swm) {
	split(col, setC, ',');
	setColWidth(sw,	swm);
	updateColX();
}

void Datagridview::addCol(const string& colN) {
	col.addElement(colN);
}

void Datagridview::removeCol(const string& colN) {
	col.deleteElement(colN);
}

void Datagridview::setColWidth(const string& set, const string& mode) {
	setColWidthMode(mode);
	colW.clear();
	Array<string> temp;
	split(temp, set, ',');
	for (size_t i = 0; i < colWMode.getSize(); i++)
	{
		int vl = atoi(temp.getElement(i).c_str());
		if (colWMode.getElement(i)) {
			vl = percent(width, vl);
		}
		colW.addElement(vl);
	}
}

void Datagridview::setColWidthMode(const string& set) {
	colWMode.clear();
	Array<string> temp;
	split(temp, set, ',');
	for (size_t i = 0; i < temp.getSize(); i++)
	{
		colWMode.addElement(atoi(temp.getElement(i).c_str()));
	}
}

void Datagridview::updateColX() {
	int tX = x;
	colX.clear();
	colX.addElement(tX);
	int cs = col.getSize();
	for (size_t i = 0; i < cs - 1; i++)
	{
		tX += colW.getElement(i);
		colX.addElement(tX);
	}
}

void Datagridview::setData(Array<string>& myData) {
	data = &myData;
	updatePageNum();
}

void Datagridview::updatePageNum() {
	int s = data->getSize();
	numPage = s / numRow ;
	if (s > numPage * numRow)
		numPage++;
}

int Datagridview::mouseInRow() {
	int mx = mousex();
	int my = mousey();

	mx -= x;
	my -= y;

	if (mx < 0 || mx > width || my < 0 || my > height)
		return MOUSE_NOT_IN_DATAGRID;

	int i = my / rowHeight;

	if (i == 0)
		return MOUSE_IN_CAPTION_ROW;
	else if (i == 1)
		return MOUSE_IN_COL_NAME_ROW;
	else if (i > numRow + 2)
		return MOUSE_IN_PAGE_ROW;
	else
		return i - 2;
}

int Datagridview::mouseInCol() {
	int mx = mousex();
	int my = mousey();

	mx -= x;
	my -= y;

	if (mx < 0 || mx > width || my < 0 || my > height)
		return MOUSE_NOT_IN_DATAGRID;

	int nx = 0;

	for (size_t i = 0; i < colW.getSize(); i++)
	{
		int w = colW.getElement(i);
		if (mx > nx && mx < nx + w)
			return i;
		nx += w;
	}

}

int Datagridview::indexData(const int& irow, const int& icol) {
	return irow * col.getSize() + icol;
}

string Datagridview::getData(const int& r, const int& c) {
	return data->getElement(indexData(r, c));
}

int Datagridview::getRowY(const int& sr) {
	return y + (2 + sr) * rowHeight;
}

#pragma endregion

#pragma region logic edit
void Datagridview::enterText(const int& irow, const int& icol) {

}
#pragma endregion

#pragma region draw
void Datagridview::drawPageBar() {

	int x = stXPageBar;

	preIcon(x, yPageBar, bookmarkWidth, normalTextColor, normalBackgroundColor);

	x += bookmarkWidth;

	if (crPage > 9)
		stInPageBar = crPage - 9;
	else
		stInPageBar = 1;

	int max = stInPageBar + 10;
	int crx = 0;
	char crt[4];

	for (size_t i = stInPageBar; i <= max; i++)
	{
		char t[4];
		t[0] = 0;
		_itoa_s(i, t, 10);
		if (i == crPage) {
			crx = x;
			strcpy_s(crt, t);
		}
		else
			textIcon(x, yPageBar, bookmarkWidth, t, normalTextColor, normalBackgroundColor);
		x += bookmarkWidth;
	}

	nextIcon(x, yPageBar, bookmarkWidth, normalTextColor, normalBackgroundColor);

	textIcon(crx, yPageBar, bookmarkWidth, crt, WHITE, BLACK);

}

void Datagridview::drawRim() {
	setlinestyle(SOLID_LINE, SOLID_FILL, borderSize);
	setcolor(normalBorderColor);

	rectangle(x, y, xr, yb);

	int tY = y + rowHeight;

	for (int i = -2; i < numRow; i++)
	{
		line(x, tY, xr, tY);
		tY += rowHeight;
	}

	int tX = x;
	tY = y + rowHeight;
	int etY = yb - rowHeight;

	for (int i = 1; i < colW.getSize(); i++)
	{
		tX += colW.getElement(i - 1);
		line(tX, tY, tX, etY);
	}

}

void Datagridview::drawCaption() {
	textProperties(normalTextColor, normalBackgroundColor, MWD::FONT1, LEFT_RIGHT, 1, CENTER_TEXT, VCENTER_TEXT);
	writeText(caption, captionLen, FRONT, x, y, width, rowHeight, CENTER_TEXT);
}

void Datagridview::drawColName() {
	int tX = x;
	int tY = y + rowHeight;
	textProperties(normalTextColor, normalBackgroundColor, MWD::FONT1, LEFT_RIGHT, 1, CENTER_TEXT, VCENTER_TEXT);
	for (size_t i = 0; i < col.getSize(); i++)
	{
		string temp = col.getElement(i);
		int cw = colW.getElement(i);
		writeText(&temp[0], temp.length() + 1, FRONT, tX, tY, cw, rowHeight, CENTER_TEXT);
		tX += cw;
	}
}

void Datagridview::drawData() {
	/*int size = data->getSize();
	int csize = col.getSize();
	int r = 0;
	int tY = 0;
	string temp;
	textProperties(normalTextColor, normalBackgroundColor, MWD::FONT1, LEFT_RIGHT, 1, LEFT_TEXT, VCENTER_TEXT);
	for (size_t i = 0; i < numRow; i++)
	{
		r = rowOfData(i);
		tY = getRowY(r);
		for (size_t j = 0; j < csize; j++)
		{
			temp = data->getElement(i);
			int rx = colX.getElement(j) + 4;
			writeText(&temp[0], temp.length() + 1, FRONT, rx, tY, colW.getElement(j), rowHeight, LEFT_TEXT);
			i++;
		}
	}*/

	int dtR = (crPage - 1) *numRow;
	int ls = dtR + numRow;
	int csize = col.getSize();
	string temp;
	int tY = y + 2 * rowHeight;
	int dts = data->getSize();

	textProperties(normalTextColor, normalBackgroundColor, MWD::FONT1, LEFT_RIGHT, 1, LEFT_TEXT, VCENTER_TEXT);
	for (size_t i = dtR; i < ls; i++)
	{
		if (i >= dts)
			break;
		for (size_t j = 0; j < csize; j++)
		{
			temp = getData(i, j);
			int rx = colX.getElement(j) + 4;
			writeText(&temp[0], temp.length() + 1, FRONT, rx, tY, colW.getElement(j), rowHeight, LEFT_TEXT);
		}
		tY += rowHeight;
	}

}

void Datagridview::drawRowRim(const int& sY) {
	
	int sX = x;
	int csize = colW.getSize() - 1;
	int bT = sY + rowHeight;

	drawBorder(x, sY, xr, bT, normalBorderColor, borderSize);

	for (size_t i = 0; i < csize; i++)
	{
		sX += colW.getElement(i);
		line(sX, sY, sX, bT);
	}
}

void Datagridview::rowMode(const int& row, const int& mode) {

	int yR = getRowY(row);
	string temp;
	int csize = col.getSize();

	if (row >= 0 && row < numRow) {
		if (mode == NORMAL) {
			drawBackground(x, yR, xr, yR + rowHeight, normalBackgroundColor, SOLID_FILL);
			drawRowRim(yR);
			textProperties(normalTextColor, normalBackgroundColor, MWD::FONT1, LEFT_RIGHT, 1, LEFT_TEXT, VCENTER_TEXT);

		}
		else if (mode == ACTIVE) {
			drawBackground(x, yR, xr, yR + rowHeight, activeBackgroundColor, SOLID_FILL);
			drawRowRim(yR);
			textProperties(activeTextColor, activeBackgroundColor, MWD::FONT1, LEFT_RIGHT, 1, LEFT_TEXT, VCENTER_TEXT);

		}
		for (size_t i = 0; i < csize; i++)
		{
			temp = getData(row, i);
			writeText(&temp[0], temp.length() + 1, FRONT, colX.getElement(i) + 4, yR, colW.getElement(i), rowHeight, LEFT_TEXT);
		}
	}
}

void Datagridview::selectRow(const int&) {
	
}

void Datagridview::display() {
	drawBackground(x, y, xr, yb, normalBackgroundColor, SOLID_FILL);
	drawRim();
	drawCaption();
	drawColName();
	drawPageBar();
	drawData();
}

#pragma endregion

void Datagridview::waitEvent() {
	if (ismouseclick(0x0200)) {
		clearmouseclick(0x0200);
		int r = mouseInRow();
		if (!isSelect) {
			if (r > -1 && r < numRow) {
				if (rowActive != r) {
					if (rowActive > -1) {
						rowMode(rowActive, NORMAL);
					}
					rowActive = r;
					rowMode(rowActive, ACTIVE);
				}
			}
			else {
				if (rowActive != -1) {
					rowMode(rowActive, NORMAL);
					rowActive = -1;
				}
			}
		}
	}
	else if (ismouseclick(0x0201)) {
		clearmouseclick(0x0201);
		if (!mouseIn()) {
			if (isSelect) {
				isSelect = 0;
				rowMode(rowActive, NORMAL);
				rowActive = -1;
			}
		}
		else {
			int r = mouseInRow();
			if (r > -1 && r < numRow) {
				if (isSelect && r == rowActive) {
					isSelect = 0;
					rowMode(rowActive, NORMAL);
					rowActive = -1;
				}
				else {
					if (r != rowActive) {
						rowMode(rowActive, NORMAL);
					}
					rowActive = r;
					rowMode(rowActive, ACTIVE);
					isSelect = 1;
				}
			}
		}
	}

}

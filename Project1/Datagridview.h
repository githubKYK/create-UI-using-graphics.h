#pragma once
#include "RootUI.h"
#include "Stringextern.h"

using std::string;

#define MOUSE_IN_COL_NAME_ROW -1
#define MOUSE_IN_CAPTION_ROW -2
#define MOUSE_NOT_IN_DATAGRID -3

class Datagridview:public RootUI {
public:
	Datagridview();
	Datagridview(const int&, const int&, const int&, const int&, char*);

	void setCaption(const string&);
	void setCol(const string&);
	void addCol(const string&);
	void removeCol(const string&);
	void setColWidth(const string&, const string&);

	void setData(Array<string> &);
	void data_grid_view_setDefault();

	int mouseInRow();
	int mouseInCol();
	int indexData(const int&, const int&);

private:
	int rowHeight,
		numRow = 0;

	int crPage = 1,
		numPage = 0;

	char caption[50];
	int captionLen = 0;

	Array<string> col;
	Array<bool> colWMode;
	Array<int> colW;
	Array<string> data;

	void setColWidthMode(const string&);

};

Datagridview::Datagridview() :RootUI() {
	data_grid_view_setDefault();
	setCaption("Caption");
}

Datagridview::Datagridview(const int& sX, const int& sY, const int& sW, const int& sH, char* setCap):RootUI(sX, sY, sW, sH) {
	setCaption(setCap);
	int i = height / rowHeight;
	height *= i;
}

void Datagridview::data_grid_view_setDefault() {
	rowHeight = 40;
	numRow = height / rowHeight - 2;
	textSize = 1;
}

void Datagridview::setCaption(const string& setCap) {
	strcpy_s(caption, setCap.c_str());
	captionLen = 0;
	while(caption[captionLen++]){}
}

void Datagridview::setCol(const string& setC) {
	col = split(',', setC);
}

void Datagridview::addCol(const string& colN) {
	col.addElement(colN);
}

void Datagridview::removeCol(const string& colN) {
	col.deleteElement(colN);
}

void Datagridview::setColWidth(const string& set, const string& mode) {
	setColWidthMode(mode);

	Array<string> temp = split(',', set);
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
	Array<string> temp = split(',', set);
	for (size_t i = 0; i < temp.getSize(); i++)
	{
		colWMode.addElement(atoi(temp.getElement(i).c_str()));
	}
}

void Datagridview::setData(Array<string> &myData) {
	data = myData;
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
	else
		return i - 2 ;
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


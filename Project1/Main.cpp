//#include "graphics.h"
#include "Textture.h"
#include "Windowproperties.h"
#include "RootUI.h"
#include <iostream>
#pragma comment(lib,"graphics.lib")

int main()
{
    MWD::initWindow(const_cast<char*>("content"));
    Textture a(10,10,100,20,const_cast<char*>("Phung duc manh dep trai vo doi"));
    a.display(0,0);
    while (1) {
        a.waitEvent();
        delay(1);
   }
    getch();
    closegraph();
    return 0;
}
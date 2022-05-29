//#include "graphics.h"
#include "Textture.h"
#include "Windowproperties.h"
#include "RootUI.h"
#include <iostream>
#include "Json.h"
#include "Stringextern.h"
#include "Datagridview.h"
#pragma comment(lib,"graphics.lib")

int main()
{
    MWD::initWindow(const_cast<char*>("content"));
    Datagridview a(10, 10, 600, 400, const_cast<char*>("PDM"));

    a.setCol("stt,ho,ten,diem","20,20,20,20","1,1,1,1");
    
    Array<string> dt;

    for (size_t i = 0; i < 100; i++)
    {
        dt.addElement(to_string(i));
    }

    a.setData(dt);

    a.display();

    while (1)
    {
        a.waitEvent();
    }

    getch();
    closegraph();
    
    return 0;
}
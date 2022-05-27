//#include "graphics.h"
#include "Textture.h"
#include "Windowproperties.h"
#include "RootUI.h"
#include <iostream>
#include "Json.h"
#include "Stringextern.h"
#pragma comment(lib,"graphics.lib")

int main()
{
   // MWD::initWindow(const_cast<char*>("content"));
   // /*Textture a(10,10,100,20,const_cast<char*>("Phung duc manh dep trai vo doi"));
   // a.display(0,0);
   // while (1) {
   //     a.waitEvent();
   //     delay(1);
   //}*/
   // if (ismouseclick(0x0201))
   //     std::cout << "hello word\n";
   // else
   //     std::cout << "hello moon\n";
   // getch();
   // closegraph();

    Array<int> a;

    for (size_t i = 0; i < 11; i++)
    {
        a.addElement(i);
    }

    /*Array<int>* b = &a;

   

    b->deleteElement(2);
    b->deleteElement(3);*/

    for (size_t i = 0; i < a.getSize(); i++)
    {
        cout << a.getElement(i) << '\n';
    }

    cout << "Size: " << a.getSize();
    

    return 0;
}
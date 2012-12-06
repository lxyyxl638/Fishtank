#include <iostream>
#include "platform.h"
#include "fish.h"
#include "st31.h"
#include "st32.h"
#include "st20.h"
#include "st34.h"
using namespace std;

platform plat;
std::ofstream ffout("result");
int main()
{
    ffout << "The Game begins" << endl;
    for (int i=1;i<=10;i++)
      plat.setID(new st32(),"st32");
    for (int i=1;i<=10;i++)
       plat.setID(new st20(),"st20");
    for (int i=1;i<=10;i++)
       plat.setID(new st31(),"st31");
    for (int i=1;i<=10;i++)
       plat.setID(new st34(),"st34");
    plat.start();
    return 0;
}

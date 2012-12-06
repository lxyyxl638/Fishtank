#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED
#include "Windows.h"
#include "platform.h"
#include <iostream>
#include <iomanip>
extern char Name[50];
extern platform plat;
using namespace std;
void gotoxy(int x,int y)
{
    COORD P;
    P.X=x-1;
    P.Y=y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),P);
}
void clear()
{
    cout << ' ';
}
void foodlogo()
{
    cout << '*';
}
void occur(int nowAI,platform & plat)
{
    cout << plat.Name[nowAI];
}
void finish()
{
    for (int i=1;i<=N;i++)
     {
         gotoxy(M+2,i);
         cout << '|';
     }
    gotoxy(M+3,2);
    cout << setw(5) << "Names";
    cout << setw(7) << "Level";
    cout << setw(5) << "HP";
    cout << setw(7) << "MaxHP";
    cout << setw(7) << "Attack";
    cout << setw(5) << "Sp";
  //  cout << setw(7) << "Score";
}
void show(int nowAI,platform & plat)
{
    gotoxy(M+3,nowAI+2);
    cout << setw(5) << plat.Name[nowAI];
    cout << setw(7) << plat.PlayerLevel[nowAI];
    cout << setw(5) << plat.PlayerHP[nowAI];
    cout << setw(7) << plat.PlayerMaxHP[nowAI];
    cout << setw(7) << plat.PlayerAttack[nowAI];
    cout << setw(5) << plat.PlayerSP[nowAI];
   // cout << setw(7) << plat.PlayerScore[nowAI];
}

#endif // OUTPUT_H_INCLUDED

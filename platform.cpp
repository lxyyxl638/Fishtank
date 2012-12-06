#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstring>
#include "platform.h"
#include "output.h"
#include <iomanip>
using namespace std;
extern std::ofstream ffout;
platform::platform()
{
    Deathnum=0;
    playernum=0;
    memset(Bonus,0,sizeof(Bonus));
    memset(Map,0,sizeof(Map));
    memset(PlayerHP,0,sizeof(PlayerHP));
    memset(PlayerMaxHP,0,sizeof(PlayerMaxHP));
    memset(PlayerAttack,0,sizeof(PlayerAttack));
    memset(PlayerSP,0,sizeof(PlayerSP));
    memset(PlayerExp,0,sizeof(PlayerExp));
    memset(PlayerLevel,0,sizeof(PlayerLevel));
    memset(PlayerScore,0,sizeof(PlayerScore));
}

platform::~platform()
{
}

void platform::output()
{
    for (int i=1;i<=playernum;i++)
       order[i]=i;
    for (int i=1;i<=playernum;i++)
     for (int j=i+1;j<=playernum;j++)
      if (PlayerScore[order[i]]<PlayerScore[order[j]]) swap(i,j);
     ffout << "Rank";
     ffout << setw(7) << "ID";
     ffout << setw(7) << "Names";
     ffout << setw(7) << "Level";
     ffout << setw(7) << "Score";
     ffout << setw(7) << "HP";
     ffout << setw(7) << "MAXHP";
     ffout << setw(7) << "ATTACK";
     ffout << setw(7) << "SP" << endl;
    for (int i=1;i<=playernum;i++)
     {
         ffout << setw(4)<< i << setw(7) << order[i];
         ffout << setw(7) << PlayerNames[order[i]];
         ffout << setw(7) << PlayerLevel[order[i]];
         ffout << setw(7) << PlayerScore[order[i]];
         ffout << setw(7) <<PlayerHP[order[i]];
         ffout << setw(7) << PlayerMaxHP[order[i]];
         ffout << setw(7) << PlayerAttack[order[i]];
         ffout << setw(7) << PlayerSP[order[i]];
         ffout << endl;
     }
}
void platform::Upgrade()
{
    while (PlayerExp[nowAI]>=Exp[PlayerLevel[nowAI]+1])
      {
         PlayerLevel[nowAI]++;
         PlayerPoint[nowAI]+=LEVEL_POINT;
         ffout << "AI" << nowAI << " upgrade to " << PlayerLevel[nowAI] << endl;
         ffout << "The Exp is " << PlayerExp[nowAI] << endl;
      }
}
void platform::swap(int i,int j)
{
    int tmp;

         tmp=order[i];
    order[i]=order[j];
    order[j]=tmp;
}
int platform::check(int i,int j)
{
    if (PlayerHP[order[i]]*PlayerMaxHP[order[j]]>PlayerHP[order[j]]*PlayerMaxHP[order[i]]) return 1;
    if (PlayerHP[order[i]]*PlayerMaxHP[order[j]]==PlayerHP[order[j]]*PlayerMaxHP[order[i]]) return 0;
    if (PlayerHP[order[i]]*PlayerMaxHP[order[j]]<PlayerHP[order[j]]*PlayerMaxHP[order[i]]) return -1;
    return 0;
}
void platform::sortHP(int l,int r)
 {
     for (int i=l;i<=r;i++)
      for (int j=i+1;j<=r;j++)
       if (check(i,j)<0) swap(i,j);
 }
void platform::sortscore(int l,int r)
{
    for (int i=l;i<=r;i++)
     for (int j=i+1;j<=r;j++)
      if (PlayerScore[order[i]]>PlayerScore[order[j]]) swap(i,j);
}
void platform::play()
{
    int s;

    for (int i=1;i<=playernum;i++)
          order[i]=i;
    for (int i=1;i<=playernum;i++)
     for (int j=i+1;j<=playernum;j++)
       if (PlayerSP[order[i]]<PlayerSP[order[j]]) swap(i,j);
    s=1;
    for (int i=2;i<=playernum;i++)
      if (PlayerSP[order[i]]!=PlayerSP[order[s]])
         {
            sortHP(s,i-1);
            s=i;
         }
    s=1;
     for (int i=2;i<=playernum;i++)
      if ((PlayerSP[order[i]]!=PlayerSP[order[s]])||(0!=check(i,s)))
         {
             sortscore(s,i-1);
             s=i;
         }
   for (int i=1;i<=playernum;i++)
     if (PlayerHP[order[i]]>0)
      {
          nowAI=order[i];
          Player[nowAI]->play();
          show(order[i],plat);
      };
}
void platform::getlocation(int &x,int &y)
{
    srand(time(NULL));
    x=rand() % N+1;
    y=rand() % M+1;
    while (Map[x][y]!=EMPTY)
      {
         x=rand() % N+1;
         y=rand() % M+1;
      }
}
void platform::refresh()
{
   int x=0,y=0;
   for (int i=1;i<=N;i++)
    for (int j=1;j<=M;j++)
     if (FOOD==Map[i][j]) Map[i][j]=EMPTY;
   for (int i=1;i<=FOOD_ROUND;i++)
    {
        getlocation(x,y);
        Map[x][y]=FOOD;
        gotoxy(x,y);foodlogo();
    }
}
void platform::setID(fish* newfish,string s)
{
    playernum++;
    Player[playernum]=newfish;
    PlayerNames[playernum]=s;
}
void platform::initial()
{
   int x=0,y=0;
   for (int i=1;i<=26;i++)
      Name[i]='A'+i-1;
   for (int i=27;i<=40;i++)
      Name[i]='a'+i-28;
   Exp[1]=1;Exp[2]=2;
   for (int i=3;i<=N*M;i++)
      Exp[i]=Exp[i-1]+i;
    for (int i=1;i<=playernum;i++)
      {
          nowAI=i;
          getlocation(x,y);
          PlayerX[i]=x;
          PlayerY[i]=y;
          PlayerPoint[i]=10;
          PlayerLevel[i]=1;
          Map[x][y]=i;
          gotoxy(x,y);occur(nowAI,plat);
          Player[i]->init();
      }
}
void platform::reviveAI()
{
    for (int i=1;i<=MAX_PLAYER;i++)
     {
         int x=1,y=1;
         if (0==Grave[i])continue;
         if (0==GraveRound[i])
          {
              GraveRound[i]++;
              continue;
          }
         nowAI=Grave[i];
         Player[nowAI]->revive(x,y);
         if (Map[x][y]!=EMPTY) getlocation(x,y);
         PlayerX[nowAI]=x;
         PlayerY[nowAI]=y;
         PlayerHP[nowAI]=max(1,PlayerMaxHP[nowAI]/10);
         Map[x][y]=nowAI;
         Grave[i]=0;
         GraveRound[i]=0;
     }
}
void platform::start()
{
    initial();
    finish();
    for (int i=1;i<=Limit;i++)
     {
         ffout << "Round " << i << endl;
         gotoxy(M+3,1);
         cout << "Round " << i << endl;
         if (1==i%5) refresh();
         reviveAI();
         play();
     }
   gotoxy(N+1,M+1);
   output();
}


bool platform::Checkdistance(int tx,int ty)
{
    if (abs(tx-PlayerX[nowAI])+abs(ty-PlayerY[nowAI])>PlayerSP[nowAI]) return false;
    return true;
}
bool platform::move(int tx,int ty)
   {
       ffout << "AI " << nowAI << " want to go to" << '(' << tx <<',' << ty << ')' << ':';
       if ((tx<1)||(ty<1)||(tx>N)||(ty>M)||(EMPTY!=Map[tx][ty])||(!Checkdistance(tx,ty)))
       {
           ffout << "False" << endl;
          return false;
       }
       Map[tx][ty]=nowAI;
       Map[PlayerX[nowAI]][PlayerY[nowAI]]=EMPTY;
       gotoxy(PlayerX[nowAI],PlayerY[nowAI]);clear();
       gotoxy(tx,ty);occur(nowAI,plat);
       PlayerX[nowAI]=tx;
       PlayerY[nowAI]=ty;
       ffout << "Success" << endl;
       return true;
   }

bool platform::attack(int tx,int ty)
   {
       int target;

       ffout << "AI " << nowAI << " want to attack" << '(' << tx <<',' << ty << ')' << ':' << Map[tx][ty] << endl;
       if ((tx<1)||(ty<1)||(tx>N)||(ty>M)||(0==PlayerAttack[nowAI])||(EMPTY==Map[tx][ty]))
       {
           ffout << "False the location is" << Map[tx][ty] << endl;
           return false;
       }
       if (FOOD==Map[tx][ty])
          {
              Map[tx][ty]=EMPTY;
              gotoxy(tx,ty);clear();
              PlayerExp[nowAI]++;
              PlayerScore[nowAI]++;
              ffout << "AI " << nowAI << " Score is "<< PlayerScore[nowAI] << endl;
              PlayerHP[nowAI]=min(PlayerMaxHP[nowAI],PlayerHP[nowAI]+max(2,PlayerMaxHP[nowAI]/10));
              ffout << "AI " << nowAI << " HP is " << PlayerHP[nowAI] << '/' << PlayerMaxHP[nowAI] << endl;
          }
       else
          {
              target=Map[tx][ty];
              PlayerHP[target]-=PlayerAttack[nowAI];
              ffout << "AI "<< target << " HP is " << PlayerHP[target] << '/' << PlayerMaxHP[target] << endl;
              if (PlayerHP[target]<=0)
                  {
                      PlayerHP[target]=0;
                      Deathnum=Deathnum % MAX_PLAYER +1;
                      ffout << "AI "<<target << " is dead" << endl;
                      Grave[Deathnum]=target;
                      GraveRound[Deathnum]=0;
                      Map[tx][ty]=EMPTY;
                      gotoxy(tx,ty);clear();
                      PlayerExp[nowAI]+=max(1,PlayerLevel[target]/2);
                      Bonus[nowAI]+=max(0,2*(PlayerLevel[target]-PlayerLevel[nowAI]));
                      PlayerScore[nowAI]+=max(1,PlayerLevel[target]/2)+max(0,2*(PlayerLevel[target]-PlayerLevel[nowAI]));
                      ffout << "AI " << nowAI << " Score is "<< PlayerScore[nowAI] << endl;
                      ffout << "AI " << nowAI << " HP is " << PlayerHP[nowAI] << '/' << PlayerMaxHP[nowAI] << endl;
                  }
          }
      Upgrade();
      return true;
   }

int platform::getPoint()
   {
       return PlayerPoint[nowAI];
   }
int platform::getLevel()
   {
       return PlayerLevel[nowAI];
   }
int platform::getExp()
   {
      return PlayerExp[nowAI];
   }
int platform::getX()
   {
      return PlayerX[nowAI];
   }
int platform::getY()
   {
      return PlayerY[nowAI];
   }
int platform::getHP()
   {
      return PlayerHP[nowAI];
   }
int platform::getMaxHP()
   {
      return PlayerMaxHP[nowAI];
   }
int platform::getAtt()
   {
      return PlayerAttack[nowAI];
   }
int platform::getSp()
   {
      return PlayerSP[nowAI];
   }
int platform::getID()
   {
       return nowAI;
   }
int platform::askWhat(int x,int y)
   {
       return Map[x][y];
   }
int platform::askHP(int target)
   {
       return PlayerHP[target];
   }
bool platform::increaseHealth()
   {
       if (PlayerPoint[nowAI]>0)
         {
             PlayerMaxHP[nowAI]+=2;
             PlayerHP[nowAI]+=2;
             PlayerPoint[nowAI]--;
             ffout << "AI " << nowAI << " HP is " << PlayerHP[nowAI] << '/' << PlayerMaxHP[nowAI] << endl;
             return true;
         }
      return false;
   }
bool platform::increaseStrength()
   {
       if (PlayerPoint[nowAI]>0)
         {
             PlayerAttack[nowAI]+=1;
             PlayerPoint[nowAI]--;
             ffout << "AI " << nowAI << " Attack is " << PlayerAttack[nowAI] << endl;
             return true;
         }
       return false;
   }
bool platform::increaseSpeed()
   {
       if (PlayerPoint[nowAI]>0)
        {
            PlayerSP[nowAI]+=1;
            PlayerPoint[nowAI]--;
            ffout << "AI " << nowAI << " Sp is " << PlayerSP[nowAI] << endl;
            return true;
        }
       return false;
   }



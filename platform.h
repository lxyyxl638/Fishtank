#ifndef PLATFORM_H
#define PLATFORM_H

#include <fstream>
#include "fish.h"
#include <cstring>
using namespace std;
extern std::ofstream ffout;
const int Limit=500;
class fish;
class platform
{
    friend void show(int nowAI,platform & plat);
    friend void occur(int nowAI,platform & plat);
    public:
        platform();
        virtual ~platform();
        bool Checkdistance(int,int);
        void output();
        void setID(fish* newfish,string);//create AI
        void start();//Begin the game
        void initial();//init
        void refresh();//refresh algaes
        void reviveAI();//reviveAI
        void play();//play every round
        void getlocation(int &,int &);//find a lawful place
        bool move(int,int);//移动到某个位置
        bool attack(int,int);//攻击某个位置
        int getPoint();//返回当前玩家剩余点数
        int getLevel();//返回当前玩家等级
        int getExp();//返回当前玩家经验
        int getX();//返回当前玩家横坐标
        int getY();//返回当前玩家纵坐标
        int getHP();//返回当前玩家生命值
        int getMaxHP();//返回当前玩家生命上限
        int getAtt();//返回当前玩家攻击力
        int getSp();//返回当前玩家速度
        int getID();//获取玩家ID
        int askWhat(int,int);//返回地图某个位置内容（玩家ID或FOOD或EMPTY）
        int askHP(int);//询问某个玩家ID当前血量
        bool increaseHealth();//增加health属性1
        bool increaseStrength();//增加Strength属性1
        bool increaseSpeed();//增加Speed属性1
        void sortHP(int l,int r);
        void sortscore(int l,int r);
        void Upgrade();
        void swap(int i,int j);
        int check(int i,int j);

    private:
      fish* Player[MAX_PLAYER+1];
      string PlayerNames[MAX_PLAYER+1];
      int Bonus[MAX_PLAYER+1];
      int Exp[N*M];
      int order[MAX_PLAYER+1];
      int Grave[MAX_PLAYER+1];
      int GraveRound[MAX_PLAYER+1];
      int Map[N+1][M+1];
      int PlayerHP[MAX_PLAYER+1];
      int PlayerSP[MAX_PLAYER+1];
      int PlayerMaxHP[MAX_PLAYER+1];
      int PlayerAttack[MAX_PLAYER+1];
      int PlayerExp[MAX_PLAYER+1];
      int PlayerLevel[MAX_PLAYER+1];
      int PlayerPoint[MAX_PLAYER+1];
      int PlayerX[MAX_PLAYER+1],PlayerY[MAX_PLAYER+1];
      int PlayerScore[MAX_PLAYER+1];
      int nowAI,Deathnum;
      int playernum;
      char Name[50];
};

#endif // PLATFORM_H

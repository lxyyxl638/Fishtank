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
        bool move(int,int);//�ƶ���ĳ��λ��
        bool attack(int,int);//����ĳ��λ��
        int getPoint();//���ص�ǰ���ʣ�����
        int getLevel();//���ص�ǰ��ҵȼ�
        int getExp();//���ص�ǰ��Ҿ���
        int getX();//���ص�ǰ��Һ�����
        int getY();//���ص�ǰ���������
        int getHP();//���ص�ǰ�������ֵ
        int getMaxHP();//���ص�ǰ�����������
        int getAtt();//���ص�ǰ��ҹ�����
        int getSp();//���ص�ǰ����ٶ�
        int getID();//��ȡ���ID
        int askWhat(int,int);//���ص�ͼĳ��λ�����ݣ����ID��FOOD��EMPTY��
        int askHP(int);//ѯ��ĳ�����ID��ǰѪ��
        bool increaseHealth();//����health����1
        bool increaseStrength();//����Strength����1
        bool increaseSpeed();//����Speed����1
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

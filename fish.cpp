#include "fish.h"
#include "platform.h"
extern platform plat;
bool fish::move(int tx,int ty)
   {
      return plat.move(tx,ty);
   }

bool fish::attack(int tx,int ty)
   {
       return plat.attack(tx,ty);
   }
int fish::getPoint()
   {
       return plat.getPoint();
   }
int fish::getLevel()
   {
       return plat.getLevel();
   }
int fish::getExp()
   {
      return plat.getExp();
   }
int fish::getX()
   {
      return plat.getX();
   }
int fish::getY()
   {
      return plat.getY();
   }
int fish::getHP()
   {
      return plat.getHP();
   }
int fish::getMaxHP()
   {
      return plat.getMaxHP();
   }
int fish::getAtt()
   {
      return plat.getAtt();
   }
int fish::getSp()
   {
      return plat.getSp();
   }
int fish::getID()
   {
       return plat.getID();
   }
int fish::askWhat(int x,int y)
   {
       return plat.askWhat(x,y);
   }
int fish::askHP(int ID)
   {
       return plat.askHP(ID);
   }
bool fish::increaseHealth()
   {
       return plat.increaseHealth();
   }
bool fish::increaseStrength()
   {
       return plat.increaseStrength();
   }
bool fish::increaseSpeed()
   {
       return plat.increaseSpeed();
   }


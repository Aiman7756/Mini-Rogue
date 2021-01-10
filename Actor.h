
#ifndef Actor_h
#define Actor_h

#include <string>

using namespace std;

class Weapon;

class Actor{
public:
    //getters
    int getHP();
    int getMaxHP();
    int getArmor();
    int getStr();
    int getDex();
    int getRow() const;
    int getCol() const;
    int getSleep();
    Weapon* getWeapon();
    std::string getName();
    
    //setters
    void setMaxHP(int add);
   void setHP(int add);
   void setArmor(int add);
   void setStr(int add);
   void setDex(int add);
    void setSleep(int add);
    
protected:
    Weapon* weapon;
    int max_hp;
    int hp;
    int armor;
    int str;
    int dex;
    int row;
    int col;
    int sleeptime = 0;
    std::string name;
};

#endif

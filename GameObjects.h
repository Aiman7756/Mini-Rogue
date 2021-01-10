
#ifndef GameObjects_h
#define GameObjects_h

#include <string>
#include <iostream>

using namespace std;

class Dungeon;
class Player;

//Base Object class
class Object{
protected:
    int row;
    int col;
    char display;
    string name;
    string retrieve;
public:
    int getRow();
    int getCol();
    char displayIcon();
    string getName();
    string getRetrieve();
    virtual ~Object();
    
};

//Base Stairway class (Derived Object)
class Stairway : public Object{
public:
    Stairway(int r, int c, Dungeon* d);
    virtual ~Stairway();
private:
    Dungeon* m_dungeon;
};

//Base Weapon class (Derived Object)
class Weapon : public Object{
protected:
    string action;
    int dexBonus;
    int dmgBonus;
    Dungeon* m_dungeon;
public:
    int getDexBonus();
    int getDamageBonus();
    string getAction();
    virtual ~Weapon();
    
};

//derived weapon
class Mace : public Weapon{
public:
    Mace();
    Mace(int r, int c, Dungeon* d);
    virtual ~Mace();

};

//derived weapon
class ShortSword : public Weapon{
public:
    ShortSword();
    ShortSword(int r, int c, Dungeon* d);
    virtual ~ShortSword();
    
};

//derived weapon
class LongSword : public Weapon{
public:
    LongSword();
    LongSword(int r, int c, Dungeon* d);
    virtual ~LongSword();
    
};

//derived weapon
class Fang : public Weapon{
public:
    Fang();
    Fang(int r, int c, Dungeon* d);
    virtual ~Fang();
    
};

//derived weapon
class MagicAxe : public Weapon{
public:
    MagicAxe();
    MagicAxe(int r, int c, Dungeon* d);
    virtual ~MagicAxe();
    
};


//Base Scroll class (derived object)
class Scroll : public Object{
    
public:
    virtual void effect(Player* player) = 0;
    virtual ~Scroll();
    string getEffect();
    
protected:
    string aftereffect;
    Dungeon* m_dungeon;
};

//derived scroll
class Teleport : public Scroll{
public:
    Teleport(int r, int c, Dungeon* d);
    void effect(Player* player);
    virtual ~Teleport();
};

//derived scroll
class EnhanceStr : public Scroll{
public:
    EnhanceStr(int r, int c, Dungeon* d);
    void effect(Player* player);
    virtual ~EnhanceStr();
};

//derived scroll
class EnhanceArmor : public Scroll{
public:
    EnhanceArmor(int r, int c, Dungeon* d);
    void effect(Player* player);
    virtual ~EnhanceArmor();
};

//derived scroll
class EnhanceHP : public Scroll{
public:
    EnhanceHP(int r, int c, Dungeon* d);
    void effect(Player* player);
    virtual ~EnhanceHP();
};

//derived scroll
class EnhanceDex : public Scroll{
public:
    EnhanceDex(int r, int c, Dungeon* d);
    void effect(Player* player);
    virtual ~EnhanceDex();
};

//Idol (derived object)
class Idol : public Object{
public:
    Idol(int r, int c, Dungeon* d);
    ~Idol();
private:
    Dungeon* m_dungeon;
};



#endif /* GameObjects_h */

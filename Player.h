
#ifndef Player_h
#define Player_h

#include <vector>

using namespace std;

#include "Actor.h"
#include "GameObjects.h"

class Dungeon;
class Object;
class Weapon;

class Player : public Actor{
    
    
public:
    Player(Dungeon* d, int r, int c);
    ~Player();
    
    //setters
    void setDead();
    void move(int r, int c);
    void cheat();
    void grabItem();
    void wieldWeapon(char item);
    void readScroll(char item);
    
    //getters
    bool isDead() const;
    bool idol() const;
    void displayInventory();
    
private:
    Dungeon* m_dungeon;
    vector<Object*> inventory;
    vector<Object*>::iterator inv;
    int invCount = 1;
    bool   m_dead = false;
    int convertInventory(char input);
    bool idolObtained = false;
    
    


};




#endif /* Player_h */

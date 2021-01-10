

#ifndef Monster_h
#define Monster_h

#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#include "Actor.h"

//Base Monster class and inherited Snakewoman, Goblin, Bogeyman and Dragon classes

class Dungeon;
class Weapon;
class Player;

class Monster : public Actor{
public:
    
    virtual ~Monster();
    virtual void move(Player* player) = 0;
    virtual void drop() = 0;
    char displayIcon();

protected:
    
    char display;
    string action;
    Dungeon* m_dungeon;
    
};

class Snakewoman : public Monster{
    public:
    Snakewoman(Dungeon* d, int r, int c);
    void move(Player* player);
    void drop();
    virtual ~Snakewoman();
private:
    
};

class Goblin : public Monster{
    private:
public:
    Goblin(int r, int c, Dungeon* d);
    virtual ~Goblin();
    void move(Player* player);
    void drop();

    
};

class Dragon : public Monster{
public:
    Dragon(int r, int c, Dungeon* d);
    virtual ~Dragon();
    void move(Player* player);
    void drop();
    
private:
    
};

class Bogeyman : public Monster{
public:
    Bogeyman(int r, int c, Dungeon* d);
    virtual ~Bogeyman();
    void move(Player* player);
    void drop();
    
private:
    
};

#endif /* Monster_h */

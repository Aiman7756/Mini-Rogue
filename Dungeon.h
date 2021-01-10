
#ifndef Dungeon_h
#define Dungeon_h

#include <vector>
#include <string>

using namespace std;

class Player;
class Monster;
class Actor;
class Object;

class Dungeon
{
    private:
    char blankGrid[18][70];
    char displayGrid[18][70];
    int floor = 0;
    Player* m_player;
    vector<Monster*> monsters;
    vector<Monster*>::iterator ptr;
    vector<std::string> results;
    vector<Object*> floorItems;
    vector<Object*>::iterator item;
    struct Room {
        Room(int Cr, int Cc, int w, int h);
        int centerR;
        int centerC;
        int width;
        int height;
        
    };
    
    vector<Room*> rooms;
    bool generateRoom();
    int roomNumber();
    void addRoom();
    void addCorridor(Room* a);
    
public:
    //constructor + destructor
    Dungeon();
    ~Dungeon();
    
    //pointer to player
    Player* player() const;

    //setup for new layout
    bool addPlayer(int r, int c);
    void initializeMap();
    bool addMonster();
    void createDrops();

    //accessor
    int getFloor();
    void display();
    char getCell(int r, int c);
    void findMonster(Actor* attacker, int r, int c);
    Object* findItem(int r, int c);
    
    //mutator
    void moveMonsters(Player* player);
    void combat(Actor* attacker, Actor* defender);
    void addResult(string s);
    void reset();
    void pushItem(Object* item);
    

    
};











#endif /* Dungeon_h */

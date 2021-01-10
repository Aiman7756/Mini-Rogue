#include <iostream>

#include "Dungeon.h"
#include "Player.h"
#include "utilities.h"
#include "Monster.h"
#include "Actor.h"
#include "GameObjects.h"

using namespace std;


Dungeon::Dungeon(){
    m_player = nullptr;
    //fill grids with all walls
    initializeMap();
    //create rooms
    addRoom();
    //for each room, create corridors
    for (int i = 0; i < rooms.size(); i++){
        addCorridor(rooms[i]);
    }
}

Dungeon::~Dungeon(){
    delete m_player;
    
    for (int i = 0; i < monsters.size(); i++){
        delete monsters[i];
    }
    for (int i = 0; i < floorItems.size(); i++){
        delete floorItems[i];
    }
    for (int i = 0; i < rooms.size(); i++){
        delete rooms[i];
    }
}

//fill both display grid and blank grid with walls
void Dungeon::initializeMap(){
    int r, c;
    
    for (r = 0; r < 18; r++){
        for (c = 0; c < 70; c++){
            displayGrid[r][c] = '#';
            blankGrid[r][c] = '#';
        }
    }
}

//determine a number of rooms
int Dungeon::roomNumber(){
    int r = randInt(4, 6);
    return r;
}

//Constructer for room struct
Dungeon::Room::Room(int Cr, int Cc, int w, int h){
    centerC = Cc;
    centerR = Cr;
    width = w;
    height = h;
}

//create a new room
bool Dungeon::generateRoom(){
    //randomly determine center coordinates as well as height and width
    int centerRow = randInt(1, 16);
    int centerCol = randInt(1, 68);
    int width = randInt(3, 5);
    int height = randInt(3, 5);
    //if room runs off the edge of the map, return false
    if (centerRow+height > 16){
        return false;
    }
    if (centerRow-height < 1){
        return false;
    }
    if (centerCol+width > 68){
        return false;
    }
    if (centerCol-width < 1){
        return false;
    }
    
    //if room overlaps with another room, return false
    for (int r = (centerRow-height-1); r < (centerRow+height+1); r++){
        for (int c = (centerCol-width-1); c < (centerCol+width+1); c++){
            if (displayGrid[r][c] == ' '){
                return false;
            }
        }
    }
    //create a new room and convert from walls to empty space
    Room* pointer = new Room(centerRow, centerCol, width, height);
    for (int r = (centerRow-height); r < (centerRow+height); r++){
        for (int c = (centerCol-width); c < (centerCol+width); c++){
            displayGrid[r][c] = ' ';
            blankGrid[r][c] = ' ';
        }
    }
    //add to room vector
    rooms.push_back(pointer);
    return true;
}

void Dungeon::addRoom(){
    int p = roomNumber();
    while (p>0){
        bool room = generateRoom();
        if (room == true){
            p--;
        }
    }
}

//make the dungeon blank and then respawn rooms, monsters and items, and the player
void Dungeon::reset(){
    
    //delete current monsters, items and rooms
    for (int i = 0; i < monsters.size(); i++){
        delete monsters[i];
    }
    for (int i = 0; i < floorItems.size(); i++){
        delete floorItems[i];
    }
    
    for(int i = 0; i < rooms.size(); i++){
        delete rooms[i];
    }
    //clear vectors
    monsters.clear();
    floorItems.clear();
    rooms.clear();
    
    //increment floor number
    floor++;
    
    //create rooms, corridors, monsters and items
    initializeMap();
    addRoom();
    for (int i = 0; i < rooms.size(); i++){
        addCorridor(rooms[i]);
    }
    createDrops();
    addMonster();
    
    //determine random coordinates to move the player to
    int r = 0;
    int c = 0;
    do {
        r = randInt(1, 16);
        c = randInt(1, 68);
    } while (getCell(r, c) == '#' or getCell(r, c) == 'B' or getCell(r, c) == 'D' or getCell(r, c) == 'G' or getCell(r, c) == 'S');
    m_player->move(r, c);
    }
    

bool Dungeon::addPlayer(int r, int c){
    //if there isnt already a player, create one
    if (m_player != nullptr){
        return false;
    }
    m_player = new Player(this, r, c);
    return true;
}



void Dungeon::createDrops(){
    
    int R = randInt(2, 3); //number of items
    int r = 0;
    int c = 0;
    
    while (R > 0){
        //Numbers 1-7 correspond to different possible items
        int choice = randInt(1, 7);
        Object* item;
        //determine random coordinates to place the item
        do {
            r = randInt(1, 16);
            c = randInt(1, 68);
        } while (getCell(r, c) == '#' or getCell(r, c) == 'Q');
        displayGrid[r][c] = 'Q';
        switch(choice){ //based on random value of choice, create one of the following weapons
            case 1:{
                item = new Mace(r, c, this);
                break;
            }
            case 2:{
                item = new ShortSword(r, c, this);
                break;
            }
            case 3:{
                item = new LongSword(r, c, this);
                break;
            }
            case 4:{
                item = new EnhanceArmor(r, c, this);
                break;
            }
            case 5:{
                item = new EnhanceStr(r, c, this);
                break;
            }
            case 6:{
                item = new EnhanceHP(r, c, this);
                break;
            }
            case 7:{
                item = new EnhanceDex(r, c, this);
                break;
            }
        }
        //push them to floor items vector and deincrement
        floorItems.push_back(item);
        R--;
    }
    //if the dungeon level is 3 or lower, create a staircase
    if (floor <= 3){
        int stairR =0;
        int stairC =0;
        
        do{
            stairR = randInt(1, 16);
            stairC = randInt(1, 68);
        } while (getCell(stairR, stairC) == '#' or getCell(stairR, stairC) == 'Q');
        //add to floor items vector
        Object* stair = new Stairway(stairR, stairC, this);
        floorItems.push_back(stair);
    }
    //if floor is 4 (bottom floor), create a golden idol
    if (floor == 4){
        int idolR =0;
        int idolC =0;
        
        do{
            idolR = randInt(1, 16);
            idolC = randInt(1, 68);
        } while (getCell(idolR, idolC) == '#' or getCell(idolR, idolC) == 'Q');
        
        Object* idol = new Idol(idolR, idolC, this);
        floorItems.push_back(idol);
        
    }
    
}

void Dungeon::addCorridor(Room* a){
    
    //determine the side walls of the given room
    int rightCol = a->centerC + a->width;
    int leftCol = a->centerC - a->width;
    int topRow = (a->centerR) - (a->height);
    int bottomRow = (a->centerR) + (a->height);
    
    //look for a blank spot in the right direction, if one is found, dig a tunnel there and exit the function.
    for (int r = topRow; r < bottomRow+1; r++){
        for (int c = rightCol+1; c < 68; c++){
            if (displayGrid[r][c] == ' '){
                for (int t = rightCol; t < c+1; t++){
                    displayGrid[r][t] = ' ';
                    blankGrid[r][t] = ' ';
                }
                return;
                
            }
        }
    }
    //check in the left direction
    for (int r = topRow; r < bottomRow+1; r++){
        for (int c = leftCol-1; c > 1; c--){
            if (displayGrid[r][c] == ' '){
                for (int t = leftCol; t > c; t--){
                    displayGrid[r][t] = ' ';
                    blankGrid[r][t] = ' ';
                }
                return;
                
            }
        }
    }
    //check in the north direction
    for (int c = rightCol; c < leftCol+1; c++){
        for (int r = topRow+1; r > 1; r--){
            if (displayGrid[r][c] == ' '){
                for (int t = topRow; t > r+1; t--){
                    displayGrid[r][t] = ' ';
                    blankGrid[r][t] = ' ';
                }
                return;
                
            }
        }
    }
    //check in the south direction
    for (int c = rightCol; c < leftCol+1; c++){
        for (int r = bottomRow+1; r <16; r++){
            if (displayGrid[r][c] == ' '){
                for (int t = bottomRow; t < r+1; t++){
                    displayGrid[r][t] = ' ';
                    blankGrid[r][t] = ' ';
                }
                return;
                
            }
        }
    }
    
}

//return the character of the given coordinates
char Dungeon::getCell(int r, int c){
    char temp = displayGrid[r][c];
    
    return temp;
}

//display the dungeon
void Dungeon::display()
{
    //clear the screen
    clearScreen();
    
    int r, c;
    
    //copy each cell of blankgrid(only walls and empty spaces) to displaygrid
    for (r = 0; r < 18; r++){
        for (c = 0; c < 70; c++){
            displayGrid[r][c] = blankGrid[r][c];
        }
    }
    
    //draw items
    for(item = floorItems.begin(); item < floorItems.end(); item++){
        int tempR = (*item)->getRow();
        int tempC = (*item)->getCol();
        displayGrid[tempR][tempC] = (*item)->displayIcon();
    }
    
   //if player is not dead, draw player
    if (m_player != nullptr && m_player->isDead() == false)
        displayGrid[m_player->getRow()][m_player->getCol()] = '@';
    
    //draw monsters
    for (int i = 0; i < monsters.size(); i++){
        int tempR = monsters[i]->getRow();
        int tempC = monsters[i]->getCol();
        displayGrid[tempR][tempC] = monsters[i]->displayIcon();
    }
    
    //print the grid
    for (r = 0; r < 18; r++)
    {
        for (c = 0; c < 70; c++)
            cout << displayGrid[r][c];
        cout << endl;
    }
    cout << endl;
    
    //assemble statistics message
    string floorMsg = "Dungeon Level: " + to_string(floor) + ", ";
    string hpMsg = "Hit Points: " + to_string(m_player->getHP()) + ", ";
    string armorMsg = "Armor: " + to_string(m_player->getArmor()) + ", ";
    string strMsg = "Strength: " + to_string(m_player->getStr()) + ", ";
    string dexMsg = "Dexterity: " + to_string(m_player->getDex());
    string display = floorMsg + hpMsg + armorMsg + strMsg + dexMsg;
    
    //print display message
    cout << display << endl;
    cout << endl;
    
    //print turn results
    for (int i = 0; i < results.size(); i++){
        cout << results[i];
    }
    //empty turn results vector
    results.clear();
}


Player* Dungeon::player() const{
    return m_player;
}

bool Dungeon::addMonster()
{
    //Determine the total number of monsters on that floor
    int M = randInt(2, 5*(floor+1)+1);
    
    while (M > 0){
        //1, 2, 3 and 4 each correspond to a different type of monster
        int p = 0;
        //assign p a value based on the floor level
        if (floor == 0 or floor == 1){
            p = randInt(1, 2);
        }
        if (floor == 2){
            p = randInt(1, 3);
        }
        if (floor >= 3){
            p = randInt(1, 4);
        }
        
        //determine random coordinates for the new monster
        int r = 0;
        int c = 0;
        char a = '#';
        do{
            r = randInt(1, 16);
            c = randInt(1, 68);
            a = getCell(r, c);
        } while (a != ' ' and a != '>' and a != '?' and a != ')' and a != '&');
        
        //depending on the value of p, create a new monster and add them to the monster vector, and deincrement M
        switch(p)
        {
            case 1:{
                Monster* snake = new Snakewoman(this, r, c);
                monsters.push_back(snake);
                M--;
                break;
            }
            case 2:{
                Monster* gob = new Goblin(r, c, this);
                monsters.push_back(gob);
                M--;
                break;
            }
            case 3:{
                Monster* bogeyman = new Bogeyman(r, c, this);
                monsters.push_back(bogeyman);
                M--;
                break;
            }
            case 4:{
                Monster* drago = new Dragon(r, c, this);
                monsters.push_back(drago);
                M--;
                break;
            }
        }
        
    }
 return true;
}

//Determine if a monster exists at that spot. Called by player class
void Dungeon::findMonster(Actor* attacker, int r, int c){
    //iterate through monster vector
    for (ptr = monsters.begin(); ptr < monsters.end(); ptr++){
        int tempR = (*ptr)->getRow();
        int tempC = (*ptr)->getCol();
        if (tempR == r and tempC == c){
            break;
        }
    }
    //once matching coordinates are found, call combat function with player and monster
    combat(attacker, (*ptr));
}

void Dungeon::moveMonsters(Player* player){
   //iterate through vector of monsters
    for (ptr = monsters.begin(); ptr < monsters.end(); ptr++){
        //if the monster is dead, try to drop an item and delete the allocated memory and erase them from the vector
        if ((*ptr)->getHP() <= 0){
            (*ptr)->drop();
            Monster* temp = *ptr;
            monsters.erase(ptr);
            delete temp;
            continue;
        }
        //otherwise, call the move function on the monster
        (*ptr)->move(player);
    }
}

//Combat between two actors
void Dungeon::combat(Actor* attacker, Actor* defender){
    
    int attackerPoints = attacker->getDex() + attacker->getWeapon()->getDexBonus();
    int defenderPoints = defender->getArmor() + defender->getDex();
    bool hit;
    
    //pushing strings to be displayed after the turn
    results.push_back(attacker->getName());
    results.push_back(" ");
    results.push_back(attacker->getWeapon()->getAction());
    results.push_back(" ");
    results.push_back(defender->getName());
    
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)){
        hit = true;
    }
    else{
        hit = false;
        results.push_back(" and misses.\n");
    }
    
    //if attacker has hit defender
    if (hit == true){
        //determine damage dealt
        int damage = randInt(0, (attacker->getStr() + attacker->getWeapon()->getDamageBonus() - 1));
        defender->setHP(damage * (-1));
        //if defender is now dead
        if (defender->getHP() <= 0){
            //push a unique result message
            results.push_back(" and hits, dealing the final blow.\n");
        }
        //if attacker is wielding magic fangs of sleep
        else if (attacker->getWeapon()->getDexBonus() == 3)
        {
            //1 in 5 chance to put defender to sleep
            if (trueWithProbability(.2)){
                int addSleep = randInt(2, 6);
                
                //if defender is already asleep, set sleeptime to the maximum of the two values
                if (addSleep > (defender->getSleep())){
                    defender->setSleep(addSleep - defender->getSleep());
                }
                
                //if defender is not asleep, add sleep time to their count
                if (defender->getSleep() == 0){
                    defender->setSleep(addSleep);
                }
                
                results.push_back(" and hits, putting ");
                results.push_back(defender->getName());
                results.push_back(" to sleep.\n");
            }
            //otherwise, push a regular hit message
            else {
                results.push_back(" and hits.\n");
            }
        }
        //if attacker missed, push missed message
        else{
            results.push_back(" and hits.\n");
        }
    }
    
    //if player died, set them as dead
    if (m_player->getHP() <= 0){
        m_player->setDead();
    }
}

//determine if a game object exists at a set of given coordinates
Object* Dungeon::findItem(int r, int c){
    //iterate through the vector of floor items and grab their coordinates
    for(item = floorItems.begin(); item < floorItems.end(); item++){
        int tempR = (*item)->getRow();
        int tempC = (*item)->getCol();
        //if they match the given coordinates AND the player coordinates, erase that item from the floor items vector and return it.
        if (tempR == r and tempC == c and (m_player->getRow() == r and m_player->getCol() == c)){
            Object* temp = *item;
            floorItems.erase(item);
            return temp;
        }
        //If they only match the given coordinates, return a pointer to that item.
        else if (tempR == r and tempC == c){
            return *item;
        }
    }
    //if no match
    return nullptr;
}

//add a string to print for this turn
void Dungeon::addResult(string s){
    results.push_back(s);
}


//add an item to the dungeon floor
void Dungeon::pushItem(Object* item){
    floorItems.push_back(item);
}

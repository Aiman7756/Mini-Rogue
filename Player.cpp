
#include "Player.h"
#include "Dungeon.h"
#include "GameObjects.h"
#include "utilities.h"

using namespace std;

//create a new player with default stats
Player::Player(Dungeon* d, int r, int c){
    m_dungeon = d;
    row = r;
    col = c;
    max_hp = 20;
   hp = 20;
    armor = 2;
   str = 2;
   dex = 2;
    name = "Player";
    
    weapon = new ShortSword();
    
}

//delete player's weapon and inventory
Player::~Player(){
    delete weapon;
    if (inventory.size() != 0){
        for (int i = 0; i < inventory.size(); i++){
            delete inventory[i];
        }
    }
    
}

bool Player::isDead() const{
    return m_dead;
}

bool Player::idol() const{
    return idolObtained;
}


void Player::displayInventory(){
    clearScreen();
    char display = 'a';
    cout << "Inventory:\n";
    //display weapon in first slot
    cout << " " << display << ". " << weapon->getName() << endl;
    display++;
    //print remaining inventory
    for (inv = inventory.begin(); inv < inventory.end(); inv++){
        cout << " " << display << ". " << (*inv)->getName() << endl;
        display++;
    }
    
}

void Player::grabItem(){
    //check if item exists at those coordinates
    Object* add = m_dungeon->findItem(row, col);
    //if item is found
    if (add != nullptr){
        //if item is the staircase, call the dungeon reset function
        if (add->displayIcon() == '>'){
            m_dungeon->reset();
            return;
        }
        //if item is the golden idol
        if (add->displayIcon() == '&'){
            idolObtained = true;
            return;
        }
        //if inventory is full
        if (invCount == 26){
            string p = "Your knapsack is full; you can't pick that up.";
            m_dungeon->addResult(p);
            return;
        }
        else{
            //add item to inventory vector and send retrival string to dungeon class
            inventory.push_back(add);
            invCount++;
            string p = add->getRetrieve() + add->getName() + "\n";
            m_dungeon->addResult(p);
        }
    }
    
}




void Player::move(int r, int c){
    //if player is asleep, do nothing
    if (sleeptime > 0){
        sleeptime--;
        return;
    }
    //if given coordinates is a valid spot, change player coordinates to given set
    char cell = m_dungeon->getCell(r, c);
    if (cell == ' ' or cell == ')' or cell == '?' or cell == '>' or cell == '&'){
        row = r;
        col = c;
    }
    //if given coordinates are occupied by a monster, call combat function
    if (m_dungeon->getCell(r, c) == 'G' || m_dungeon->getCell(r, c) == 'S'|| m_dungeon->getCell(r, c) == 'B'|| m_dungeon->getCell(r, c) == 'D'){
        m_dungeon->findMonster(this, r, c);
    }
}

void Player::setDead(){
    m_dead = true;
}

void Player::cheat(){
    str = 9;
    max_hp = 50;
    hp = 50;
}


void Player::wieldWeapon(char item){
    if (item == 'a'){
        //pointing to already wielded weapon
        string p = "You are wielding " + weapon->getName();
        m_dungeon->addResult(p);
        return;
    }
    //convert character to number
    int index = convertInventory(item);
    if (index == -1){
        return;
    }
    //change pointer type using dynamic cast
    Weapon* newWeapon = dynamic_cast<Weapon*>(inventory[index]);
    if (newWeapon == nullptr){
        //if selected item is not a weapon, print "cant wield" string
        string p = "You can't wield " + inventory[index]->getName() + "\n";
        m_dungeon->addResult(p);
        return;
    }
    else {
        //swap pointers of current weapon and selected weapon
        Weapon* temp = weapon;
        weapon = newWeapon;
        inventory[index] = temp;
        string p = "You are wielding " + weapon->getName();
        m_dungeon->addResult(p);
    }
}

void Player::readScroll(char item){
    if (item == 'a'){
        //first slot always points to a weapon, so send error string
        string p = "You can't read a " + weapon->getName() + "\n";
        m_dungeon->addResult(p);
        return;
    }
    else{
        //convert character to numerical index
    int index = convertInventory(item);
    if (index == -1){
        return;
    }
        //convert to scroll pointer using dynamic cast
    Scroll* toRead = dynamic_cast<Scroll*>(inventory[index]);
    if (toRead == nullptr){
        //if selected item is not a scroll, send error string
        string p = "You can't read a " + inventory[index]->getName() + "\n";
        m_dungeon->addResult(p);
        return;
    }
    else {
        //call the scrolls efect function
        toRead->effect(this);
        //push result string
        string p = "You read the scroll called " + toRead->getName() + "\n" + toRead->getEffect() + "\n";
        m_dungeon->addResult(p);
        //delete item and remove from inventory, and deincrement inventory count
        Object* temp = inventory[index];
        inventory.erase(inventory.begin()+ index);
        delete temp;
        invCount--;
    }
    }
}

//simple switch function to convert character to numerical index
int Player::convertInventory(char input){
    switch (input){
        case 'b' : {return 0; break;}
        case 'c' : {return 1; break;}
        case 'd' : {return 2; break;}
        case 'e' : {return 3; break;}
        case 'f' : {return 4; break;}
        case 'g' : {return 5; break;}
        case 'h' : {return 6; break;}
        case 'i' : {return 7; break;}
        case 'j' : {return 8; break;}
        case 'k' : {return 9; break;}
        case 'l' : {return 10; break;}
        case 'm' : {return 11; break;}
        case 'n' : {return 12; break;}
        case 'o' : {return 13; break;}
        case 'p' : {return 14; break;}
        case 'q' : {return 15; break;}
        case 'r' : {return 16; break;}
        case 's' : {return 17; break;}
        case 't' : {return 18; break;}
        case 'u' : {return 19; break;}
        case 'v' : {return 20; break;}
        case 'w' : {return 21; break;}
        case 'x' : {return 22; break;}
        case 'y' : {return 23; break;}
        case 'z' : {return 24; break;}
        default: {return -1; break;}
    }
    
}

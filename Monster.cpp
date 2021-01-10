
#include "Monster.h"
#include "Dungeon.h"
#include "Player.h"
#include "utilities.h"
#include "GameObjects.h"


Monster::~Monster(){
}

char Monster::displayIcon(){
    return display;
}





//create a new snakewoman with default stats
Snakewoman::Snakewoman(Dungeon* d, int r, int c){
    
    hp = randInt(3, 6);
    max_hp = hp;
    row = r;
    col = c;
    m_dungeon = d;
    display = 'S';
    armor = 3;
    str = 2;
    dex = 3;
    sleeptime = 0;
    name = "the Snakewoman";
    weapon = new Fang();
}


void Snakewoman::move(Player* player){
    //if asleep, do nothing
    if (sleeptime > 0){
        sleeptime--;
        return;
    }
    int r = player->getRow();
    int c = player->getCol();
    
    //if adjecent to player, attack
    if ((row +1 == r and col == c) or (row-1 == r and col == c) or (row == r and col-1 == c) or (row == r and col+1 == c)){
        m_dungeon->combat(this, player);
        return;
    }
    //look for player in a 3 x 3 box centered on the snakewoman, if found try to move closer
    char a;
    int Mr = getRow();
    int Mc = getCol();
    int rowDif = r - Mr;
    int colDif = c - Mc;
    for (int i = Mr-3; i < Mr+4; i++)
        for (int t = Mc-3; t < Mc+4; t++){
            if (t == c and r == i){
                if (rowDif < 0){
                    a = m_dungeon->getCell(row-1, col);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        row = row -1;
                        return;
                    }
                }
                else if (rowDif > 0){
                    a = m_dungeon->getCell(row+1, col);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        row = row +1;
                        return;
                    }
                }
                else if (colDif < 0){
                    a = m_dungeon->getCell(row, col-1);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        col = col-1;
                        return;
                    }
                }
                else if (colDif > 0){
                    a = m_dungeon->getCell(row, col+1);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        col = col+1;
                        return;
                    }
                }
                
            }
        }
}

// 1 in 3 chance to drop magic fangs of sleep
void Snakewoman::drop(){
    //check if item already exists at that spot
    Object* pos = m_dungeon->findItem(row, col);
    if ( pos == nullptr){
        if (trueWithProbability(.33)){
            Object* temp = new Fang(row, col, m_dungeon);
            //send to dungeon's floor items vector
            m_dungeon->pushItem(temp);
        }
    }
}

Snakewoman::~Snakewoman(){
    delete weapon;
}


Goblin::Goblin(int r, int c, Dungeon* d){
    hp = randInt(15, 20);
    max_hp = hp;
    str = 3;
    dex = 1;
    armor = 1;
    row = r;
    col = c;
    display = 'G';
    name = "the Goblin";
    m_dungeon = d;
    weapon = new ShortSword();
    
}
//same algorithm as snakewoman but with distance of 15
void Goblin::move(Player* player){
    if (sleeptime > 0){
        sleeptime--;
        return;
    }
    
    int r = player->getRow();
    int c = player->getCol();
    
    if ((row +1 == r and col == c) or (row-1 == r and col == c) or (row == r and col-1 == c) or (row == r and col+1 == c)){
        m_dungeon->combat(this, player);
        return;
    }
    char a;
    int Mr = getRow();
    int Mc = getCol();
    int rowDif = r - Mr;
    int colDif = c - Mc;
    for (int i = Mr-15; i < Mr+16; i++)
        for (int t = Mc-15; t < Mc+16; t++){
            if (t == c and r == i){
                if (rowDif < 0){
                    a = m_dungeon->getCell(row-1, col);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        row = row -1;
                        return;
                    }
                }
                else if (rowDif > 0){
                    a = m_dungeon->getCell(row+1, col);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        row = row +1;
                        return;
                    }
                }
                else if (colDif < 0){
                    a = m_dungeon->getCell(row, col-1);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        col = col-1;
                        return;
                    }
                }
                else if (colDif > 0){
                    a = m_dungeon->getCell(row, col+1);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        col = col+1;
                        return;
                    }
                }
                
            }
        }
}

// 1 in 3 chance to drop magic axe or fangs
void Goblin::drop(){
    //check if theres already an item
    Object* pos = m_dungeon->findItem(row, col);
    if ( pos == nullptr){
        if (trueWithProbability(.33)){
            int p = randInt(1, 2); // determine if axe or fang
            switch (p){
                    //create new and push to dungeon's floor item vector
                case 1:{
                    Object* temp = new Fang(row, col, m_dungeon);
                    m_dungeon->pushItem(temp);
                }
                case 2:{
                    Object* temp = new MagicAxe(row, col, m_dungeon);
                    m_dungeon->pushItem(temp);
                }
            }
        }
    }
}

Goblin::~Goblin(){
    delete weapon;
}


Dragon::Dragon(int r, int c, Dungeon* d){
    hp = randInt(20, 25);
    max_hp = hp;
    str = 4;
    dex = 4;
    armor = 4;
    m_dungeon = d;
    display = 'D';
    row = r;
    col = c;
    name = "the Dragon";
    weapon = new LongSword();
}

Dragon::~Dragon(){
    delete weapon;
}

// 100% chance to drop a scroll
void Dragon::drop(){
    //check if theres already an item
    if (m_dungeon->findItem(row, col) == nullptr){
        int r = randInt(1, 5); // determine which type of scroll
        Object* temp = nullptr;
        switch(r){
                //create new scroll
            case 1:{
                temp = new Teleport(row, col, m_dungeon);
            }
            case 2:{
                temp = new EnhanceHP(row, col, m_dungeon);
            }
            case 3:{
                temp = new EnhanceDex(row, col, m_dungeon);
            }
            case 4:{
                temp = new EnhanceArmor(row, col, m_dungeon);
            }
            case 5:{
                temp = new EnhanceStr(row, col, m_dungeon);
            }
        }
        if (temp != nullptr)
            //push to dungeon's floor item vector
            m_dungeon->pushItem(temp);
    }
}

void Dragon::move(Player* player){
    //if asleep, do nothing
    if (sleeptime > 0){
        sleeptime--;
        return;
    }
    //1 in 10 chance to recover HP
    if (hp < max_hp){
        if (trueWithProbability(.1)){
            setHP(1);
        }
    }
    //if next to player, attack
    int r = player->getRow();
    int c = player->getCol();
    
    if ((row +1 == r and col == c) or (row-1 == r and col == c) or (row == r and col-1 == c) or (row == r and col+1 == c)){
        m_dungeon->combat(this, player);
    }
}

Bogeyman::Bogeyman(int r, int c, Dungeon* d){
    hp = randInt(5, 10);
    max_hp = hp;
    str = randInt(2, 3);
    dex = randInt(2, 3);
    armor = 2;
    display = 'B';
    row = r;
    col = c;
    m_dungeon = d;
    name = "the Bogeyman";
    weapon = new ShortSword();
}

//1 in 10 chance to drop magic axe
void Bogeyman::drop(){
    if (m_dungeon->findItem(row, col) == nullptr){
        if (trueWithProbability(.1) == true){
            Object* temp = new MagicAxe(row, col, m_dungeon);
            m_dungeon->pushItem(temp);
        }
    }
}

Bogeyman::~Bogeyman(){
    delete weapon;
}

//same algorithm as snakewoman with distance of 5
void Bogeyman::move(Player* player){
    if (sleeptime > 0){
        sleeptime--;
        return;
    }
    
    int r = player->getRow();
    int c = player->getCol();
    
    if ((row +1 == r and col == c) or (row-1 == r and col == c) or (row == r and col-1 == c) or (row == r and col+1 == c)){
        m_dungeon->combat(this, player);
        return;
    }
    char a;
    int Mr = getRow();
    int Mc = getCol();
    int rowDif = r - Mr;
    int colDif = c - Mc;
    for (int i = Mr-5; i < Mr+6; i++)
        for (int t = Mc-5; t < Mc+6; t++){
            if (t == c and r == i){
                if (rowDif < 0){
                    a = m_dungeon->getCell(row-1, col);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        row = row -1;
                        return;
                    }
                }
                else if (rowDif > 0){
                    a = m_dungeon->getCell(row+1, col);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        row = row +1;
                        return;
                    }
                }
                else if (colDif < 0){
                    a = m_dungeon->getCell(row, col-1);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        col = col-1;
                        return;
                    }
                }
                else if (colDif > 0){
                    a = m_dungeon->getCell(row, col+1);
                    if (a == ' ' or a == '>' or a == '?' or a == ')' or a == '&'){
                        col = col+1;
                        return;
                    }
                }
                
            }
        }
}





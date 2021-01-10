
#include "Actor.h"

//getters

int Actor::getHP(){
    return hp;
}
int Actor::getMaxHP(){
    return max_hp;
}
int Actor::getArmor(){
    return armor;
}
int Actor::getStr(){
    return str;
}
int Actor::getDex(){
    return dex;
}
int Actor::getRow() const{
    return row;
}
int Actor::getCol() const{
    return col;
}
int Actor::getSleep(){
    return sleeptime;
}

Weapon* Actor::getWeapon(){
    return weapon;
}

string Actor::getName(){
    return name;
}

//setters
void Actor::setMaxHP(int add){
    max_hp += add;
}
void Actor::setHP(int add){
    hp += add;
}
void Actor::setArmor(int add){
    armor += add;
}
void Actor::setStr(int add){
    str += add;
}
void Actor::setDex(int add){
    dex += add;
}
void Actor::setSleep(int add){
    sleeptime += add;
}



#include "GameObjects.h"
#include "Dungeon.h"
#include "Player.h"
#include "utilities.h"

//Object class getters
Object::~Object(){}

string Object::getName(){
    return name;
}

string Object::getRetrieve(){
    return retrieve;
}

int Object::getRow(){
    return row;
}

int Object::getCol(){
    return col;
}

char Object::displayIcon(){
    return display;
}

//different weapon constructors

ShortSword::ShortSword(){
    action = "slashes short sword at";
    dexBonus = 0;
    dmgBonus = 2;
    name = "short sword";
    display = ')';
    retrieve = "You pick up ";
}

ShortSword::ShortSword(int r, int c, Dungeon* d){
    action = "slashes short sword at";
    dexBonus = 0;
    dmgBonus = 2;
    name = "short sword";
    display = ')';
    row = r;
    col = c;
    m_dungeon = d;
    retrieve = "You pick up ";
}

ShortSword::~ShortSword(){}

Fang::Fang(){
    action = "strikes magic fangs at";
    dexBonus = 3;
    dmgBonus = 2;
    name = "magic fangs of sleep";
    display = ')';
    retrieve = "You pick up ";
}

Fang::Fang(int r, int c, Dungeon* d){
    action = "strikes magic fangs at";
    dexBonus = 3;
    dmgBonus = 2;
    name = "magic fangs of sleep";
    display = ')';
    row = r;
    col = c;
    m_dungeon = d;
    retrieve = "You pick up ";
}

Fang::~Fang(){}

LongSword::LongSword(){
    action = "swings long sword at";
    dexBonus = 2;
    dmgBonus = 4;
    name = "long sword";
    display = ')';
    retrieve = "You pick up ";
}

LongSword::LongSword(int r, int c, Dungeon* d){
    action = "swings long sword at";
    dexBonus = 2;
    dmgBonus = 4;
    name = "long sword";
    display = ')';
    row = r;
    col = c;
    m_dungeon = d;
    retrieve = "You pick up ";
}

LongSword::~LongSword(){}

MagicAxe::MagicAxe(){
    action = "chops magic axe at";
    dexBonus = 5;
    dmgBonus = 5;
    name = "magic axe";
    display = ')';
    retrieve = "You pick up ";
}

MagicAxe::MagicAxe(int r, int c, Dungeon* d){
    action = "chops magic axe at";
    dexBonus = 5;
    dmgBonus = 5;
    name = "magic axe";
    display = ')';
    row = r;
    col = c;
    m_dungeon = d;
    retrieve = "You pick up ";
}

MagicAxe::~MagicAxe(){}

Mace::Mace(){
    action = "swings mace at";
    dexBonus = 0;
    dmgBonus = 2;
    name = "mace";
    display = ')';
    retrieve = "You pick up ";
}

Mace::Mace(int r, int c, Dungeon* d){
    action = "swings mace at";
    dexBonus = 0;
    dmgBonus = 2;
    name = "mace";
    display = ')';
    row = r;
    col = c;
    m_dungeon = d;
    retrieve = "You pick up ";
    
}

Mace::~Mace(){}

//weapon class getters

string Weapon::getAction(){
    return action;
}

int Weapon::getDexBonus(){
    return dexBonus;
}

int Weapon::getDamageBonus(){
    return dmgBonus;
}

Weapon::~Weapon(){}

//stairway constructor and destructor

Stairway::Stairway(int r, int c, Dungeon* d){
    display = '>';
    row = r;
    col = c;
    m_dungeon = d;
}

Stairway::~Stairway(){}


Teleport::Teleport(int r, int c, Dungeon* d){
    name = "scroll of teleportation";
    aftereffect = "You feel your body wrenched in space and time.";
    row = r;
    col = c;
    m_dungeon = d;
    display = '?';
    retrieve = "You pick up a scroll called ";
}

//moves player to a random set of coordinates
void Teleport::effect(Player* player){
    int r = 0;
    int c = 0;
    char temp = '#';
    do {
        r = randInt(1, 16);
        c = randInt(1, 68);
        temp = m_dungeon->getCell(r, c);
    } while (temp == '#' or temp == 'B' or temp == 'S' or temp == 'G' or temp == 'D');
    player->move(r, c);
    }

Teleport::~Teleport(){}


EnhanceStr::EnhanceStr(int r, int c, Dungeon* d){
    name = "scroll of strength";
    aftereffect = "Your muscles bulge.";
    row = r;
    col = c;
    m_dungeon = d;
    display = '?';
    retrieve = "You pick up a scroll called ";
}

void EnhanceStr::effect(Player* player){
    player->setStr(randInt(1, 3));
}

EnhanceStr::~EnhanceStr(){}

EnhanceArmor::EnhanceArmor(int r, int c, Dungeon* d){
    name = "scroll of enhance armor";
    aftereffect =  "Your armor glows blue.";
    row = r;
    col = c;
    m_dungeon = d;
    display = '?';
    retrieve = "You pick up a scroll called ";
}

void EnhanceArmor::effect(Player* player){
    player->setArmor(randInt(1,3));
}

EnhanceArmor::~EnhanceArmor(){}

EnhanceHP::EnhanceHP(int r, int c, Dungeon* d){
    name = "scroll of enhance health";
    aftereffect = "You feel your heart beating stronger.";
    row = r;
    col = c;
    m_dungeon = d;
    display = '?';
    retrieve = "You pick up a scroll called ";
}

void EnhanceHP::effect(Player* player){
    player->setMaxHP(randInt(3, 8));
}

EnhanceHP::~EnhanceHP(){}

EnhanceDex::EnhanceDex(int r, int c, Dungeon* d){
    name = "scroll of enhance dexterity";
    aftereffect = "You feel like less of a klutz.";
    row = r;
    col = c;
    m_dungeon = d;
    display = '?';
    retrieve = "You pick up a scroll called ";
}

void EnhanceDex::effect(Player* player){
    player->setDex(1);
}

EnhanceDex::~EnhanceDex(){}

Scroll::~Scroll(){}

string Scroll::getEffect(){
    return aftereffect;
}

Idol::Idol(int r, int c, Dungeon* d){
    row = r;
    col = c;
    m_dungeon = d;
    name = "the golden idol";
    display = '&';
    retrieve = "You pick up ";
    
}

Idol::~Idol(){}

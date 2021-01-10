#include "Game.h"
#include "utilities.h"
#include "Dungeon.h"
#include "Player.h"
#include <iostream>
using namespace std;


Game::Game(int goblinSmellDistance)
{
    //initialize a new dungeon
    m_dungeon = new Dungeon();
    
    //determine random starting coordinates for the player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, 16);
        cPlayer = randInt(1, 68);
    } while (m_dungeon->getCell(rPlayer, cPlayer) != ' ');
    
    //add the player, monsters, and items
    m_dungeon->addPlayer(rPlayer, cPlayer);
    m_dungeon->addMonster();
    m_dungeon->createDrops();
        }

void Game::playerTurn(char action){
    
    Player* player = m_dungeon->player();
    
    // 1 in 10 chance to recover one point of HP
    if (trueWithProbability(.1) && (player->getHP() < player->getMaxHP())){
        player->setHP(1);
    }
    
    if (action == ARROW_UP){
        player->move(player->getRow()-1, player->getCol());
        return;
    }
    if (action == ARROW_RIGHT){
        player->move(player->getRow(), player->getCol()+1);
        return;
    }
    if (action == ARROW_DOWN){
        player->move(player->getRow()+1, player->getCol());
        return;
    }
    if (action == ARROW_LEFT){
        player->move(player->getRow(), player->getCol()-1);
        return;
    }
    if (action == 'c'){
        player->cheat();
    }
     if (action == 'i'){
         player->displayInventory();
         getCharacter();
     }
    if (action == 'g'){
        player->grabItem();
    }
    if (action == 'w'){
        player->displayInventory();
        char item = getCharacter();
        player->wieldWeapon(item);
    }
    if (action == 'r'){
        player->displayInventory();
        char item = getCharacter();
        player->readScroll(item);
    }
     if (action == '>'){
         player->grabItem();
     }

    return;
}


void Game::play()
{
    
    //initially display the dungeon
    m_dungeon->display();
    Player* player = m_dungeon->player();
    
    //while the player is alive and hasn't obtained the idol
        while (player->isDead() == false && player->idol() == false){
            //read an action for player turn
            char temp = getCharacter();
            if (temp == 'q'){
                break;
            }
            playerTurn(temp);
            if (player->idol() == true){
                break;
            }
            //move the monsters and redisplay dungeon
            m_dungeon->moveMonsters(player);
            m_dungeon->display();
        }
    //if player is dead, print quit message and wait for q input
    if (player->isDead() == true){
        cout << "Press q to exit game." << endl;
        char exit = getCharacter();
        while (exit != 'q')
            exit = getCharacter();
    }
    //if player has the idol, print winning message and wait for q input
    if (player->idol() == true){
        cout << "Congratulations, you won!" << endl;
        cout << "Press q to exit game." << endl;
        char exit = getCharacter();
        while (exit != 'q')
            exit = getCharacter();
    }
        
    }
        

Game::~Game(){
        delete m_dungeon;
    }


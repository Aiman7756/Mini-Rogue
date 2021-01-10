
#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Dungeon;
class Player;

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
    
private:
    void playerTurn(char action);
    Dungeon* m_dungeon;
    Player* m_player;
};

#endif // GAME_INCLUDED

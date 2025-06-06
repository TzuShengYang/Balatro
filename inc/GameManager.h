#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <cstdlib>

#include "Interface.h"
#include "Player.h"
#include "Item.h"

class Player;

class start;

class GameManager{
private:
    Player *current_user;
    bool first_in;
    
    //UI
    start *start_UI;
    start_menu *start_menu_UI;
    
    int status;
    void init();
public:
    GameManager();
    void implement_game();
};

#endif

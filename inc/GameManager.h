#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <cstdlib>

#include "Interface.h"
#include "Player.h"
#include "Item.h"
#include "Game.h"

class Player;

class start;

class GameManager{
private:
    Player *current_user;
    bool first_in;
    
    //UI
    start *start_UI;
    start_menu *start_menu_UI;
    sign_up *sign_up_UI;
    sign_in *sign_in_UI;
    main_menu *main_menu_UI;
    rule *rule_UI;
    leading_board *leading_board_UI;
    Game *balatro;
    
    
    int status;
    void init();
public:
    GameManager();
    void implement_game();
};

#endif

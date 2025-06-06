#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "Item.h"
#include <vector>

using namespace std;

class Game{
public:
    Game();

private:
    vector<card*> deck;

};

#endif

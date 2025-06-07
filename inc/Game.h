#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "Item.h"
#include <vector>

using namespace std;

class Game{
private:
    vector<card*> full_deck;
    vector<card*> deck;
    vector<card*> table;
    vector<good*> goods;

public:
    Game();

    void set_deck();
    void discard_card();
    void set_goods(string _goods_name, int _amount);

};

#endif

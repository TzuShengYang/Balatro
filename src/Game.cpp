#include "../inc/Game.h"
#include <random>
#include <algorithm>

using namespace std;


Game::Game(){
    for (int suit = 0; suit < 4; suit++){
        for (int number = 1; number <= 13; number++){
            card* new_card = new card();
            new_card->set_card(suit, number);
            full_deck.push_back(new_card);
        }
    }

    vector<pair<string, int>> goods_info = {
        {"score x 2", 10},
        {"change 3 cards to ♠", 5},
        {"change 3 cards to ♥", 5},
        {"change 3 cards to ♦", 5},
        {"change 3 cards to ♣", 5},
        {"copy 1 card", 8}
    };
    
    for (const auto& info : goods_info){
        good* new_goods = new good();
        new_goods->set_goods(info.first, info.second, 2);
        goods.push_back(new_goods);
    }
}

void Game::set_deck(){
    for (auto card_ptr : deck){
        delete card_ptr;
    }
    deck.clear();
    
    random_device rd;
    mt19937 gen(rd());
    shuffle(full_deck.begin(), full_deck.end(), gen);
    for(int i = 0; i < 8; i++){
        deck.push_back(full_deck[i]);
    }

}

void Game::discard_card(){


}

void Game::set_goods(string _goods_name, int _amount){
    for (auto goods_ptr : goods){
        delete goods_ptr;
    }
    goods.clear();


}

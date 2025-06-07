#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "Item.h"
#include <vector>
#include <map>

using namespace std;

class score_board{
private:
    unsigned int total_score;
    map<string, int> hand_type_times;

    int get_card_value(int card_number);

public:
    score_board();

    string set_hand_type_times(vector<card*> _cards); 
    void calculate_score(vector<card*> _cards);

    int get_times(string type_name);
    int get_score();

};

class Game{
private:
    score_board *my_score_board;
    Player *current_player;

    vector<card*> full_deck;
    vector<card*> hand;
    vector<card*> table;
    vector<good*> goods;

    int selected_card_number;
    int round;

    
    void reset_full_deck();//
    void shuffle_full_deck();
    void clear_hand();//
    void set_goods();//

    void sort_by_suit();
    void sort_by_number();

    void add_card_to_hand(int amount);
    void discard_card_from_hand();
    void put_card_from_hand_to_table();

    void calculate_score_of_table();
    int  get_the_score_of_cards();

    void show_table();
    void show_hand();
    void show_shop();
    void show_score_board();
    //void show_joker();

    void run_game_UI();

public:
    Game();

    int run_game();

};

#endif

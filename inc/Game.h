#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "Item.h"
#include "Interface.h"
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

void wait();

class score_board{
private:
    unsigned int total_score;
    unsigned int cur_score;
    map<string, int> hand_type_times;

    int get_card_value(int card_number);

public:
    score_board();

    string set_hand_type_times(vector<card*> _cards); 
    void calculate_score(vector<card*> _cards, bool _is_double);

    int get_times(string type_name);
    int get_score();
    string get_type(vector<card*> _cards);
    int get_cur_score();

    int get__multiplier(vector<card*> _cards);
    void init();

};


class Interface;

class Game: public Interface{
private:
    score_board *my_score_board;
    Player *current_player;

    vector<card*> full_deck;
    vector<card*> hand;
    vector<card*> table;
    vector<good*> goods;
    vector<good*> inventory;
    login_system *log_out_sys;

    int selected_card_number;
    int round;
    int play_hand;
    int play_hand_number;
    int discard_card;
    int discard_card_number;
    int score;
    int prev_score;
    int sort_status;
    int buy_item_num;

    bool inventory_button_is_selected;
    bool hand_button_is_selected;
    bool discard__button_is_selected;
    bool score_is_doubled;
    bool has_use_item;

    string current_hand_type;

    bool good_in_shop_can_buy(int no);
    bool good_in_inv_can_use(int no);
    void buy_good(int no);
    void use_good(int no);
    void set_inventory();
    
    void reset_full_deck();//
    void shuffle_full_deck();
    void clear_hand();//
    void set_goods();//

    void sort_by_suit();
    void sort_by_number();

    void add_card_to_hand(int amount);
    void discard_card_from_hand();
    void put_card_from_hand_to_table();
    void chosen_card_removal();
    void unchoose_hand_card();

    void calculate_score_of_table();
    int  get_the_score_of_cards();

    void show_table();
    void show_table_in_calculating();
    void show_hand_and_button();
    void show_hand_and_button_in_calculating();
    void show_result();
    void show_shop();
    void show_goods(int selected_idx);
    void show_inv_goods(int selected_idx);
    

    void show_inventory();
    void show_score_board();
    void show_sort_approach();

    void final_choice_processing();

    void run_game_UI();

    char input_manage();

    void small_blind();
    void big_blind();
    void the_manacle();

public:
    Game();

    int run_game(Player *_current_user);

};

#endif

#include "../inc/Game.h"
#include <random>
#include <algorithm>

using namespace std;


Game::Game(){
    my_score_board = new score_board;
    reset_full_deck();
    set_goods();
}

void Game::reset_full_deck(){
    for (auto i: full_deck){
        delete i;
    }

    full_deck.clear();

    for (int suit = 0; suit < 4; suit++){
        for (int number = 1; number <= 13; number++){
            card* new_card = new card();
            new_card->set_card(suit, number);
            full_deck.push_back(new_card);
        }
    }

    shuffle_full_deck();
}

void Game::shuffle_full_deck(){
    random_device rd;
    mt19937 gen(rd());
    shuffle(full_deck.begin(), full_deck.end(), gen);
}

void Game::clear_hand(){
    for (auto card_ptr : hand){
        delete card_ptr;
    }
    hand.clear();
}

void Game::set_goods(){
    for (int i = 0;i < 6;i++){
        good *temp = new good;
        switch(i){
            case 0:
                temp -> set_goods("score x 2", 10);
                break;

            case 1:
                temp -> set_goods("change 3 cards to ♠", 5);
                break;

            case 2:
                temp -> set_goods("change 3 cards to ♥", 5);
                break;

            case 3:
                temp -> set_goods("change 3 cards to ♦", 5);
                break;

            case 4:
                temp -> set_goods("change 3 cards to ♣", 5);
                break;
                
            case 5:
                temp -> set_goods("copy 1 card", 5);
                break;

            default:
                break;
        }
        
        goods.push_back(temp);
    }
}

void Game::add_card_to_hand(int amount = 1){
    for (int i = 0;i < amount;i++){
        card *temp = full_deck.back();
        full_deck.pop_back();
        hand.push_back(temp);
    }
}

void Game::discard_card_from_hand(){
    vector<card*> temp;
    for (auto i: hand){
        if (!i -> card_is_chosen()){
            temp.push_back(i);
        }
    }
    hand.clear();
    hand = temp;
}

void Game::put_card_from_hand_to_table(){
    vector<card*> temp;
    for (auto i: hand){
        if (i -> card_is_chosen()){
            table.push_back(i);
        } else {
            temp.push_back(i);
        }
    }
    hand.clear();
    hand = temp;
}

void Game::calculate_score_of_table(){
    my_score_board -> calculate_score(table);
}

int Game::get_the_score_of_cards(){
    return my_score_board -> get_score();
}

void Game::run_game_UI(){
    char input = 'i';

    for (round = 0;round < 4;round++){

    }
}

int Game::run_game(){
    run_game_UI();
}



//game
//-----------------------------------------------------------

score_board::score_board(){
    total_score = 0;
    hand_type_times = {
        {"High Card", 0},
        {"Pair", 0},
        {"Two Pair", 0},
        {"Three of a Kind", 0},
        {"Straight", 0},
        {"Flush", 0},
        {"Full House", 0},
        {"Four of a Kind", 0},
        {"Straight Flush", 0}
    };
}

string score_board::set_hand_type_times(vector<card*> _cards){
    int card_count = _cards.size();
    if (card_count == 0) return "";

    map<int, int> number_count;
    map<int, int> suit_count;
    
    for (auto card : _cards){
        number_count[card->get_card_num()]++;
        suit_count[card->get_card_suit()]++;
    }

    // straight_flush
    bool is_flush = false;
    if (card_count >= 5){
        for (auto& pair : suit_count){
            if (pair.second >= 5){
                is_flush = true;
                break;
            }
        }
    }

    // four_of_a_king
    bool is_straight = false;
    if (card_count >= 5){
        vector<int> numbers;
        for (auto& pair : number_count){
            numbers.push_back(pair.first);
        }
        sort(numbers.begin(), numbers.end());
        
        for (int i = 0; i <= numbers.size() - 5; i++){
            bool consecutive = true;
            for (int j = 0; j < 4; j++){
                if (numbers[i+j+1] != numbers[i+j] + 1){
                    consecutive = false;
                    break;
                }
            }
            if (consecutive){
                is_straight = true;
                break;
            }
        }
        
        // A2345
        if (!is_straight && numbers.size() >= 5){
            bool has_ace = (number_count.find(1) != number_count.end());
            bool has_2 = (number_count.find(2) != number_count.end());
            bool has_3 = (number_count.find(3) != number_count.end());
            bool has_4 = (number_count.find(4) != number_count.end());
            bool has_5 = (number_count.find(5) != number_count.end());
            
            if (has_ace && has_2 && has_3 && has_4 && has_5){
                is_straight = true;
            }
        }
    }

    // 
    vector<int> counts;
    for(auto& pair : number_count){
        counts.push_back(pair.second);
    }
    sort(counts.rbegin(), counts.rend());
    
    string hand_type = "";
    
    if(is_flush && is_straight){
        hand_type = "Straight Flush";
    }
    else if(counts[0] >= 4){
        hand_type = "Four of a Kind";
    } 
    else if(counts[0] >= 3 && counts[1] >= 2){
        hand_type = "Full House";
    }
    else if(is_flush){
        hand_type = "Flush";
    }
    else if(is_straight){
        hand_type = "Straight";
    }
    else if(counts[0] >= 3){
        hand_type = "Three of a Kind";
    }
    else if(counts[0] >= 2 && counts[1] >= 2){
        hand_type = "Two Pair";
    }
    else if(counts[0] >= 2){
        hand_type = "Pair";
    }
    else{
        hand_type = "High Card";
    }
    
    hand_type_times[hand_type]++;
    
    return hand_type;
}

void score_board::calculate_score(vector<card*> _cards){
    string hand_type = set_hand_type_times(_cards);
    
    // multiplier
    map<string, int> multipliers = {
        {"Straight Flush", 9},
        {"Four of a Kind", 8},
        {"Full House", 7},
        {"Flush", 6},
        {"Straight", 5},
        {"Three of a Kind", 4},
        {"Two Pair", 3},
        {"Pair", 2},
        {"High Card", 1}
    };
    
    int card_values_sum = 0;
    
    if(hand_type == "High Card"){
        int max_value = 0;
        for(auto card : _cards){
            int card_value = get_card_value(card->get_card_num());
            if(card_value > max_value){
                max_value = card_value;
            }
        }
        card_values_sum = max_value;
    }
    else if(hand_type == "Two Pair"){
        map<int, int> number_count;
        for(auto card : _cards){
            number_count[card->get_card_num()]++;
        }
        
        for(auto& pair : number_count){
            if(pair.second >= 2){
                card_values_sum += get_card_value(pair.first) * 2;
            }
        }
    }
    else {
        for(auto card : _cards){
            card_values_sum += get_card_value(card->get_card_num());
        }
    }
    
    int hand_score = card_values_sum * multipliers[hand_type];
    total_score += hand_score;
}

int score_board::get_times(string type_name){
    if (hand_type_times.find(type_name) != hand_type_times.end()){
        return hand_type_times[type_name];
    }
    else {
        return 0;
    }
}

int score_board::get_score(){
    return total_score;
}

int score_board::get_card_value(int card_number){
    if(card_number == 1){        // A
        return 11;
    }
    else if(card_number >= 11 && card_number <= 13){  // J, Q, K
        return 10;
    }
    else {                       // 2-10
        return card_number;
    }
}

//score_board
//-----------------------------------------------------------
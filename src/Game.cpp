#include "../inc/Game.h"
#include "../inc/InterfaceNo.h"

using namespace std;

void wait(){
    this_thread::sleep_for(chrono::milliseconds(500));
}

Game::Game(): Interface(){
    my_score_board = new score_board;
    log_out_sys = new login_system;
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

void Game::sort_by_suit(){ 
    sort(hand.begin(), hand.end(), [](card* a, card* b){
        if (a->get_card_suit() != b->get_card_suit()){
            return a->get_card_suit() < b->get_card_suit();
        }
        int num_a = a->get_card_num();
        int num_b = b->get_card_num();
        
        if (num_a == 1) num_a = 14;
        if (num_b == 1) num_b = 14;
        
        return num_a > num_b; 
    });
}

void Game::sort_by_number(){
    sort(hand.begin(), hand.end(), [](card* a, card* b){
        int num_a = a->get_card_num();
        int num_b = b->get_card_num();
        
        if(num_a == 1) num_a = 14;
        if(num_b == 1) num_b = 14;
        
        if(num_a != num_b) {
            return num_a > num_b;
        }
        
        int suit_a = a->get_card_suit();  
        int suit_b = b->get_card_suit();
        
        return suit_a < suit_b;  
    });
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
        } else {
            delete i;
        }
    }
    hand.clear();
    hand = temp;
}

void Game::put_card_from_hand_to_table(){
    table.clear();
    for (auto i: hand){
        if (i -> card_is_chosen()){
            table.push_back(i);
        }
    }
}

void Game::chosen_card_removal(){
    vector<card*> temp;
    for (auto i: hand){
        if (i -> card_is_chosen()){
            delete i;
        } else {
            temp.push_back(i);
        }
    }
    hand.clear();
    hand = temp;
}

void Game::unchoose_hand_card(){
    for (auto i: hand){
        if (i -> card_is_chosen()) i -> switch_card_status();
    }
}

void Game::calculate_score_of_table(){
    my_score_board -> calculate_score(table);
    show_table_in_calculating();
    score = my_score_board -> get_cur_score();
}

int Game::get_the_score_of_cards(){
    return my_score_board -> get_score();
}

void Game::show_table(){
    for (int i = 0;i < 5;i++){
        cout << "          ";
        cout << "            ";
        cout << "          ";
        for (int j = 0;j < 5;j++){
            if (i == 0){
                cout << "╔═════╗";
            } else if (i == 1 || i == 3){
                cout << "║     ║";
            } else if (i == 2){
                cout << "║EMPTY║";
            } else {
                cout << "╚═════╝";
            }
            cout << " ";
        }
        cout << "\n";
    }

    cout << "\n\n";
}

void Game::show_table_in_calculating(){
    string add_process = "                                ";
    char input;
    for (int card_idx = -1;card_idx <= selected_card_number;card_idx++){
        
        system("clear");
        show_score_board();
        for (int i = 0;i < 5;i++){
            cout << "          ";
            cout << "          ";
            cout << "            ";

            for (int j = 0;j < selected_card_number;j++){
                
                if (i == 0){
                    cout << "╔═════╗";
                } else if (i == 1 || i == 3){
                    cout << "   ";
                    if (table.at(j) -> get_card_suit() == 0) cout << "♠";
                    else if (table.at(j) -> get_card_suit() == 1) cout << "♥";
                    else if (table.at(j) -> get_card_suit() == 2) cout << "♦";
                    else cout << "♣";
                    cout << "   ";
                } else if (i == 2){
                    cout << "║ ";
                    if (table.at(j) -> get_card_num() == 1)       cout << " A ";
                    else if (table.at(j) -> get_card_num() == 10) cout << "1 0";
                    else if (table.at(j) -> get_card_num() == 11) cout << " J ";
                    else if (table.at(j) -> get_card_num() == 12) cout << " Q ";
                    else if (table.at(j) -> get_card_num() == 13) cout << " K ";
                    else cout << " " << table.at(j) -> get_card_num() << " ";
                    cout << " ║";
                } else {
                    cout << "╚═════╝";
                }
                cout << " ";
            }

            for (int j = 0;j < 5 - selected_card_number;j++){
                    if (i == 0){
                        cout << "╔═════╗";
                    } else if (i == 1 || i == 3){
                        cout << "║     ║";
                    } else if (i == 2){
                        cout << "║EMPTY║";
                    } else {
                        cout << "╚═════╝";
                    }
                    cout << " ";
                }

            cout << "\n";
        }

        if (card_idx >= 0 && card_idx < selected_card_number){
            if (table.at(card_idx) -> card_is_used()){
                if (table.at(card_idx) -> get_card_num() == 1){
                    add_process += "  +11   ";
                } else if (table.at(card_idx) -> get_card_num() >= 10){
                    add_process += "  +10   ";
                } else {
                    add_process += "   +" + to_string(table.at(card_idx) -> get_card_num()) + "   ";
                }
            } else {
                add_process += "        ";
            }
            cout << add_process << "\n";
        } else if (card_idx == selected_card_number){
            for (int x = 0;x < 5 - selected_card_number;x++) add_process += "        ";
            add_process += "   |  X ";
            cout << add_process;
            cout << my_score_board -> get__multiplier(table);
            cout << "   ( " << my_score_board -> get_type(table) << " )\n";
        } else {
            cout << "\n";
        }

        cout << "\n";
        
        show_hand_and_button_in_calculating();
        wait();
    }
     
    cin >> input;
}

void Game::show_hand_and_button(){
    if (sort_status == 0){
        sort_by_number();
    } else {
        sort_by_suit();
    }
    for (int i = 0;i < 5;i++){
        cout << "          ";
        //inventory
        if (i == 0 || i == 4) cout << "             ";
        else if (i == 1 || i == 3){
            if (inventory_button_is_selected) cout << "#=========#  ";
            else cout << " ---------   ";
        } else {
            if (inventory_button_is_selected) cout << "║INVENTORY║  ";
            else cout << "|INVENTORY|  ";
        }

        for (int j = 0;j < 8;j++){
            if (j == final_choice - 1){
                if (hand.at(j) -> card_is_chosen()) cout << "\033[33m";
                if (i == 0){
                    cout << "╔═════╗";
                } else if (i == 1 || i == 3){
                    cout << "║  ";
                    if (hand.at(j) -> get_card_suit() == 0) cout << "♠";
                    else if (hand.at(j) -> get_card_suit() == 1) cout << "♥";
                    else if (hand.at(j) -> get_card_suit() == 2) cout << "♦";
                    else cout << "♣";
                    cout << "  ║";
                } else if (i == 2){
                    cout << "║ ";
                    if (hand.at(j) -> get_card_num() == 1)       cout << " A ";
                    else if (hand.at(j) -> get_card_num() == 10) cout << "1 0";
                    else if (hand.at(j) -> get_card_num() == 11) cout << " J ";
                    else if (hand.at(j) -> get_card_num() == 12) cout << " Q ";
                    else if (hand.at(j) -> get_card_num() == 13) cout << " K ";
                    else cout << " " << hand.at(j) -> get_card_num() << " ";
                    cout << " ║";
                } else {
                    cout << "╚═════╝";
                }
                cout << "\033[0m";
            } else {
                if (hand.at(j) -> card_is_chosen()) cout << "\033[33m";
                if (i == 0){
                    cout << ".-----.";
                } else if (i == 1 || i == 3){
                    cout << "|  ";
                    if (hand.at(j) -> get_card_suit() == 0) cout << "♠";
                    else if (hand.at(j) -> get_card_suit() == 1) cout << "♥";
                    else if (hand.at(j) -> get_card_suit() == 2) cout << "♦";
                    else cout << "♣";
                    cout << "  |";
                } else if (i == 2){
                    cout << "| ";
                    if (hand.at(j) -> get_card_num() == 1)       cout << " A ";
                    else if (hand.at(j) -> get_card_num() == 10) cout << "1 0";
                    else if (hand.at(j) -> get_card_num() == 11) cout << " J ";
                    else if (hand.at(j) -> get_card_num() == 12) cout << " Q ";
                    else if (hand.at(j) -> get_card_num() == 13) cout << " K ";
                    else cout << " " << hand.at(j) -> get_card_num() << " ";
                    cout << " |";
                } else {
                    cout << "'-----'";
                }
                cout << "\033[0m";
            }
            cout << " ";
        }

        if (i == 0 || i == 4) cout << "";
        else if (i == 1 || i == 3){
            if (hand_button_is_selected) cout << "   #========#  ";
            else cout << "    --------   ";
        } else {
            if (hand_button_is_selected) cout << "   ║  HAND  ║  ";
            else cout << "   |  HAND  |  ";
        }

        if (i == 0 || i == 4) cout << "           ";
        else if (i == 1 || i == 3){
            if (discard__button_is_selected) cout << "#=======#";
            else cout << " ------- ";
        } else {
            if (discard__button_is_selected) cout << "║DISCARD║";
            else cout << "|DISCARD|";
        }

        cout << "\n";
    }

    show_sort_approach();
}

void Game::show_hand_and_button_in_calculating(){
    char input;
    for (int i = 0;i < 5;i++){
        cout << "          ";
        //inventory
        if (i == 0 || i == 4) cout << "             ";
        else if (i == 1 || i == 3){
            if (inventory_button_is_selected) cout << "#=========#  ";
            else cout << " ---------   ";
        } else {
            if (inventory_button_is_selected) cout << "║INVENTORY║  ";
            else cout << "|INVENTORY|  ";
        }

        for (int j = 0;j < 8;j++){
            if (j == final_choice - 1){
                if (hand.at(j) -> card_is_chosen()){
                    if (i == 0){
                        cout << "╔═════╗";
                    } else if (i == 1 || i == 3){
                        cout << "║     ║";
                    } else if (i == 2){
                        cout << "║EMPTY║";
                    } else {
                        cout << "╚═════╝";
                    }
                    cout << " ";
                }
            } else {
                if (hand.at(j) -> card_is_chosen()) cout << "\033[33m";
                if (i == 0){
                    cout << ".-----.";
                } else if (i == 1 || i == 3){
                    cout << "   ";
                    if (hand.at(j) -> get_card_suit() == 0) cout << "♠";
                    else if (hand.at(j) -> get_card_suit() == 1) cout << "♥";
                    else if (hand.at(j) -> get_card_suit() == 2) cout << "♦";
                    else cout << "♣";
                    cout << "   ";
                } else if (i == 2){
                    cout << "| ";
                    if (hand.at(j) -> get_card_num() == 1)       cout << " A ";
                    else if (hand.at(j) -> get_card_num() == 10) cout << "1 0";
                    else if (hand.at(j) -> get_card_num() == 11) cout << " J ";
                    else if (hand.at(j) -> get_card_num() == 12) cout << " Q ";
                    else if (hand.at(j) -> get_card_num() == 13) cout << " K ";
                    else cout << " " << hand.at(j) -> get_card_num() << " ";
                    cout << " |";
                } else {
                    cout << "'-----'";
                }
                cout << "\033[0m";
            }
            cout << " ";
        }

        if (i == 0 || i == 4) cout << "           ";
        else if (i == 1 || i == 3){
            if (hand_button_is_selected) cout << "   #========#  ";
            else cout << "    --------   ";
        } else {
            if (hand_button_is_selected) cout << "   ║  HAND  ║  ";
            else cout << "   |  HAND  |  ";
        }

        if (i == 0 || i == 4) cout << "           ";
        else if (i == 1 || i == 3){
            if (discard__button_is_selected) cout << "#=======#";
            else cout << " ------- ";
        } else {
            if (discard__button_is_selected) cout << "║DISCARD║";
            else cout << "|DISCARD|";
        }

        cout << "\n";
    }
}

void Game::show_result(){
    char input;
    cout << "\n\n\n";
    cout << "                                         " << setw(20) << left << "TOTAL SCORE : " << my_score_board -> get_score() << "\n";
    cout << "                                         " << setw(20) << left << "EXPERIENCE: " << (((my_score_board -> get_score() - 1) / 100) * 100) + 100 << "\n";
    cout << "                                         " << setw(20) << left << "CURRENCY: " << ((my_score_board -> get_score() - 1) / 10) << "\n";

    current_player -> gain_exp((((my_score_board -> get_score() - 1) / 100) * 100) + 100);
    current_player -> gain_currency(((my_score_board -> get_score() - 1) / 20));
    current_player -> set_user_highest(max((int)current_player -> get_user_highest(), my_score_board -> get_score()));
    current_player -> set_user_rate((my_score_board -> get_score()) / (play_hand_number + discard_card_number));

    log_out_sys -> save_data(current_player);
    log_out_sys -> log_out();

    cout << "\n";
    cout << "                                ----------- gameplay statistic -----------\n\n";
    cout << "                                         " << setw(20) << left << "PLAY CARDS: " << play_hand_number << "\n";
    cout << "                                         " << setw(20) << left << "DISCARD CARDS: " << discard_card_number << "\n\n";
    cout << "                                         " << setw(20) << left << "Straight Flush: " << my_score_board -> get_times("Straight Flush") << "\n";
    cout << "                                         " << setw(20) << left << "Four of a Kind: " << my_score_board -> get_times("Four of a Kind") << "\n";
    cout << "                                         " << setw(20) << left << "Full House: " << my_score_board -> get_times("Full House") << "\n";
    cout << "                                         " << setw(20) << left << "Flush: " << my_score_board -> get_times("Flush") << "\n";
    cout << "                                         " << setw(20) << left << "Straight: " << my_score_board -> get_times("Straight") << "\n";
    cout << "                                         " << setw(20) << left << "Three of a Kind: " << my_score_board -> get_times("Three of a Kind") << "\n";
    cout << "                                         " << setw(20) << left << "Two Pair: " << my_score_board -> get_times("Two Pair") << "\n";
    cout << "                                         " << setw(20) << left << "Pair: " << my_score_board -> get_times("Pair") << "\n";
    cout << "                                         " << setw(20) << left << "High Card: " << my_score_board -> get_times("High Card") << "\n\n";
    cin >> input;
}

void Game::show_shop(){

}

void Game::show_score_board(){
    cout << "Total score: " << my_score_board -> get_score() << "\n";
    cout << "\n";
    cout << "HANDS      : " << play_hand << "\n";
    cout << "DISCARDS   : " << discard_card << "\n";
    cout << "\n";
    cout << "SCORE      : " << score << "\n";
}

void Game::show_sort_approach(){
    if (sort_status == 0){
        cout << "Sort by NUMBER\n";
    } else {
        cout << "Sort by SUIT\n";
    }
}

void Game::final_choice_processing(){
    if (final_choice == 0){
        inventory_button_is_selected = true;
    } else {
        inventory_button_is_selected = false;
    }

    if (final_choice == 9){
        hand_button_is_selected = true;
    } else {
        hand_button_is_selected = false;
    }

    if (final_choice == 10){
        discard__button_is_selected = true;
    } else {
        discard__button_is_selected = false;
    }
}

void Game::run_game_UI(){
    char input = 'i';
    reset_full_deck();
    clear_hand();
    shuffle_full_deck();
    play_hand = 4;
    discard_card = 4;
    add_card_to_hand(8);
    
    while (true){   
        if (play_hand <= 0) return;

        do {
            system("clear");
            show_score_board();
            show_table();
            show_hand_and_button();
            input = input_manage();
            final_choice_processing();
        } while (input != '=');

        if (final_choice == 0){
            
        } else if (final_choice == 9){
            if (selected_card_number == 0){
                cout << "You have to select at least ONE card.";
                cin >> input;
                input = 'i';
            } else {
                put_card_from_hand_to_table();
                calculate_score_of_table();
                chosen_card_removal();
                unchoose_hand_card();
                add_card_to_hand(selected_card_number);
                play_hand_number += selected_card_number;
                table.clear();
                selected_card_number = 0;
                play_hand--;
            }
        } else if (final_choice == 10){
            if (selected_card_number == 0){
                cout << "You have to select at least ONE card.";
                cin >> input;
                input = 'i';
            } else if (discard_card <= 0){
                cout << "You can not discard cards anymore.";
                cin >> input;
                input = 'i';
            } else {
                discard_card_from_hand();
                unchoose_hand_card();
                add_card_to_hand(selected_card_number);
                discard_card_number += selected_card_number;
                selected_card_number = 0;
                discard_card--;
            }

        } else {
            if (selected_card_number >= 5){
                if (selected_card_number == 5 && hand.at(final_choice - 1) -> card_is_chosen()){
                    if (hand.at(final_choice - 1) -> card_is_chosen()){
                        selected_card_number--;
                    } else {
                        selected_card_number++;
                    }
                    hand.at(final_choice - 1) -> switch_card_status();
                } else {
                    cout << "You can not select more than 5 cards.";
                    cin >> input;
                    input = 'i';
                }
            } else {
                if (hand.at(final_choice - 1) -> card_is_chosen()){
                    selected_card_number--;
                } else {
                    selected_card_number++;
                }
                hand.at(final_choice - 1) -> switch_card_status();
            }
        }
    }
}

char Game::input_manage(){
    char input;
    cin >> input;
    if (input == 'w' || input == 'W') sort_status = 0;
    else if (input == 's' || input == 'S') sort_status = 1;

    if ((input == 'd' || input == 'D') && final_choice < 10) final_choice++;
    else if ((input == 'a' || input == 'A') && final_choice > 0) final_choice--; 

    return input;
}

void Game::small_blind(){
    char input = 'i';
    bool play = true;
    do {
        system("clear");
        cout << "                            ╔█████╗ ███╗   ███╗ █████╗ ██╗     ██╗     \n";
        cout << "                           ██╔════╝ ████╗ ████║██╔══██╗██║     ██║     \n";
        cout << "                            ██████╗ ██╔████╔██║███████║██║     ██║     \n";
        cout << "                            ╚════██╗██║╚██╔╝██║██╔══██║██║     ██║     \n";
        cout << "                            ██████╔╝██║ ╚═╝ ██║██║  ██║███████╗███████╗\n";
        cout << "                            ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝\n";

        cout << "                             ██████╗  ██╗      ██╗ ███╗   ██╗ ██████╗ \n";
        cout << "                             ██╔══██╗ ██║      ██║ ████╗  ██║ ██╔══██╗\n";
        cout << "                             ██████╔╝ ██║      ██║ ██╔██╗ ██║ ██║  ██║\n";
        cout << "                             ██╔══██╗ ██║      ██║ ██║╚██╗██║ ██║  ██║\n";
        cout << "                             ██████╔╝ ███████╗ ██║ ██║ ╚████║ ██████╔╝\n";
        cout << "                             ╚═════╝  ╚══════╝ ╚═╝ ╚═╝  ╚═══╝ ╚═════╝ \n";
        cout << "\n\n\n";

        if (input == 'd' || input == 'D'){
            play = false;
        } else if (input == 'a' || input == 'A'){
            play = true;
        }


        if (play){
            cout << "               #========================#              ------------------------ \n";
            cout << "               ║        P L A Y         ║             |         S K I P        |\n";
            cout << "               #========================#              ------------------------ \n";
        } else {
            cout << "                ------------------------              #========================#\n";
            cout << "               ║        P L A Y         ║             |         S K I P        |\n";
            cout << "                ------------------------              #========================#\n";
        }

        cin >> input;
        
    } while (input != '=');

    if (play) run_game_UI();
}

void Game::big_blind(){
    char input = 'i';
    bool play = true;
    do {
        system("clear");
        cout << "                                       ██████╗  ██╗ ╔██████╗ \n";
        cout << "                                       ██╔══██╗ ██║ ██║     \n";
        cout << "                                       ██████╔╝ ██║ ██║  ███╗\n";
        cout << "                                       ██╔══██╗ ██║ ██║   ██║\n";
        cout << "                                       ██████╔╝ ██║ ╚██████╔╝\n";
        cout << "                                       ╚═════╝  ╚═╝  ╚═════╝ \n";

        cout << "                             ██████╗  ██╗      ██╗ ███╗   ██╗ ██████╗ \n";
        cout << "                             ██╔══██╗ ██║      ██║ ████╗  ██║ ██╔══██╗\n";
        cout << "                             ██████╔╝ ██║      ██║ ██╔██╗ ██║ ██║  ██║\n";
        cout << "                             ██╔══██╗ ██║      ██║ ██║╚██╗██║ ██║  ██║\n";
        cout << "                             ██████╔╝ ███████╗ ██║ ██║ ╚████║ ██████╔╝\n";
        cout << "                            ╚═════╝  ╚══════╝ ╚═╝ ╚═╝  ╚═══╝ ╚═════╝ \n";
        cout << "\n\n\n";

        if (input == 'd' || input == 'D'){
            play = false;
        } else if (input == 'a' || input == 'A'){
            play = true;
        }

        if (play){
            cout << "               #========================#              ------------------------ \n";
            cout << "               ║        P L A Y         ║             |         S K I P        |\n";
            cout << "               #========================#              ------------------------ \n";
        } else {
            cout << "                ------------------------              #========================#\n";
            cout << "               |        P L A Y         |             ║         S K I P        ║\n";
            cout << "                ------------------------              #========================#\n";
        }

        cin >> input;

    } while (input != '=');

    if (play) run_game_UI();
}

void Game::the_manacle(){
    char input = 'i';

        system("clear");
        cout << "                                     ████████╗██╗  ██╗███████╗\n";
        cout << "                                     ╚══██╔══╝██║  ██║██╔════╝\n";
        cout << "                                        ██║   ███████║█████╗  \n";
        cout << "                                        ██║   ██╔══██║██╔══╝  \n";
        cout << "                                        ██║   ██║  ██║███████╗\n";
        cout << "                                        ╚═╝   ╚═╝  ╚═╝╚══════╝\n";


        cout << "              ████╗    ████╗ █████╗  ███╗   ██╗█████╗   ██████╗ ██╗      ███████╗ \n";
        cout << "              ████║    ████║ ██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██║      ██╔════╝\n";
        cout << "              ██╔██║  ██╔██║ ███████║██╔██╗ ██║███████║██║      ██║      █████╗  \n";
        cout << "              ██║╚██╗██╔╝██║ ██╔══██║██║╚██╗██║██╔══██║██║      ██║      ██╔══╝  \n";
        cout << "              ██║ ╚███╔╝ ██║ ██║  ██║██║ ╚████║██║  ██║╚██████╗ ███████╗ ███████╗\n";
        cout << "              ╚═╝  ╚══╝  ╚═╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝ ╚══════╝\n";

        cout << "\n\n\n";

        cin >> input;

    run_game_UI();
}

int Game::run_game(Player *_current_user){
    current_player = _current_user;

    selected_card_number = 0;
    sort_status = 0;
    score = 0;
    inventory_button_is_selected = true;
    hand_button_is_selected = false;
    discard__button_is_selected = false;
    play_hand_number = 0;
    discard_card_number = 0;

    my_score_board -> init();


    reset_full_deck();
    set_goods();

    for (int i = 0;i < 1;i++){
        round = i;
        show_shop();
        small_blind();
        show_shop();
        big_blind();
        show_shop();
        the_manacle();
    }

    show_result();

    return MAIN_MENU;
    
}



//game
//-----------------------------------------------------------

score_board::score_board(){
    total_score = 0;
    cur_score = 0;
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

void score_board::init(){
    total_score = 0;
    cur_score = 0;
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

    map<int, int> number_count = {
        {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0},
        {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}  
    };
    map<int, int> suit_count = {
        {0, 0}, {1, 0}, {2, 0}, {3, 0}
    };
    
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
    /*bool is_straight = false;
    if (card_count >= 5){
        vector<int> numbers;
        for (auto& pair : number_count){
            numbers.push_back(pair.first);
        }
        sort(numbers.begin(), numbers.end());
        
        for (int i = 0; i + 5 <= numbers.size(); i++){
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

        // 10JQKA
        
    }*/

    bool is_straight = false;
    if (card_count >= 5 && _cards.at(0) -> get_card_num() == _cards.at(1) -> get_card_num() + 1 && 
        _cards.at(1) -> get_card_num() == _cards.at(2) -> get_card_num() + 1 && 
        _cards.at(2) -> get_card_num() == _cards.at(3) -> get_card_num() + 1 && 
        _cards.at(3) -> get_card_num() == _cards.at(4) -> get_card_num() + 1)
        {
            is_straight = true;
        }
    
    // 10JQKA
    if (card_count >= 5 && _cards.at(0) -> get_card_num() == 1 && _cards.at(1) -> get_card_num() == 13 &&
        _cards.at(2) -> get_card_num() == 12 && _cards.at(3) -> get_card_num() == 11 && _cards.at(4) -> get_card_num() == 10)
        {
            is_straight = true;
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
    
    if (hand_type == "High Card"){
        int max_value = 0;
        int max_index = 0;
        for (int i=0; i<_cards.size(); i++){
            int card_value = get_card_value(_cards[i]->get_card_num());
            if (card_value > max_value){
                max_value = card_value;
                max_index = i;
            }
        }

        _cards[max_index] -> set_card_which_is_used();
        card_values_sum = max_value;
        
    } 
    else if (hand_type == "Pair") {
        map<int, int> number_count;
        map<int, vector<int>> number_positions;
        
        for (int i = 0; i < _cards.size(); i++){
            int card_num = _cards[i]->get_card_num();
            number_count[card_num]++;
            number_positions[card_num].push_back(i);
        }
        
        for (auto& pair : number_count){
            if(pair.second >= 2){
                card_values_sum += get_card_value(pair.first) * 2;
                for(int index : number_positions[pair.first]){
                    _cards[index]->set_card_which_is_used();
                }
            }
        }
    }
    else if (hand_type == "Two Pair"){
        map<int, int> number_count;
        map<int, vector<int>> number_positions;
        
        for (int i = 0; i < _cards.size(); i++){
            int card_num = _cards[i]->get_card_num();
            number_count[card_num]++;
            number_positions[card_num].push_back(i);
        }
        
        for (auto& pair : number_count){
            if(pair.second >= 2){
                card_values_sum += get_card_value(pair.first) * 2;
                for(int index : number_positions[pair.first]){
                    _cards[index]->set_card_which_is_used();
                }
            }
        }
    }
    else if (hand_type == "Three of a Kind"){
        map<int, int> number_count;
        map<int, vector<int>> number_positions;
        
        for (int i = 0; i < _cards.size(); i++){
            int card_num = _cards[i]->get_card_num();
            number_count[card_num]++;
            number_positions[card_num].push_back(i);
        }
        
        for (auto& pair : number_count){
            if(pair.second >= 3){
                card_values_sum += get_card_value(pair.first) * 3;
                for(int index : number_positions[pair.first]){
                    _cards[index]->set_card_which_is_used();
                }
            }
        }            
    }
    else {
        for(auto card : _cards){
            card_values_sum += get_card_value(card->get_card_num());
        }
        for(int i = 0;i < 5;i++){
            _cards[i]->set_card_which_is_used();
        }
    }
    
    int hand_score = card_values_sum * multipliers[hand_type];
    total_score += hand_score;
    cur_score = hand_score;
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

int score_board::get__multiplier(vector<card*> _cards){
    int card_count = _cards.size();
    if (card_count == 0) return 0;

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

    // four_of_a_kind
    /*bool is_straight = false;
    if (card_count >= 5){
        vector<int> numbers;
        for (auto& pair : number_count){
            numbers.push_back(pair.first);
        }
        sort(numbers.begin(), numbers.end());
        
        for (int i = 0; i + 5 <= numbers.size(); i++){
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

        // 10JQKA
        if (!is_straight && numbers.size() >= 5){
            bool has_ace = (number_count.find(1) != number_count.end());
            bool has_K = (number_count.find(13) != number_count.end());
            bool has_Q = (number_count.find(12) != number_count.end());
            bool has_J = (number_count.find(11) != number_count.end());
            bool has_10 = (number_count.find(10) != number_count.end());
            
            if (has_ace && has_K && has_Q && has_J && has_10){
                is_straight = true;
            }
        }
    }*/

    bool is_straight = false;
    if (card_count == 5 && _cards.at(0) -> get_card_num() == _cards.at(1) -> get_card_num() + 1 && 
        _cards.at(1) -> get_card_num() == _cards.at(2) -> get_card_num() + 1 && 
        _cards.at(2) -> get_card_num() == _cards.at(3) -> get_card_num() + 1 && 
        _cards.at(3) -> get_card_num() == _cards.at(4) -> get_card_num() + 1)
        {
            is_straight = true;
        }
    
    // 10JQKA
    if (card_count == 5 && _cards.at(0) -> get_card_num() == 1 && _cards.at(1) -> get_card_num() == 13 &&
        _cards.at(2) -> get_card_num() == 12 && _cards.at(3) -> get_card_num() == 11 && _cards.at(4) -> get_card_num() == 10)
        {
            is_straight = true;
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

    return multipliers[hand_type];
}

string score_board::get_type(vector<card*> _cards){
    int card_count = _cards.size();
    if (card_count == 0) return 0;

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

    // four_of_a_kind
    /*bool is_straight = false;
    if (card_count >= 5){
        vector<int> numbers;
        for (auto& pair : number_count){
            numbers.push_back(pair.first);
        }
        sort(numbers.begin(), numbers.end());
        
        for (int i = 0; i + 5 <= numbers.size(); i++){
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

        // 10JQKA
        if (!is_straight && numbers.size() >= 5){
            bool has_ace = (number_count.find(1) != number_count.end());
            bool has_K = (number_count.find(13) != number_count.end());
            bool has_Q = (number_count.find(12) != number_count.end());
            bool has_J = (number_count.find(11) != number_count.end());
            bool has_10 = (number_count.find(10) != number_count.end());
            
            if (has_ace && has_K && has_Q && has_J && has_10){
                is_straight = true;
            }
        }
    }*/

    bool is_straight = false;
    if (card_count == 5 && _cards.at(0) -> get_card_num() == _cards.at(1) -> get_card_num() + 1 && 
        _cards.at(1) -> get_card_num() == _cards.at(2) -> get_card_num() + 1 && 
        _cards.at(2) -> get_card_num() == _cards.at(3) -> get_card_num() + 1 && 
        _cards.at(3) -> get_card_num() == _cards.at(4) -> get_card_num() + 1)
        {
            is_straight = true;
        }
    
    // 10JQKA
    if (card_count == 5 && _cards.at(0) -> get_card_num() == 1 && _cards.at(1) -> get_card_num() == 13 &&
        _cards.at(2) -> get_card_num() == 12 && _cards.at(3) -> get_card_num() == 11 && _cards.at(4) -> get_card_num() == 10)
        {
            is_straight = true;
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

    
    return hand_type;
}

int score_board::get_cur_score(){
    return cur_score;
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
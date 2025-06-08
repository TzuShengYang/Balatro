#include "../inc/Interface.h"
#include "../inc/Item.h"
#include "../inc/InterfaceNo.h"
#include "../inc/Player.h"

using namespace std;

void show_balatro(){
    cout << "\n\n\n";
    cout << "  ██████╗  █████╗ ██╗      █████╗ ████████╗██████╗  ██████╗     ██████╗  ██████╗ ██╗  ██╗███████╗██████╗ \n";
    cout << "  ██╔══██╗██╔══██╗██║     ██╔══██╗╚══██╔══╝██╔══██╗██╔═══██╗    ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝██╔══██╗\n";
    cout << "  ██████╔╝███████║██║     ███████║   ██║   ██████╔╝██║   ██║    ██████╔╝██║   ██║█████╔╝ █████╗  ██████╔╝\n";
    cout << "  ██╔══██╗██╔══██║██║     ██╔══██║   ██║   ██╔══██╗██║   ██║    ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██╔══██╗\n";
    cout << "  ██████╔╝██║  ██║███████╗██║  ██║   ██║   ██║  ██║╚██████╔╝    ██║     ╚██████╔╝██║  ██╗███████╗██║  ██║\n";
    cout << "  ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝     ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n";
    cout << "\n";
}



//
//------------------------------------------------------------


Interface::Interface(){
    final_choice = 0;
    item_number = 0;
}

Interface::Interface(int _item_number){
    item_number = _item_number;
}

Interface::~Interface(){

}


//Interface
//------------------------------------------------------------

start::start(): Interface(){
    
}

void start::run_UI(){
    system("clear");
    show_balatro();
    cout << "                                       Welcome to Balatro Poker!\n\n";
    cout << "                                         Press any key to start...";
    char temp;
    cin >> temp;
    
}

int start::run_start(){
    run_UI();
    
    return 1;
}

//start
//----------------------------------------------------------

start_menu::start_menu(): Interface(3){}


int start_menu::run_start_menu(){
    set_item();
    run_UI();
    
    if (final_choice == 0) return RULE;
    if (final_choice == 1) return SIGN_UP;
    else return SIGN_IN;
}

void start_menu::set_item(){
    for (int i = 0;i < 3;i++){
        Item *temp = new Item(i);
        switch(i){
            case 0:
                temp->set_item_name("RULE");
                break;
                
            case 1:
                temp->set_item_name("SIGN UP");
                break;
            
            case 2:
                temp->set_item_name("LOGIN");
                break;
                
            default:
                break;
        }
        add_item(temp);
    }
    item_number = 3;
}

void start_menu::add_item(Item *obj){
    buttons.push_back(obj);
}

void start_menu::run_UI(){
    char input = 'i';
    do {
        system("clear");
        show_balatro();
        item_display(11);
        input = input_manage();
        
    } while (input != '=');
}

Item *start_menu::get_item(int index){
    return buttons.at(index);
}


void start_menu::item_display(int item_width, int item_height){
    for (int i = 0;i < item_height;i++){
        cout << "                            ";
        if (i == 0 || i == item_height - 1){
            for (int j = 0;j < item_number;j++){
                if (j){
                    for (int k = 0;k < 7;k++) cout << " ";
                }
                if (get_item(j) -> get_item_status()){
                    for (int k = 0;k < item_width;k++) cout << "=";
                } else {
                    for (int k = 0;k < item_width;k++) cout << "-";
                }
            }
        } else {
            for (int j = 0;j < item_number;j++){
                if (j){
                    for (int k = 0;k < 7;k++) cout << " ";
                }
                if (get_item(j) -> get_item_status()){
                    cout << "║" << left << setw(item_width - 2) << get_item(j) -> get_item_name() << "║";
                } else {
                    cout << "|" << left << setw(item_width - 2) << get_item(j) -> get_item_name() << "|";
                }
            }
        }
        cout << "\n";
    }
    return;
}

char start_menu::input_manage(){
    char input;
    cin >> input;

    if ((input == 'd' || input == 'D') && final_choice < item_number - 1){
        final_choice++;
        get_item(final_choice - 1) -> switch_item_status();
        get_item(final_choice) -> switch_item_status();
    } else if ((input == 'a' || input == 'A') && final_choice > 0){
        final_choice--;
        get_item(final_choice + 1) -> switch_item_status();
        get_item(final_choice) -> switch_item_status();
    }

    return input;
}


//start menu
//----------------------------------------------------------

sign_up::sign_up(): Interface(){
    current_user_account = "";
    current_user_password = "";
    successful = false;
}

int sign_up::run_sign_up(Player *_current_user){
    my_login_system.load_file();
    run_UI();

    if (successful){
        _current_user -> set_username(my_login_system.get_username());
        _current_user -> set_user_currency(my_login_system.get_user_currency());
        _current_user -> set_user_experience(my_login_system.get_user_experience());
        _current_user -> set_user_level(my_login_system.get_user_level());
        _current_user -> set_user_highest(my_login_system.get_user_highest());
        _current_user -> set_password(my_login_system.get_password());
        _current_user -> set_user_rate(my_login_system.get_user_rate());
    }
    current_user_account = "";
    current_user_password = "";
    successful = false;

    if (final_choice == 1){
        return MAIN_MENU;
    } else {
        return START_MENU;
    }
}

bool sign_up::char_is_valid(char input){
    return (input >= 48 && input <= 57) || (input >= 65 && input <= 90) || (input >= 97 && input <= 122);
}

void sign_up::run_UI(){
    char input = 'i';
    while (true){
        do {
            system("clear");
            show_balatro();
            block_display("ACCOUNT", current_user_account, true);

            cin >> input;
            if (input == '-' && current_user_account.length() > 0){
                current_user_account = current_user_account.substr(0, current_user_account.length() - 1);
            } else if (input == '-' && current_user_account.length() == 0){
                final_choice = 0;
                return;
            } else if (char_is_valid(input)){
                current_user_account += input;
            }
        } while (input != '=');

        if (current_user_account.length() == 0){
            cout << "Account can NOT be EMPTY.";
            cin >> input;
            input = 'i';
        } else if (my_login_system.have_existed(current_user_account)){
            cout << "Account has EXISTED.";
            cin >> input;
            input = 'i';
        } else {
            break;
        }
    }

    my_login_system.set_account(current_user_account);

    while (true){
        do {
            system("clear");
            show_balatro();
            block_display("ACCOUNT", current_user_account, false);
            block_display("PASSWORD", current_user_password, true);

            cin >> input;
            if (input == '-' && current_user_password.length() > 0){
                current_user_password = current_user_password.substr(0, current_user_password.length() - 1);
            }  else if (char_is_valid(input)){
                current_user_password += input;
            }
        } while (input != '=');

        if (current_user_account.length() == 0){
            cout << "Account can NOT be EMPTY.";
            cin >> input;
            input = 'i';
        } else {
            break;
        }
    }

    my_login_system.set_password(current_user_password);

    my_login_system.save_user();
    final_choice = 1;
    successful = true;
}

void sign_up::block_display(string title, string content, bool blod){
    if (blod){
        cout << "\n";
        cout << "                                    #================================#\n";
        cout << setw(34) << right << title << ": ║" << setw(32) << left << content << "║\n";
        cout << "                                    #================================#\n";
        cout << "\n";
    } else {
        cout << "\n";
        cout << "                                    .--------------------------------.\n";
        cout << setw(34) << right << title << ": ║" << setw(32) << left << content << "║\n";
        cout << "                                    '--------------------------------'\n";
        cout << "\n";  
    }

}

//sign up
//----------------------------------------------------------


sign_in::sign_in(): Interface(){
    current_user_account = "";
    current_user_password = "";
    successful = false;
    
}

int sign_in::run_sign_in(Player *_current_user){
    my_login_system.load_file();
    run_UI();

    if (successful){
        _current_user -> set_username(my_login_system.get_username());
        _current_user -> set_password(my_login_system.get_password());
        _current_user -> set_user_currency(my_login_system.get_user_currency());
        _current_user -> set_user_experience(my_login_system.get_user_experience());
        _current_user -> set_user_level(my_login_system.get_user_level());
        _current_user -> set_user_highest(my_login_system.get_user_highest());
        _current_user -> set_user_rate(my_login_system.get_user_rate());
    }
    current_user_account = "";
    current_user_password = "";

    if (final_choice == 1){
        return MAIN_MENU;
    } else {
        return START_MENU;
    }
}

bool sign_in::char_is_valid(char input){
    return (input >= 48 && input <= 57) || (input >= 65 && input <= 90) || (input >= 97 && input <= 122);
}

void sign_in::run_UI(){
    char input = 'i';
    while (true){
        do {
            system("clear");
            show_balatro();
            block_display("ACCOUNT", current_user_account, true);

            cin >> input;
            if (input == '-' && current_user_account.length() > 0){
                current_user_account = current_user_account.substr(0, current_user_account.length() - 1);
            } else if (input == '-' && current_user_account.length() == 0){
                final_choice = 0;
                return;
            } else if (char_is_valid(input)){
                current_user_account += input;
            }
        } while (input != '=');

        if (current_user_account.length() == 0){
            cout << "Account can NOT be EMPTY.";
            cin >> input;
            input = 'i';
        } else if (!my_login_system.have_existed(current_user_account)){
            cout << "Account NOT FOUND.";
            cin >> input;
            input = 'i';
        } else {
            break;
        }
    }

    my_login_system.set_account(current_user_account);

    while (true){
        
        do {
            system("clear");
            show_balatro();
            block_display("ACCOUNT", current_user_account, false);
            block_display("PASSWORD", current_user_password, true);

            cin >> input;
            if (input == '-' && current_user_password.length() > 0){
                current_user_password = current_user_password.substr(0, current_user_password.length() - 1);
            }  else if (char_is_valid(input)){
                current_user_password += input;
            }
        } while (input != '=');

        if (current_user_account.length() == 0){
            cout << "Account can NOT be EMPTY.";
            cin >> input;
            input = 'i';
        } else if (my_login_system.password_is_valid(current_user_password)){
            break;
        } else {
            cout << "Password is INCORRECT.";
            cin >> input;
            input = 'i';
        }
    }

    my_login_system.set_password(current_user_password);
    successful = true;
    final_choice = 1;
}

void sign_in::block_display(string title, string content, bool blod){
    if (blod){
        cout << "\n";
        cout << "                                    #================================#\n";
        cout << setw(34) << right << title << ": ║" << setw(32) << left << content << "║\n";
        cout << "                                    #================================#\n";
        cout << "\n";
    } else {
        cout << "\n";
        cout << "                                    .--------------------------------.\n";
        cout << setw(34) << right << title << ": ║" << setw(32) << left << content << "║\n";
        cout << "                                    '--------------------------------'\n";
        cout << "\n";
    }

}

//sign up
//----------------------------------------------------------

main_menu::main_menu(): Interface(4){}

int main_menu::run_main_menu(Player *_current_user){
    current_user = _current_user;
    set_item();
    run_UI();
    
    if (final_choice == 0) return PLAY;
    else if (final_choice == 1) return START_MENU;
    else if (final_choice == 2) return QUIT;
    else return LEADINGBOARD;
}

void main_menu::set_item(){
    for (int i = 0;i < 4;i++){
        Item *temp = new Item(i);
        switch(i){
            case 0:
                temp->set_item_name("PLAY");
                break;
                
            case 1:
                temp->set_item_name("LOG OUT");
                break;
            
            case 2:
                temp->set_item_name("QUIT");
                break;

            case 3:
                temp->set_item_name("LEADING BOARD");
                break;
                
            default:
                break;
        }
        add_item(temp);
    }
    item_number = 4;
}

void main_menu::add_item(Item *obj){
    buttons.push_back(obj);
}

void main_menu::run_UI(){
    char input = 'i';
    do {
        system("clear");
        cout << current_user -> get_username() << "\n";
        cout << current_user -> get_user_level() << "\n";
        cout << current_user -> get_user_experience() << "\n";
        cout << current_user -> get_user_currency() << "\n";
        cout << current_user -> get_user_highest() << "\n";
        cout << current_user -> get_user_rate() << "\n";
        cout << current_user -> get_password() << "\n";
        show_balatro();
        item_display(15);
        input = input_manage();
        
    } while (input != '=');
}

Item *main_menu::get_item(int index){
    return buttons.at(index);
}


void main_menu::item_display(int item_width, int item_height){
    for (int i = 0;i < item_height;i++){
        cout << "               ";
        if (i == 0 || i == item_height - 1){
            for (int j = 0;j < item_number;j++){
                if (j){
                    for (int k = 0;k < 7;k++) cout << " ";
                }
                if (get_item(j) -> get_item_status()){
                    for (int k = 0;k < item_width;k++) cout << "=";
                } else {
                    for (int k = 0;k < item_width;k++) cout << "-";
                }
            }
        } else {
            for (int j = 0;j < item_number;j++){
                if (j){
                    for (int k = 0;k < 7;k++) cout << " ";
                }
                if (get_item(j) -> get_item_status()){
                    cout << "║" << left << setw(item_width - 2) << get_item(j) -> get_item_name() << "║";
                } else {
                    cout << "|" << left << setw(item_width - 2) << get_item(j) -> get_item_name() << "|";
                }
            }
        }
        cout << "\n";
    }
    return;
}

char main_menu::input_manage(){
    char input;
    cin >> input;

    if ((input == 'd' || input == 'D') && final_choice < item_number - 1){
        final_choice++;
        get_item(final_choice - 1) -> switch_item_status();
        get_item(final_choice) -> switch_item_status();
    } else if ((input == 'a' || input == 'A') && final_choice > 0){
        final_choice--;
        get_item(final_choice + 1) -> switch_item_status();
        get_item(final_choice) -> switch_item_status();
    }

    return input;
}

//main menu
//----------------------------------------------------------

int rule::show_rule(){
    int page = 0;
    char choice;
    system("clear");
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║                                                  ║\n";
    cout << "║             Use 'WASD' keys to select            ║\n";
    cout << "║               Use '=' key to enter               ║\n";
    cout << "║            Use '-' key to delete input           ║\n";
    cout << "║                                                  ║\n";
    cout << "║                                                  ║\n";
    cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
    cout << "║           A ┃ < ┃   page 1/6   ┃ > ┃ D           ║\n";
    cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
    cout << "║                                                  ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    while (cin >> choice){
        if ((choice == 'D' || choice == 'd') && page != 5){
            page += 1;
        } else if ((choice == 'A' || choice == 'a') && page != 0) {
            page -= 1;
        } else if (choice == '=' && page == 5) {
            break;
        }

        switch (page) {
            case 0:
                system ("clear");
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                                  ║\n";
                cout << "║             Use 'WASD' keys to select            ║\n";
                cout << "║               Use '=' key to enter               ║\n";
                cout << "║            Use '-' key to delete input           ║\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║           A ┃ < ┃   page 1/6   ┃ > ┃ D           ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║                                                  ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                break;
            case 1:
                system ("clear");
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                                  ║\n";
                cout << "║           There is 1 round in one game           ║\n";
                cout << "║              Each round has 3 blinds             ║\n";
                cout << "║       SMALL BLIND, BIG BLIND, MANACLE BLIND      ║\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║           A ┃ < ┃   page 2/6   ┃ > ┃ D           ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║                                                  ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                break;
            case 2:
                system ("clear");
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                                  ║\n";
                cout << "║              In SMALL and BIG Blind,             ║\n";
                cout << "║          player can choose PLAY or SKIP          ║\n";
                cout << "║   But in MANACLE BLIND, player must choose PLAY  ║\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║           A ┃ < ┃   page 3/6   ┃ > ┃ D           ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║                                                  ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                break;
            case 3:
                system ("clear");
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║   In each blind, player must play hand 4 times   ║\n";
                cout << "║   Player also has 4 times to discard 1~5 cards   ║\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║           A ┃ < ┃   page 4/6   ┃ > ┃ D           ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║                                                  ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                break;
            case 4:
                system ("clear");
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║           After 3 blinds in one round,           ║\n";
                cout << "║             navigate to award stage              ║\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║           A ┃ < ┃   page 5/6   ┃ > ┃ D           ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║                                                  ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                break;
            case 5:
                system ("clear");
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║            Now try your best to become           ║\n";
                cout << "║               the top 1 player !!!               ║\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║           A ┃ < ┃   page 6/6   ┃ > ┃ D           ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║              Enter '=' to start ...              ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                break;
            default:
                system ("clear");
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                                  ║\n";
                cout << "║             Use 'WASD' keys to select            ║\n";
                cout << "║               Use '=' key to enter               ║\n";
                cout << "║            Use '-' key to delete input           ║\n";
                cout << "║                                                  ║\n";
                cout << "║                                                  ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║           A ┃ < ┃   page 1/4   ┃ > ┃ D           ║\n";
                cout << "║              ━━━━━━━━━━━━━━━━━━━━━━              ║\n";
                cout << "║                                                  ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";
                break;
        }
    }

    
    
    return START_MENU;
} 
    
//rule
//----------------------------------------------------------

leading_board::leading_board(): Interface(){
    page = 0;
    userdata = load_user();
    key = "highest";
}

int leading_board::show_leading_board(){
    run_UI();
    return MAIN_MENU;
}

void leading_board::run_UI(){
    char input = 'i';
    userdata = load_user();
    do {
        system("clear");
        bar_display();
        sort_leading_board();
        rank_table_display();
        input = input_manage();
    } while (input != '=');
}

char leading_board::input_manage(){
    char input;
    cin >> input;
    if ((input == 'd' || input == 'D') && page < 2){
        page++;
    } else if ((input == 'a' || input == 'A') && page > 0){
        page--;
    }

    switch (page){
        case 0: 
            key = "highest";
            break;

        case 1:
            key = "experience";
            break;

        case 2:
            key = "level";
            break;

        default:
            break;
    }

    return input;
}

void leading_board::rank_table_display(){
    int linenum = min(15, (int)sorted_rank.size());

    for (int i = 1;i <= linenum;i++){
        const auto &[name, val] = sorted_rank[i - 1];
        cout << "          |";
        cout << setw(5) << left << i;
        cout << setfill('-') << "    " << setw(36) << left << name;
        cout << setfill(' ') << setw(5) << right << val << "|\n";
    }
}

void leading_board::sort_leading_board(){

    sorted_rank.clear();

    for (const auto &[name, info]: userdata.items()){
        sorted_rank.emplace_back(name, info[key]);
    }

    sort(sorted_rank.begin(), sorted_rank.end(), 
        [](const pair<string, int> &a, const pair<string, int> &b){
            return a.second > b.second;
        }
    );
}

void leading_board::bar_display(){
    cout << "          ";

    if (page == 0){
        cout << "#";
        for (int i = 0;i < 16;i++) cout << "=";
    } else {
        cout << ".";
        for (int i = 0;i < 16;i++) cout << "-";
    }

    if (page == 0 || page == 1){
        cout << "#";
    } else {
        cout << ".";
    }

    if (page == 1) for (int i = 0;i < 16;i++) cout << "=";
    else for (int i = 0;i < 16;i++) cout << "-";

    if (page == 1 || page == 2){
        cout << "#";
    } else {
        cout << ".";
    }

    if (page == 2) for (int i = 0;i < 16;i++) cout << "=";
    else for (int i = 0;i < 16;i++) cout << "-";

    if (page == 2){
        cout << "#\n";
    } else {
        cout << ".\n";
    }

    cout << "          ";

    if (page == 0){
        cout << "║";
    } else {
        cout << "|";
    }

    cout << "  HIGHEST SCORD ";

    if (page == 0 || page == 1){
        cout << "║";
    } else {
        cout << "|";
    }

    cout << "   EXPERIENCE   ";

    if (page == 1 || page == 2){
        cout << "║";
    } else {
        cout << "|";
    }

    cout << "      LEVEL     ";

    if (page == 2){
        cout << "║\n";
    } else {
        cout << "|\n";
    }

    cout << "          :----------------'----------------'----------------:\n";
}

json leading_board::load_user(){
    ifstream infile("users.json");
    if (!infile.is_open()) return json::object();
    json users;
    infile >> users;
    infile.close();
    return users;
}

//leading board
//----------------------------------------------------------
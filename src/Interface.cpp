#include "../inc/Interface.h"
#include "../inc/Item.h"
#include "../inc/InterfaceNo.h"

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
    
    if (final_choice == 1) return LOGIN;
    else return SIGN_UP;
}

void start_menu::set_item(){
    for (int i = 0;i < 3;i++){
        Item *temp = new Item(i);
        switch(i){
            case 0:
                temp->set_item_name("RULE");
                break;
                
            case 1:
                temp->set_item_name("LOGIN");
                break;
            
            case 2:
                temp->set_item_name("SIGN UP");
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





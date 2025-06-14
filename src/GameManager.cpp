#include "../inc/GameManager.h"
#include "../inc/Interface.h"
#include "../inc/Player.h"
#include "../inc/InterfaceNo.h"

using namespace std;

GameManager::GameManager(){
    status = 0;
    first_in = true;
    
    current_user = new Player;
    
    start_UI = new start;
    start_menu_UI = new start_menu;
    sign_up_UI = new sign_up;
    sign_in_UI = new sign_in;
    main_menu_UI = new main_menu;
    rule_UI = new rule;
    leading_board_UI = new leading_board;
    balatro = new Game;

}

void GameManager::init(){
    system("clear");
    system("stty -icanon");
}

void GameManager::implement_game(){
    init();

    //rule_UI -> show_rule();

    while (status != QUIT){
        switch (status) {
            case START:
                status = start_UI -> run_start();
                break;

            case START_MENU:
                status = start_menu_UI -> run_start_menu();
                break;

            case SIGN_UP:
                status = sign_up_UI -> run_sign_up(current_user);
                break;

            case SIGN_IN:
                status = sign_in_UI -> run_sign_in(current_user);
                break;

            case MAIN_MENU:
                status = main_menu_UI -> run_main_menu(current_user);
                break;

            case RULE:
                status = rule_UI -> show_rule();
                break;

            case LEADINGBOARD:
                status = leading_board_UI -> show_leading_board();
                break;

            case PLAY:
                status = balatro -> run_game(current_user);
                break;
                
            default:
                return;
        }
    }

    system("clear");
        cout << "\n\n\n";
        cout << "                     ██████╗ ██╗   ██╗███████╗    ██████╗ ██╗   ██╗███████╗\n";
        cout << "                     ██╔══██╗╚██╗ ██╔╝██╔════╝    ██╔══██╗╚██╗ ██╔╝██╔════╝\n";
        cout << "                     ██████╔╝ ╚████╔╝ █████╗      ██████╔╝ ╚████╔╝ █████╗  \n";
        cout << "                     ██╔══██╗  ╚██╔╝  ██╔══╝      ██╔══██╗  ╚██╔╝  ██╔══╝  \n";
        cout << "                     ██████╔╝   ██║   ███████╗    ██████╔╝   ██║   ███████╗\n";
        cout << "                     ╚═════╝    ╚═╝   ╚══════╝    ╚═════╝    ╚═╝   ╚══════╝\n";
        cout << "\n";
}

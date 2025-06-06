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
}

void GameManager::init(){
    system("clear");
    system("stty -icanon");
}

void GameManager::implement_game(){
    init();

    while (status != 10){
        switch (status) {
            case 0:
                status = start_UI -> run_start();
                break;

            case 1:
                status = start_menu_UI -> run_start_menu();
                break;
            case 2:
                
                break;
            default:
                return;
        }
    }
}

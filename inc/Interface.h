#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Item.h"
#include "json.hpp"
#include "LoginSystem.h"
#include "Player.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using json = nlohmann::json;
using namespace std;

void show_balatro();

class Interface{
protected:
    int final_choice;
    int item_number;
public:
    Interface();
    Interface(int _item_number);
    virtual ~Interface();
};

//----------------------------------------------

class start: public Interface{
private:
    void run_UI();
public:
    start();
    int run_start();
};

//----------------------------------------------

class start_menu: public Interface{
private:
    vector<Item*> buttons;
    void set_item();
    void run_UI();
    void add_item(Item *obj);
    void item_display(int item_width, int item_height = 3);
    Item *get_item(int index);
    char input_manage();
public:
    start_menu();
    int run_start_menu();
};

//----------------------------------------------

class sign_up: public Interface{
private:
    login_system my_login_system;

    string current_user_account;
    string current_user_password;

    void run_UI();
    void block_display(string title, string content, bool blod);
    bool char_is_valid(char input);
public:
    sign_up();
    int run_sign_up(Player *_current_user);
};

//----------------------------------------------

class sign_in: public Interface{
private:
    login_system my_login_system;

    string current_user_account;
    string current_user_password;

    void run_UI();
    void block_display(string title, string content, bool blod);
    bool char_is_valid(char input);
public:
    sign_in();
    int run_sign_in(Player *_current_user);
};

//----------------------------------------------

class main_menu: public Interface{
private:
    Player *current_user;
    vector<Item*> buttons;
    void set_item();
    void run_UI();
    void add_item(Item *obj);
    void item_display(int item_width, int item_height = 3);
    Item *get_item(int index);
    char input_manage();
public:
    main_menu();
    int run_main_menu(Player *_current_user);
};

//----------------------------------------------

class rule: public Interface{
public:
    rule(){}
    int show_rule();
};

//----------------------------------------------
/*
class leading_board: public Interface{
private:
    int page;
    json userdata;
    string key;

    void run_UI();
    void bar_display();
    void rank_table_display();
    void sort_leading_board();
    json load_user();
    void input_manage();
public:
    leading_board();
    int show_leading_board();
};

*/



#endif

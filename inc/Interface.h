#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Item.h"
#include "json.hpp"
#include "LoginSystem.h"

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
    int run_sign_up();
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
    int run_sign_in();
};

//----------------------------------------------

#endif

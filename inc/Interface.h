#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Item.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>

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


#endif

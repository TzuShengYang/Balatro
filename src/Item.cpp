#include "../inc/Item.h"

using namespace std;

Item::Item(){}

Item::Item(unsigned int _item_index){
    item_index = _item_index;
    if (_item_index == 0) is_selected = true;
    else is_selected = false;
}

void Item::set_item_name(string _item_name){
    item_name = _item_name;
}

void Item::set_item_description(string _item_description){
    item_description =_item_description;
}

void Item::set_item_index(unsigned int _item_index){
    item_index = _item_index;
}

string Item::get_item_name(){
    return item_name;
}

string Item::get_item_description(){
    return item_description;
}

bool Item::get_item_status(){
    return is_selected;
}

unsigned int Item::get_item_index(){
    return item_index;
}

void Item::switch_item_status(){
    is_selected ^= true;
}

//Item
//-----------------------------------------------------------

card::card(){}

void card::set_card(int _suit, int _number){
    suit = _suit;
    number = _number;
}

unsigned int card::get_card_suit(){
    return suit;
}

unsigned int card::get_card_num(){
    return number;
} 

//card
//-----------------------------------------------------------



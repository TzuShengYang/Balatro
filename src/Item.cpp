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

void card::set_suit(int _suit){
    suit = _suit;
}

unsigned int Item::get_item_index(){
    return item_index;
}

void Item::switch_item_status(){
    is_selected ^= true;
}

//Item
//-----------------------------------------------------------

good::good(){
    amount = 2;
}

void good::set_goods(string _goods_name, unsigned int _price, unsigned int _amount){
    item_name  = _goods_name;
    price = _price;
    amount = _amount;
}

void good::buy(){
    amount--;
}

void good::gain(){
    amount++;
}

void good::use(){
    amount--;
}

unsigned int good::get_goods_price(){
    return price;
}

unsigned int good::get_goods_amount(){
    return amount;
}

string good::get_goods_name(){
    return item_name;
}

//goods
//-----------------------------------------------------------

card::card(){
    is_chosen = false;
    is_in_set = false;
}

void card::set_card(int _suit, int _number){
    suit = _suit;
    number = _number;
    is_chosen = false;
}

void card::switch_card_status(){
    is_chosen ^= true;
}

unsigned int card::get_card_suit(){
    return suit;
}

unsigned int card::get_card_num(){
    return number;
} 

void card::set_card_which_is_used(){
    is_in_set ^= true;
}

void card::set_num(int _num){
    number = _num;
}

bool card::card_is_chosen(){
    return is_chosen;
}

bool card::card_is_used(){
    return is_in_set;
}

//card
//-----------------------------------------------------------



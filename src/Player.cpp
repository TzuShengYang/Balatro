#include "../inc/Player.h"

using namespace std;

Player::Player(){}

void Player::set_username(string _username){
    username = _username;
}

void Player::set_user_currency(unsigned int _user_currency){
    user_currency = _user_currency;
}

void Player::set_user_experience(unsigned int _user_experience){
    user_experience = _user_experience;
}

void Player::set_user_level(unsigned int _user_level){
    user_level = _user_level;
}

void Player::set_user_highest(unsigned int _highest){
    highest = _highest;
}

string Player::get_username(){
    return username;
}

unsigned int Player::get_user_level(){
    return user_level;
}

unsigned int Player::get_user_currency(){
    return user_currency;
}

unsigned int Player::get_user_experience(){
    return user_experience;
}

unsigned int Player::get_user_highest(){
    return highest;
}

void Player::level_up(){
    user_level++;
}

void Player::gain_exp(int amount){
    user_experience += amount;
    if (to_level_up()) level_up();
}

void Player::gain_currency(int amount){
    user_currency += amount;
}

bool Player::buy(int amount){
    if (able_to_buy(amount)){
        user_currency -= amount;
        return true;
    } else {
        return false;
    }
}

bool Player::to_level_up(){
    if (user_experience >= user_level * user_level * 20){
        return true;
    } else {
        return false;
    }
}

bool Player::able_to_buy(int amount){
    return user_currency >= amount;
}

//Player
//------------------------------------------------------------

Inventory::Inventory(){
    amount = 0;
}

void Inventory::add_item(){

}

void Inventory::use_item(){

}

//Inventory
//------------------------------------------------------------
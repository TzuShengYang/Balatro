#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Item.h"
#include <string>
#include <vector>

using namespace std;

class Player{
private:
    string username;
    unsigned int user_level;
    unsigned int user_experience;
    unsigned int user_currency;
    unsigned int highest;
    
    bool able_to_buy(int amount);
    void level_up();
    bool to_level_up();
    
public:
    Player();
    
    void set_username(string _username);
    void set_user_currency(unsigned int _user_currency);
    void set_user_experience(unsigned int _user_experience);
    void set_user_level(unsigned int _user_level);
    void set_user_highest(unsigned int _highest);
    
    string          get_username();
    unsigned int    get_user_level();
    unsigned int    get_user_experience();
    unsigned int    get_user_currency();
    unsigned int    get_user_highest();
    
    void gain_exp(int amount);
    void gain_currency(int amount);
    bool buy(int amount);

};

class Inventory{
private:
    unsigned int amount;
    vector<good*> my_items;

public:
    Inventory();

    void add_item();
    void use_item();

};

#endif

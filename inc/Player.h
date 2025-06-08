#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Item.h"
#include <string>
#include <vector>

using namespace std;

class Player{
private:
    string username;
    string password;
    unsigned int user_level;
    unsigned int user_experience;
    unsigned int user_currency;
    unsigned int highest;
    double rate;
    
    bool able_to_buy(int amount);
    void level_up();
    bool to_level_up();
    
public:
    Player();
    
    void set_username(string _username);
    void set_password(string _password);
    void set_user_currency(unsigned int _user_currency);
    void set_user_experience(unsigned int _user_experience);
    void set_user_level(unsigned int _user_level);
    void set_user_highest(unsigned int _highest);
    void set_user_rate(double _rate);
    
    string          get_username();
    string          get_password();
    unsigned int    get_user_level();
    unsigned int    get_user_experience();
    unsigned int    get_user_currency();
    unsigned int    get_user_highest();
    double get_user_rate();
    
    void gain_exp(int amount);
    void gain_currency(int amount);
    bool buy(int amount);

};


#endif

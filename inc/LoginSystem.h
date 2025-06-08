#ifndef _LOGINSYSTEM_H_
#define _LOGINSYSTEM_H_

#include "json.hpp"
#include "Player.h"

#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
using json = nlohmann::json;

class login_system{
private:
    json json_user;
    const string filename = "users.json";
    
    string account;
    string password;
    unsigned int currency;
    unsigned int experience;
    unsigned int level;
    unsigned int highest;
    
    json load_user();
    void add_user();
    
public:
    login_system();
    void load_file();

    bool have_existed(string _username);
    bool password_is_valid(string _password);
    void save_user();
    void set_account(string _account);
    void set_password(string _password);
    void save_data(Player *_cur_player);

    string          get_username();
    string          get_password();
    unsigned int    get_user_level();
    unsigned int    get_user_experience();
    unsigned int    get_user_currency();
    unsigned int    get_user_highest();
    double          get_user_rate();

    void log_out();
};

#endif

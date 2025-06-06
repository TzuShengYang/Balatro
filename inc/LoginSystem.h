#ifndef _LOGINSYSTEM_H_
#define _LOGINSYSTEM_H_

#include "json.hpp"

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
    
    void load_file();
    json load_user();
    void add_user();
    void add_user(unsigned int _currency, unsigned int _experince, unsigned int _level);
   
public:
    login_system();

    bool have_existed(string _username);
    bool password_is_valid(string _password);
    void save_user();
    void set_account(string _account);
    void set_password(string _password);

    string          get_username();
    unsigned int    get_user_level();
    unsigned int    get_user_experience();
    unsigned int    get_user_currency();

    void sign_up();
    void sign_in();
};

#endif

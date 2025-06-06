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
    
    void load_file();
    json load_user();
    void add_user();
   
public:
    login_system();

    bool have_existed(string _username);
    bool password_is_valid(string _password);
    void save_user();
    void set_account(string _account);
    void set_password(string _password);

    void sign_up();
    void sign_in();
};

#endif

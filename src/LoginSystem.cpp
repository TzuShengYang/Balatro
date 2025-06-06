#include "../inc/LoginSystem.h"

using namespace std;
using json = nlohmann::json;

login_system::login_system(){
    load_file();
    json_user = load_user();
}

void login_system::load_file(){
    ifstream infile(filename);
    if (!infile.good()){
        ofstream outfile(filename);
        outfile << "{}";
        outfile.close();
    }
    infile.close();
}

json login_system::load_user(){
    ifstream infile(filename);
    if (!infile.is_open()) return json::object();
    json users;
    infile >> users;
    infile.close();
    return users;
}

void login_system::add_user(){
    json_user[account] = {
        {"password", password},
        {"currency", 0}
    };
}

void login_system::save_user(){
    add_user();
    ofstream outfile(filename);
    outfile << json_user.dump(4);
    outfile.close();
}

bool login_system::have_existed(string _username){
    return json_user.contains(_username);
}

bool login_system::password_is_valid(string _password){
    if (json_user[account]["password"] == _password){
        password = _password;
        return true;
    }

    return false;
}

void login_system::set_account(string _account){
    account = _account;
}

void login_system::set_password(string _password){
    password = _password;
}
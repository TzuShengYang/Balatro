#include "../inc/LoginSystem.h"

using namespace std;
using json = nlohmann::json;

login_system::login_system(){
    load_file();
    json_user = load_user();
}

void login_system::load_file(){
    json_user = load_user();
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
    json_user = load_user();
    json_user[account] = {
        {"password", password},
        {"currency", 0},
        {"experience", 0},
        {"highest", 0},
        {"level", 1},
        {"rate", 0.0}
    };
}



void login_system::save_data(Player *_cur_player){
    json_user = load_user();
    json_user[_cur_player -> get_username()]["currency"] = _cur_player -> get_user_currency();
    json_user[_cur_player -> get_username()]["experience"] = _cur_player -> get_user_experience();
    json_user[_cur_player -> get_username()]["highest"] = _cur_player -> get_user_highest();
    json_user[_cur_player -> get_username()]["level"] = _cur_player -> get_user_level();
    json_user[_cur_player -> get_username()]["rate"] = _cur_player -> get_user_rate();
    json_user[_cur_player -> get_username()]["password"] = _cur_player -> get_password();
}

void login_system::save_user(){
    add_user();
    ofstream outfile(filename);
    outfile << json_user.dump(4);
    outfile.close();
}

void login_system::log_out(){
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

string login_system::get_username(){
    return account;
}

unsigned int login_system::get_user_level(){
    return json_user[account]["level"];
}

unsigned int login_system::get_user_currency(){
    return json_user[account]["currency"];
}

unsigned int login_system::get_user_experience(){
    return json_user[account]["experience"];
}

unsigned int login_system::get_user_highest(){
    return json_user[account]["highest"];
}

double login_system::get_user_rate(){
    return json_user[account]["rate"];
}

string login_system::get_password(){
    return json_user[account]["password"];
}



#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>

using namespace std;

class Item{
protected:
    string item_name;
    string item_description;
    bool is_selected;
    unsigned int item_index;
    
public:
    Item();
    Item(unsigned int _item_index);
    
    void set_item_name(string _item_name);
    void set_item_description(string _item_description);
    void set_item_index(unsigned int _item_index);
    
    string get_item_name();
    string get_item_description();
    bool get_item_status();
    unsigned int get_item_index();
    
    void switch_item_status();
};

class goods: public Item{
    bool is_sold;
};

class card: public Item{
private:
    enum enum_suit{
        SPADE,
        HEART,
        DIAMOND,
        CLUB
    };
    int suit;
    int number;

public:
    card();

    void set_card(int _suit, int _number);

    unsigned int get_card_suit();
    unsigned int get_card_num();

};

#endif

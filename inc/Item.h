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

class good: public Item{
private:
    unsigned int price;
    unsigned int amount;

public:
    good();

    void set_goods(string _goods_name, unsigned int _price);
    bool is_sold();

    unsigned int get_goods_price();
    string get_goods_name();
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
    bool is_chosen;
    bool is_in_set;

public:
    card();

    void set_card(int _suit, int _number);

    unsigned int get_card_suit();
    unsigned int get_card_num();
    bool card_is_chosen();
    bool card_is_used();
    void set_card_which_is_used();
    void switch_card_status();

};

#endif

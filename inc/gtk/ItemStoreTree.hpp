#pragma once
#include <glib-2.0>
#include <iostream>

using std::string;


class ItemStoreTree : public Glib::Object
{
private:
    /* data */
    string name;
    string icon;
public:
    ItemStoreList();
    ~ItemStoreList();

    string get_name_file();
    string get_icon_file();
};

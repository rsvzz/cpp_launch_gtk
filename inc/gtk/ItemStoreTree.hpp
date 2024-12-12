#pragma once
#include <glibmm-2.68/glibmm.h>
#include <iostream>

using std::string;


class ItemStoreTree : public Glib::Object
{
private:
    /* data */
    string name;
    string icon;
public:
    ItemStoreTree();
    ~ItemStoreTree();

    string get_name_file();
    string get_icon_file();
};

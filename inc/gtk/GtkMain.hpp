#pragma once
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/textview.h>
#include "../model/PathItemList.hpp"

class GtkMain : public Gtk::Window
{
private:
    /* data */
    Gtk::Entry *txtSearch;
    Gtk::Box *box;
    Gtk::TextView *txtResult;
    PathItemList *p_files;
    void on_entry_changed();
    void on_entry_activate();

public:
    GtkMain();
    ~GtkMain();
};

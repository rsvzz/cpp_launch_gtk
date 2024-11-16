#pragma once
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/textview.h>

class GtkMain : public Gtk::Window
{
private:
    /* data */
    Gtk::Entry *txtSearch;
    Gtk::Box *box;
    Gtk::TextView *txtResult;
    void on_entry_changed();
    void on_entry_activate();

public:
    GtkMain();
    ~GtkMain();
};

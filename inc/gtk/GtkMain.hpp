#pragma once
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/textview.h>
#include <gtkmm-3.0/gtkmm/treeview.h>
#include <gtkmm-3.0/gtkmm/scrolledwindow.h>
#include <gtkmm-3.0/gtkmm/grid.h>
#include "../model/PathItemList.hpp"
#include "ModelColumns.hpp"

class GtkMain : public Gtk::Window
{
private:
    /* data */
    Gtk::Entry *txtSearch;
    Gtk::Box *box;
    PathItemList *p_files;
    Gtk::TreeView *tv_list_view;
    Gtk::ScrolledWindow *scroll;
    Gtk::Grid *grid;
    ModelColumns *columns;
    void on_entry_changed();
    void on_entry_activate();
    static void filter_by_list(PathItemList*, Glib::ustring, Gtk::TreeView*, ModelColumns*);

public:
    GtkMain();
    ~GtkMain();
};

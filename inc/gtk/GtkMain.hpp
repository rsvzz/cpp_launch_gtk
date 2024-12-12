#pragma once
#include <gtkmm-4.0/gtkmm/window.h>
#include <gtkmm-4.0/gtkmm/entry.h>
#include <gtkmm-4.0/gtkmm/box.h>
#include <gtkmm-4.0/gtkmm/textview.h>
#include <gtkmm-4.0/gtkmm/treeview.h>
#include <gtkmm-4.0/gtkmm/scrolledwindow.h>
#include <gtkmm-4.0/gtkmm/listitem.h>
#include <gtkmm-4.0/gtkmm/grid.h>
#include <gtkmm-4.0/gtkmm/columnview.h>
#include "../model/PathItemList.hpp"
#include <mutex>
//#include "ModelColumns.hpp"
#include "ModelItemColumn.hpp"
#include <giomm-2.68/giomm/liststore.h>
#include <iostream>
#include <memory>

using std::shared_ptr;

class GtkMain : public Gtk::Window
{
private:
    /* data */
    std::mutex *mtex;
    shared_ptr<Gtk::Entry> txtSearch;
    shared_ptr<Gtk::Box> box;
    shared_ptr<PathItemList> p_files;
    shared_ptr<Gtk::TreeView> tv_list_view;
    shared_ptr<Gtk::ScrolledWindow> scroll;
    shared_ptr<Gtk::Grid> grid;
    //shared_ptr<ModelColumns> columns;
    Glib::RefPtr<Gio::ListStore<ModelItemColumn>> model_list;
    shared_ptr<Gtk::ColumnView> cv_app;
    void on_entry_changed();
    void on_entry_activate();
    /// @brief crear label se reutiliza para todo column que use label
    /// @param list_item 
    /// @param halign 
    void on_setup_label_column(const Glib::RefPtr<Gtk::ListItem>& list_item, Gtk::Align halign);
    void on_bind_label_column_id(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_label_column_name(const Glib::RefPtr<Gtk::ListItem>& list_item);

    //void on_change_treeview();
    //void on_event_enter_select_treeview(const Glib::RefPtr<Gdk::Event>&, Gtk::TreeView*);
    static void filter_by_list(PathItemList*, Glib::ustring, Gtk::ColumnView*, std::mutex*);
    void on_select_item_column_view(guint);

public:
    GtkMain();
    ~GtkMain();
};

//void on_select_item_column_view(Gtk::ColumnView *cview);

#pragma once
#include <gtkmm-4.0/gtkmm/treemodel.h>
#include <gtkmm-4.0/gtkmm/treemodelcolumn.h>

class ModelColumns : public Gtk::TreeModel::ColumnRecord { 

    public: ModelColumns() { add(col_id); add(col_name); } 
    Gtk::TreeModelColumn<int> col_id; 
    Gtk::TreeModelColumn<Glib::ustring> col_name; 
};
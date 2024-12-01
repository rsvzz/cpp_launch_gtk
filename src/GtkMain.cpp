
#include "../inc/gtk/GtkMain.hpp"
#include <cstdlib>
#include <cstring>
#include <gtkmm-3.0/gtkmm.h>
#include <sigc++-2.0/sigc++/functors/mem_fun.h>
#include "../inc/gtk/ModelColumns.hpp"
#include <thread>
using std::thread;

GtkMain::GtkMain()
{
  p_files = new PathItemList("/usr/bin");
  this->set_border_width(3);
  this->set_resizable(false);
  this->set_decorated(false); // toolbar not visibility
  this->set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);

  Gtk::HeaderBar header;
  // header.set_title("Open C++/gtkmm-3.0");
  header.set_show_close_button(false);
  this->set_titlebar(header);

  txtSearch = new Gtk::Entry();
  txtSearch->set_placeholder_text("Application");
  txtSearch->set_size_request(300, 40);
  grid = new Gtk::Grid();
  grid->set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
  grid->set_column_spacing(5);
  grid->set_row_spacing(5);
  box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3);
  box->set_halign(Gtk::Align::ALIGN_CENTER);
  //box->set_valign(Gtk::Align::ALIGN_CENTER);
  box->set_size_request(350, 250);
  // box->set_homogeneous(true);
  txtSearch->set_hexpand(10);
  txtSearch->signal_changed().connect(
      sigc::mem_fun(*this, &GtkMain::on_entry_changed));
  txtSearch->signal_activate().connect(
      sigc::mem_fun(*this, &GtkMain::on_entry_activate));

  // agregando informacion TreeView

  tv_list_view = new Gtk::TreeView();
  columns = new ModelColumns;
  tv_list_view->append_column("ID", columns->col_id);
  tv_list_view->append_column("Name", columns->col_name);
  // tv_list_view->set_model(0);
  //  txtSearch->signal
  grid->add(*txtSearch);
  box->add(*tv_list_view);
  scroll = new Gtk::ScrolledWindow;
  //scroll->set_visible(false);
  scroll->set_size_request(350, 250);
  scroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  scroll->add(*box);
  grid->add(*scroll);
  // Agregar la caja al Gtk::ScrolledWindow scrolled_window.add(vbox);
  this->add(*grid);
  this->show_all_children();
}

GtkMain::~GtkMain()
{
  delete p_files;
}

void GtkMain::filter_by_list(PathItemList *files, Glib::ustring str, Gtk::TreeView *tr_view, ModelColumns *columns)
{
  files->get_filter_by_c_str(str);
  if (files->get_filter_status())
  {
    stack<PathItem *> *aux = new stack<PathItem *>(*files->get_filter_list());
    Glib::RefPtr<Gtk::ListStore> list_store = Gtk::ListStore::create(*columns);
    int i = 0;
          while (!aux->empty())
          {
            Gtk::TreeModel::Row row = *(list_store->append());
            auto _item = aux->top();
            i++;
            row[columns->col_id] = i;
            row[columns->col_name] = _item->name;
            aux->pop();
            if (i > 5)
            {
              break;
            }
          }
          tr_view->set_model(list_store); // Añadir columnas al TreeView
          
    delete aux;
  }
}

void GtkMain::on_entry_changed()
{
  // auto buffer = txtResult->get_buffer();
  int rq = txtSearch->get_text().length();
  if (rq == 1){
    thread th(filter_by_list, p_files, txtSearch->get_text(), tv_list_view, columns);
    th.detach();
  }
  else if (rq > 1){
    if (p_files->get_filter_status()){
      auto filter = p_files->get_filter_by_list(txtSearch->get_text());
      if (filter != nullptr)
      {
        stack<PathItem *> *aux = filter;
        Glib::RefPtr<Gtk::ListStore> list_store = Gtk::ListStore::create(*columns);
        int i = 0;
        while (!aux->empty())
        {
          Gtk::TreeModel::Row row = *(list_store->append());
          auto _item = aux->top();
          i++;
          row[columns->col_id] = i;
          row[columns->col_name] = _item->name;
          aux->pop();
          if (i > 5)
          {
            break;
          }
        }

        // Configurar el TreeView t
        tv_list_view->set_model(list_store); // Añadir columnas al TreeView
        delete aux;
      }
    }
  }
}

void GtkMain::on_entry_activate()
{
  // enter se valida haca
  if (txtSearch->get_text().length() == 0)
  {
    this->close();
    return;
  }
  auto app_name = txtSearch->get_text() + "&";
  // printf("enter %s \n", txtSearch->get_text().c_str());
  system(app_name.c_str());
  this->close();
}

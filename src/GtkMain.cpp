
#include "../inc/gtk/GtkMain.hpp"
#include <cstdlib>
#include <cstring>
#include <gtkmm-3.0/gtkmm.h>
#include <sigc++-2.0/sigc++/functors/mem_fun.h>

GtkMain::GtkMain() {
  this->set_border_width(10);
  this->set_resizable(false);
  this->set_decorated(false); // toolbar not visibility
  this->set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
  Gtk::HeaderBar header;
  // header.set_title("Open C++/gtkmm-3.0");
  header.set_show_close_button(false);
  this->set_titlebar(header);

  txtResult = new Gtk::TextView();
  txtResult->set_size_request(400, 260);
  txtResult->set_sensitive(false);
  txtSearch = new Gtk::Entry();
  txtSearch->set_placeholder_text("Application");
  txtSearch->set_size_request(400, 40);
  box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
  box->set_halign(Gtk::Align::ALIGN_CENTER);
  box->set_valign(Gtk::Align::ALIGN_CENTER);
  box->set_size_request(400, 300);
  // box->set_homogeneous(true);
  txtSearch->set_hexpand(10);
  txtSearch->signal_changed().connect(
      sigc::mem_fun(*this, &GtkMain::on_entry_changed));
  txtSearch->signal_activate().connect(
      sigc::mem_fun(*this, &GtkMain::on_entry_activate));

  // txtSearch->signal
  box->add(*txtSearch);
  box->add(*txtResult);
  this->add(*box);
  this->show_all_children();
  p_files = new PathItemList("/usr/bin");
}

GtkMain::~GtkMain() {
  delete p_files;
}

stack<PathItem*> *items;
void GtkMain::on_entry_changed() {
  auto buffer = txtResult->get_buffer();

  switch (txtSearch->get_text().length()) {
      case 0:{
          break;
      }
      case 1:{
          items = p_files->get_filter_by_c_str(txtSearch->get_text());
          if(items != nullptr){
              auto item = items->top();
              if(item != nullptr){
                  buffer->set_text(item->name);
                  txtResult->set_buffer(buffer);
              }
          }
      }
      default:{
          if(items != nullptr){
            auto filter = p_files->get_filter_by_list(items, txtSearch->get_text());
            if(filter != nullptr){
                auto item = filter->top();
                if(item != nullptr){
                    buffer->set_text(item->name);
                    txtResult->set_buffer(buffer);
                }
            }
        }
      }
  }

}

void GtkMain::on_entry_activate() {
  //enter se valida haca
  if (txtSearch->get_text().length() == 0)
    {
      this->close();
      return;
    }
  auto app_name = txtSearch->get_text() + "&";
  // printf("enter %s \n", txtSearch->get_text().c_str());
  int rs = system(app_name.c_str());
  this->close();
}

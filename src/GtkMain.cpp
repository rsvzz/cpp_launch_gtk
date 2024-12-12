#include "../inc/gtk/GtkMain.hpp"
#include <gtkmm-4.0/gtkmm/headerbar.h>
#include <gtkmm-4.0/gtkmm/treelistrow.h>
#include <gtkmm-4.0/gtkmm/eventcontrollerkey.h>
#include <gtkmm-4.0/gtkmm/singleselection.h>
#include <gtkmm-4.0/gtkmm/signallistitemfactory.h>
#include <gtkmm-4.0/gtkmm/label.h>
#include <gtkmm-4.0/gtkmm/cssprovider.h>
#include <gtkmm-4.0/gtkmm/stylecontext.h>
#include <gtkmm-4.0/gtkmm/styleprovider.h>
#include <gtkmm-4.0/gtkmm/widget.h>
#include <giomm-2.68/giomm/liststore.h>
#include <cstdlib>
#include <cstring>
#include <sigc++-3.0/sigc++/sigc++.h>
#include <iostream>
#include <memory>
#include <thread>
using std::dynamic_pointer_cast;
using std::make_shared;
using std::mutex;
using std::shared_ptr;
using std::thread;

/*
void on_select_item_column_view(Gtk::ColumnView *cview)
{
  auto selection_model = dynamic_cast<Gtk::SingleSelection *>(cview->get_model().get());
  if (selection_model)
  {
    auto item = dynamic_pointer_cast<ModelItemColumn>(selection_model->get_selected_item());
    std::cout << item->col_id << " -- " << item->col_name << std::endl;
  }

}
*/
/*
bool on_key_pressed(const Glib::RefPtr<Gdk::Event> &event, Gtk::TreeView *treeview)
{

  auto key_event = std::dynamic_pointer_cast<Gdk::EventKey>(event);
  if (key_event && key_event->get_keyval() == GDK_KEY_Return)
  // Verifica si la tecla presionada es "Enter"
   auto selection = treeview->get_selection();
   if (auto iter = selection->get_selected())
   {
    auto path = treeview->get_model()->get_path(*iter);
    auto column = treeview->get_column(0);
    treeview->row_activated(path, *column); // Emula el doble clic en la fila seleccionada } return true; } return false; }
   }

  return false;
}
*/
GtkMain::GtkMain()
{
  mtex = new mutex;
  p_files = make_shared<PathItemList>("/usr/bin");
  // this->set_border_width(3);
  this->set_resizable(false);
  this->set_decorated(false); // toolbar not visibility
  // this->set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
  this->set_halign(Gtk::Align::CENTER);
  this->set_halign(Gtk::Align::CENTER);
  this->set_size_request(310,300);

  Gtk::HeaderBar header;

  this->set_titlebar(header);
  txtSearch = make_shared<Gtk::Entry>();

  //definicendo class de css para el control
  this->add_css_class("mywindow");
  txtSearch->set_name("myEntry");

  txtSearch->set_placeholder_text("Application :");
  txtSearch->set_size_request(300, 40);
  //cargando css provider
  auto css_provider = Gtk::CssProvider::create();
 
  //#if HAS_STYLE_PROVIDER_ADD_PROVIDER_FOR_DISPLAY
   // Gtk::StyleProvider::add_provider_for_display(get_display(), css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  //#else
    Gtk::StyleContext::add_provider_for_display(get_display(), css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  //#endif
   css_provider->load_from_path("styles/main.css");

   
  grid = make_shared<Gtk::Grid>();
  grid->set_orientation(Gtk::Orientation::VERTICAL);
  grid->set_column_spacing(5);
  grid->set_row_spacing(5);
  box = make_shared<Gtk::Box>(Gtk::Orientation::VERTICAL, 3);
  box->set_halign(Gtk::Align::CENTER);
  // box->set_valign(Gtk::Align::ALIGN_CENTER);
  box->set_size_request(350, 250);
  // box->set_homogeneous(true);
  txtSearch->set_hexpand(10);
  txtSearch->signal_changed().connect(sigc::mem_fun(*this, &GtkMain::on_entry_changed));
  txtSearch->signal_activate().connect(sigc::mem_fun(*this, &GtkMain::on_entry_activate));

  // cv_app->signal_activate().connect(sigc::mem_fun(*this, &GtkMain::on_select_item_column_view));
  // selection_model->signal_selection_changed().connect(sigc::mem_fun(*this, &GtkMain::on_select_item_column_view));

  // agregando informacion TreeView
  /*
  tv_list_view = make_shared<Gtk::TreeView>();
  auto tv_select = tv_list_view->get_selection();
  tv_select->set_mode(Gtk::SelectionMode::SINGLE);
  tv_select->signal_changed().connect(sigc::mem_fun(*this, &GtkMain::on_change_treeview));
  */
  cv_app = make_shared<Gtk::ColumnView>();
  //cv_app->add_css_class("data-table"); // high density table
  cv_app->set_reorderable(true);
  cv_app->signal_activate().connect(sigc::mem_fun(*this, &GtkMain::on_select_item_column_view));
  /*
  model_list = Gio::ListStore<ModelItemColumn>::create();
  //model_list->append(ModelItemColumn::create(1,"alacritty")); //llamar para llenar

   auto selection_model = Gtk::SingleSelection::create(model_list);
  selection_model->set_autoselect(false);
  selection_model->set_can_unselect(true);
  cv_app->set_model(selection_model);
  cv_app->add_css_class("data-table"); // high density table

  cv_app->set_reorderable(true);
  */
  // Id column
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
                                                           &GtkMain::on_setup_label_column),
                                             Gtk::Align::END));
  factory->signal_bind().connect(
      sigc::mem_fun(*this, &GtkMain::on_bind_label_column_id));
  auto column_id = Gtk::ColumnViewColumn::create("ID", factory);
  column_id->set_fixed_width(40);
  cv_app->append_column(column_id);

  // Name column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
                                                           &GtkMain::on_setup_label_column),
                                             Gtk::Align::START));
  factory->signal_bind().connect(
      sigc::mem_fun(*this, &GtkMain::on_bind_label_column_name));

  auto column_name = Gtk::ColumnViewColumn::create("Name", factory);
  column_name->set_fixed_width(300); // width column
  cv_app->append_column(column_name);
  // Conectar la señal de fila activada
  // tv_list_view->signal_row_activated().connect(sigc::ptr_fun(&on_row_activated));
  // Crear y agregar un controlador de eventos de teclado
  // auto key_controller = Gtk::EventControllerKey::create();
  // Gtk::TreeView treeview = shared_ptr<Gtk::TreeView>(*(tv_list_view).get()));
  // key_controller->signal_key_pressed().connect(sigc::bind(sigc::ptr_fun(&on_key_pressed), &treeview), false);
  // key_controller->signal_key_pressed().connect(sigc::bind(sigc::mem_fun(*this, &GtkMain::on_event_enter_select_treeview)),tv_list_view.get(), false);
  // tv_list_view->add_controller(key_controller);
  // tv_list_view->signal_row_activated

  // tv_list_view->signal_ch().connect(sigc::mem_fun(*this, &GtkMain::on_change_treeview));
  // tv_list_view->set_model(Gtk::SELECTION_SINGLE);
  // columns = make_shared<ModelColumns>();
  // tv_list_view->append_column("Id", columns->col_id);
  // tv_list_view->append_column("Name", columns->col_name);
  //  tv_list_view->set_model(0);
  //   txtSearch->signal
  grid->attach(*txtSearch, 0, 0, 1, 1);
  box->append(*cv_app);
  scroll = make_shared<Gtk::ScrolledWindow>();
  // scroll->set_visible(false);
  scroll->set_size_request(350, 250);
  scroll->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  scroll->set_child(*box);
  grid->attach(*scroll, 0, 1, 1, 1);
  // Agregar la caja al Gtk::ScrolledWindow scrolled_window.add(vbox);
  this->set_child(*grid);
  this->show();
}

void GtkMain::on_setup_label_column(const Glib::RefPtr<Gtk::ListItem> &list_item, Gtk::Align halign)
{
  auto wid_lbl = Gtk::make_managed<Gtk::Label>("", halign);
  wid_lbl->add_css_class("cv-lbl-view");
  list_item->set_child(*wid_lbl);
}

void GtkMain::on_bind_label_column_id(const Glib::RefPtr<Gtk::ListItem> &list_item)
{
  auto col = std::dynamic_pointer_cast<ModelItemColumn>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Glib::ustring::format(col->col_id));
}

void GtkMain::on_bind_label_column_name(const Glib::RefPtr<Gtk::ListItem> &list_item)
{
  auto col = std::dynamic_pointer_cast<ModelItemColumn>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Glib::ustring::format(col->col_name));
}

GtkMain::~GtkMain()
{
}
void GtkMain::filter_by_list(PathItemList *files, Glib::ustring str, Gtk::ColumnView *cview, std::mutex *_mtx)
{
  _mtx->lock();
  files->get_filter_by_c_str(str); // busca si es primer caracter.

  auto _filter = files->get_filter_by_list(str); // busca la lista previamente filtrado por el primer caracter
  if (_filter != NULL)
  {

    auto model = Gio::ListStore<ModelItemColumn>::create();
    auto selection_model = Gtk::SingleSelection::create(model);
    // auto selection_model = dynamic_cast<Gtk::SingleSelection*>(cview->get_model().get());
    // auto model = dynamic_cast<Gio::ListStore<ModelItemColumn>*>(selection_model->get_model().get());
    stack<PathItem *> *aux = new stack<PathItem *>(*_filter);
    int i = 0;
    while (!aux->empty())
    {
      auto _item = aux->top();
      i++;
      model->append(ModelItemColumn::create(i, _item->name));
      aux->pop();
      if (i > 9)
      {
        break;
      }
    }

    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);

    cview->set_model(selection_model); // Añadir columnas al TreeView

    delete aux;
    aux = nullptr;
  }
  _mtx->unlock();
}

void GtkMain::on_select_item_column_view(guint position)
{

  auto selection_model = dynamic_cast<Gtk::SingleSelection *>(cv_app->get_model().get());
  auto model = dynamic_cast<Gio::ListStore<ModelItemColumn> *>(selection_model->get_model().get());
  auto item = dynamic_pointer_cast<ModelItemColumn>(model->get_item(position));

  txtSearch->set_text(item->col_name);
  // txtSearch->grab_focus();
  on_entry_activate();
  // txtSearch->set_focus_on_click()
  // txtSearch->set_text(item->col_name);
  // std::cout<<"llega "<<item->col_name<<" < posicion"<<std::endl;
}

void GtkMain::on_entry_changed()
{
  // auto buffer = txtResult->get_buffer();
  int rq = txtSearch->get_text().length();
  switch (rq)
  {
  case 0:
  {
    cv_app->set_model(NULL);
    p_files->set_key_first();
  }
  break;
  default:
  {
    // auto model = Gio::ListStore<ModelItemColumn>::create();
    //  uso de punteros inteligentes con shared_ptr get se extrae para llamar puntero normal.
    thread th(filter_by_list, p_files.get(), txtSearch->get_text(), cv_app.get(), mtex);
    th.join(); // detach no actualiza ui

    // auto selection = cv_app->get_model();

    // if(select != nullptr)
    // selection->signal_selection_changed().connect(sigc::mem_fun(*this, &GtkMain::on_select_item_column_view));
    // auto selection_model = cv_app->get_model().get();
    // selection_model->signal_selection_changed().connect(sigc::mem_fun(*this, &GtkMain::on_select_item_column_view));
  }
  break;
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

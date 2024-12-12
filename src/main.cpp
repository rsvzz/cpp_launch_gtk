/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cpplite/CPPTemplate.cpp to edit this template
 */
#include <cstdlib>
#include <iostream>
#include "../inc/gtk/GtkMain.hpp"
#include <gtkmm-4.0/gtkmm/application.h>

int main (int argc, char* argv[]){
    /*
    std::string path = "/usr/bin";

    stack<PathItem> *files = new stack<PathItem>;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            //cout<<entry.path().filename().c_str()<<endl;
            if(!entry.is_directory()){
                PathItem item;
                item.path = string(entry.path().c_str());
                item.name = string(entry.path().filename().c_str());
                item.extention = string(entry.path().extension().c_str());
                files->push(item);

            }
        }
    } catch (const fs::filesystem_error& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }

    PathItemList obj(files);
    auto nlist = obj.get_filter_by_c_str("al");
    if(nlist != NULL){
        auto app = nlist->top();
        cout<<app.name<<" top --> "<<nlist->size()<<endl;
    }
    */
    auto app = Gtk::Application::create("org.gtkmm.mytestapp", Gio::Application::Flags::NONE);
    return app->make_window_and_run<GtkMain>(argc, argv);
   
}

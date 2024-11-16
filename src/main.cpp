/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cpplite/CPPTemplate.cpp to edit this template
 */
#include <cstdlib>
#include <iostream>
#include "../inc/gtk/GtkMain.hpp"
#include <gtkmm-3.0/gtkmm/application.h>

int main (int argc, char* argv[]){
    /*
    std::cout<<"This's a test"<<std::endl;

    int rs = system("rofi -show run");
    if(rs == 0){
        std::cout<<"open"<<std::endl;
    }
    */

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.mywin");
    GtkMain mywin; 
    return app->run(mywin);
   
}

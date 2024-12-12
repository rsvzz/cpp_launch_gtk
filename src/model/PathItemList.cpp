#include "../../inc/model/PathItemList.hpp"
#include <cstddef>
#include <iostream>
#include <thread>

void PathItemList::read_path_files(stack<PathItem*> *items, const char* path){
   try {
    for (const auto &entry : fs::directory_iterator(path)) {
      // cout<<entry.path().filename().c_str()<<endl;
      if (!entry.is_directory()) {
        PathItem *item = new PathItem;
        item->path = string(entry.path().c_str());
        item->name = string(entry.path().filename().c_str());
        item->extention = string(entry.path().extension().c_str());
        items->push(item);
      }
    }
  } catch (const fs::filesystem_error &err) {
    std::cerr << "Error: " << err.what() << std::endl;
  }

}
PathItemList::PathItemList(const char *path) {
  files = new stack<PathItem *>;
  std::thread thr(read_path_files, files, path);
  thr.detach();
 
}

PathItemList::~PathItemList() {
  delete files;
  files = nullptr;
}
stack<PathItem*> *PathItemList::exec_by_filter(stack<PathItem *> *list,string str) {
  stack<PathItem *> *item = new stack<PathItem *>(*list);
  stack<PathItem*> *filtro = new stack<PathItem*>;
  while (!item->empty()) {
    /* code */
    auto info = item->top();
    if (info->name.length() >= str.length()) {
      string find = "";
      for (size_t i = 0; i < info->name.length(); i++) {
        /* code */
        if (find.length() < str.length()) {
          // listando los caracteres requerios por el filtro
          if (str.at(i) == info->name.at(i)) {
            find += info->name.at(i);
          } else {
            break;
          }
        } else {
          break;
        }
      }
      if (str.compare(find.c_str()) == 0) {
        // std::cout<<"Entro >> "<<info.name<<std::endl;
        filtro->push(info);
      }
    }
    item->pop();
  }
  delete item;
  item = nullptr;
  if (filtro->size() > 0) {
    return filtro;
  } else {
    return nullptr;
  }
}

void PathItemList::get_filter_by_c_str(string str) {
  if(str.length() == 1){
    if(!get_first_key(str.c_str())){
      key = const_cast<char*>(str.c_str());
      //std::cout<<"asig :"<<str<<std::endl;
      filter = nullptr;
      filter = exec_by_filter(files, str);
    }
    else{
      //std::cout<<str<<" -> la misma"<<std::endl;
    }
  }
  else{
      //std::cout<<str<<" -> mas letras"<<std::endl;
  }
   
}
bool PathItemList::get_filter_status(){
  if(filter != nullptr)
    return false;
    
  if(filter->size() > 0){
    return true;
  }

  return false;
}

stack<PathItem *>* PathItemList::get_filter_by_list(string str) {
  if(str.length() == 1){
    return filter;
  }
  else{
     //std::cout<<str<<" entro a filtrar :)"<<std::endl;
     return exec_by_filter(filter, str);
  }
   
}

bool PathItemList::get_first_key(const char* _key){
  if(key != nullptr){
    if(*key == *_key)
      return true;
    else
      return false;
  }
  return false;
}

void PathItemList::set_key_first(){
  key = nullptr;
}

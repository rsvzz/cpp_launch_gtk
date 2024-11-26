#include "../../inc/model/PathItemList.hpp"
#include <cstddef>
#include <iostream>

PathItemList::PathItemList(const char *path) {
  files = new stack<PathItem *>;
  try {
    for (const auto &entry : fs::directory_iterator(path)) {
      // cout<<entry.path().filename().c_str()<<endl;
      if (!entry.is_directory()) {
        PathItem *item = new PathItem;
        item->path = string(entry.path().c_str());
        item->name = string(entry.path().filename().c_str());
        item->extention = string(entry.path().extension().c_str());
        files->push(item);
      }
    }
  } catch (const fs::filesystem_error &err) {
    std::cerr << "Error: " << err.what() << std::endl;
  }
}

PathItemList::~PathItemList() {
  delete files;
  files = nullptr;
}
stack<PathItem *> *PathItemList::exec_by_filter(stack<PathItem *> *list,
                                                string str) {
  stack<PathItem *> *item = new stack<PathItem *>(*list);
  stack<PathItem *> *filtro = new stack<PathItem *>;
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

stack<PathItem *> *PathItemList::get_filter_by_c_str(string str) {
  return exec_by_filter(files, str);
}

stack<PathItem *> *PathItemList::get_filter_by_list(stack<PathItem *> *list,
                                                    string str) {
  return exec_by_filter(list, str);
}

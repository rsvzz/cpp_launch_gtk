#pragma once
#include <filesystem>
#include <iostream>
#include <stack>
using std::stack;
using std::string;
namespace fs = std::filesystem;

struct PathItem {
  /* data */
  string name;
  string path;
  string extention;
};

class PathItemList {
private:
  /* data */
  std::string path;
  char* key;
  stack<PathItem *> *files, *filter;
  stack<PathItem*>* exec_by_filter(stack<PathItem*>*, string);
  static void read_path_files(stack<PathItem*>*, const char*);
  /// @brief validar si es primera key
  /// @param  primer char
  /// @return true valid false nofund
  bool get_first_key(const char*);
  
public:
  PathItemList(const char *);
  ~PathItemList();
  /// @brief Se llama cuando el la primera letra
  /// @param  find string
  void get_filter_by_c_str(string);
  /// @brief Si existe registros
  /// @return 
  bool get_filter_status();
  /// @brief Permite filtrar con el primer caracter agregado por primera vez
  /// @param  
  /// @return 
  stack<PathItem *>* get_filter_by_list(string);
  /// @brief reiniciar validacion primer caracter
  void set_key_first();
  
};

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
  stack<PathItem *> *files, *filter;
  stack<PathItem*>* exec_by_filter(stack<PathItem*>*, string);
  static void read_path_files(stack<PathItem*>*, const char*);
public:
  PathItemList(const char *);
  ~PathItemList();
  void get_filter_by_c_str(string);
  bool get_filter_status();
  stack<PathItem*>* get_filter_list();
  stack<PathItem *>* get_filter_by_list(string);
};

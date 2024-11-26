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
  stack<PathItem *> *files;
  stack<PathItem*>* exec_by_filter(stack<PathItem*>*, string);
public:
  PathItemList(const char *);
  ~PathItemList();
  stack<PathItem *> *get_filter_by_c_str(string);
  stack<PathItem *> *get_filter_by_list(stack<PathItem *>*, string);
};

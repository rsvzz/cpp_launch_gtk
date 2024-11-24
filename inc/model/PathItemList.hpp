#include <iostream>
#include <stack>

struct PathItem
{
    /* data */
    std::string name;
    std::string path;
    std::string extention;
};

class PathItemList
{
private:
    /* data */
    std::stack<PathItem> *items;
public:
    PathItemList(std::stack<PathItem>*);
    ~PathItemList();

    std::stack<PathItem>* get_filter_by_c_str(std::string);

};

PathItemList::PathItemList(std::stack<PathItem>* data)
{
    items = data;
}

PathItemList::~PathItemList()
{
}

std::stack<PathItem>* PathItemList::get_filter_by_c_str(std::string str){
    std::stack<PathItem> *item =  new std::stack<PathItem>(*items);
    std::stack<PathItem> *filtro = new std::stack<PathItem>;
    while (!item->empty())
    {
        /* code */
        auto info = item->top();
        if(info.name.length() >= str.length())
        {
          std::string find = "";
          for (size_t i = 0; i < info.name.length(); i++)
          {
              /* code */
              if(find.length() < str.length()){
                  //listando los caracteres requerios por el filtro
                  find += info.name.at(i);
              }
              else{
                  break;
              }

          }
          if(str.compare(find.c_str()) == 0){
              //std::cout<<"Entro >> "<<info.name<<std::endl;
              filtro->push(info);
          }
      }
      item->pop();
    }

    return filtro;
}

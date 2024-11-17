#include <stack>
#include <iostream>
using namespace std;

struct ItemsFile
{
    const char* name;
    const char* image;
};

struct PathFiles
{
    /* data */
    const char* path;
    stack<ItemsFile> *items;
};


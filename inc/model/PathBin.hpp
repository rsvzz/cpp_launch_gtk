#pragma once
#include "Items.hpp"
/*
    Read to Directory the application
*/
class PathBin
{
private:
public:
    PathBin();
    ~PathBin();
    PathFiles* get_path_name(const char*);
};


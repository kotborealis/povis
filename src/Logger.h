#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "utils/to_string.h"

#define info(str) log(__FILE__,__LINE__,"info",TO_STRING(str));
#define warn(str) log(__FILE__,__LINE__,"warn",TO_STRING(str));
#define error(str) log(__FILE__,__LINE__,"error",TO_STRING(str));
#define note(str) log(__FILE__,__LINE__,"note",TO_STRING(str));

namespace pse{

class Logger{
public:
    static void log(const char* file, int line, const char* type, std::string text){
        std::cout << "[" << type << "] " << text << std::endl;
    }
};

}
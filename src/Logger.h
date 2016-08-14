#pragma once

#include <string>
#include <iostream>
#include <sstream>

#define SSTR(x) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define info(str) log(__FILE__,__LINE__,"info",SSTR(str));
#define warn(str) log(__FILE__,__LINE__,"warn",SSTR(str));
#define error(str) log(__FILE__,__LINE__,"error",SSTR(str));

namespace PovisEngine{

class Logger{
public:
    static void log(const char* file, int line, const char* type, std::string text){
        std::cout << "{" << file << " at " << line << "}" << "[" << type << "] " << text << std::endl;
    }
};

}
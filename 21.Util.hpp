#pragma once

#include <iostream>
#include <string>

class Util
{
public:
    // XXXX XXX XXX\r\nYYYYY
    static std::string getOneLine(std::string &buffer, const std::string &sep)
    {
        auto pos = buffer.find(sep);
        if(pos == std::string::npos) return "";
        std::string sub = buffer.substr(0, pos);
        buffer.erase(0, sub.size()+sep.size());
        return sub;
    }
};

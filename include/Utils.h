//
// Created by sam on 2018/12/8.
//

#ifndef DONGMENDBAUTOTEST_UTILS_H
#define DONGMENDBAUTOTEST_UTILS_H

#include <string>

using namespace std;


class Utils{
public:
    static string  ws2s(const wstring& ws);
    static wstring  s2ws(const string& s);

    template<typename ... Args>
    static string string_format( const std::string& format, Args ... args );
};
#endif //DONGMENDBAUTOTEST_UTILS_H

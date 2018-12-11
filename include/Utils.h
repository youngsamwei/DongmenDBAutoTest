//
// Created by sam on 2018/12/8.
//

#ifndef DONGMENDBAUTOTEST_UTILS_H
#define DONGMENDBAUTOTEST_UTILS_H

#include <string>

/* wstring 转换为 char * 的宏*/
#define WS2CHAR(x)  (Utils::ws2s(x).c_str())
/* wstring 转换为 string*/
#define WS2S(x)  (Utils::ws2s(x))


using namespace std;


class Utils{
public:
    static string  ws2s(const wstring& ws);
    static wstring  s2ws(const string& s);

    static string FormatString(const char *lpcszFormat,...);
    static wstring FormatWString(const wchar_t *lpcwszFormat,...);

    static wstring findFileNameEndWith(wstring dir, wstring name);
    static int copyDir(wstring src_dir, wstring dest_dir);
    static int removeDirW(const wchar_t *dirPath);
};


#endif //DONGMENDBAUTOTEST_UTILS_H

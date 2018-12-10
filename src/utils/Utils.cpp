//
// Created by sam on 2018/12/8.
//

#include <memory.h>
#include <memory>
#include <cstdarg>
#include "Utils.h"

string Utils::ws2s(const wstring &ws) {
    string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";

    setlocale(LC_ALL, "chs");

    const wchar_t *_Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest, 0, _Dsize);
    wcstombs(_Dest, _Source, _Dsize);
    string result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, curLocale.c_str());

    return result;
}

 wstring Utils::s2ws(const string &s) {
    setlocale(LC_ALL, "chs");

    const char *_Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest, _Source, _Dsize);
    wstring result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, "C");

    return result;
}

string Utils::FormatString(const char *lpcszFormat,...)
{
    char *pszStr = NULL;
    if (NULL != lpcszFormat)
    {
        va_list marker = NULL;
        va_start(marker, lpcszFormat); //初始化变量参数
        size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //获取格式化字符串长度
        pszStr = new char[nLength];
        memset(pszStr, '\0', nLength);
        _vsnprintf_s(pszStr, nLength, nLength, lpcszFormat, marker);
        va_end(marker); //重置变量参数
    }
    string strResult(pszStr);
    delete[]pszStr;
    return strResult;
}

wstring Utils::FormatWstring(const wchar_t *lpcwszFormat,...)
{
    wchar_t *pszStr = NULL;
    if (NULL != lpcwszFormat)
    {
        va_list marker = NULL;
        va_start(marker, lpcwszFormat); //初始化变量参数
        size_t nLength = _vscwprintf(lpcwszFormat, marker) + 1; //获取格式化字符串长度
        pszStr = new wchar_t[nLength];
        memset(pszStr, L'\0', nLength);
        _vsnwprintf_s(pszStr, nLength, nLength, lpcwszFormat, marker);
        va_end(marker); //重置变量参数
    }
    wstring strResult(pszStr);
    delete[]pszStr;
    return strResult;
}

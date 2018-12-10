//
// Created by sam on 2018/12/8.
//

#include <memory.h>
#include <memory>
#include <cstdarg>
#include <io.h>
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

wstring Utils::FormatWString(const wchar_t *lpcwszFormat,...)
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

/*在指定的文件夹中查找以name结尾的文件名称，应对云班课导出文件改名问题。只查找dir指定的文件夹，不查找更深层次的文件夹
 * TODO:处理多个匹配文件的情况
 * */
wstring Utils::findFileNameEndWith(wstring dir, wstring name) {
    struct _wfinddata_t fb;   //查找相同属性文件的存储结构体
    wstring path;
    wstring resultone = L"";

    long handle;
    int noFile;             //对系统隐藏文件的处理标记

    noFile = 0;
    handle = 0;

    path = dir + L"/*";
    //制作路径

    handle = _wfindfirst(path.c_str(), &fb);
    //找到第一个匹配的文件
    if (handle != 0) {
        //当可以继续找到匹配的文件，继续执行
        while (0 == _wfindnext(handle, &fb)) {
            //属性值为16，则说明是文件夹
            if (fb.attrib != 16) {
                wstring fb_name = fb.name;
                if (fb_name.length() >= name.length()) {
                    wstring px = fb_name.substr(fb_name.length() - name.length(), fb_name.length());
                    int r = wcscmp(px.c_str(), name.c_str());
                    if (r == 0) {
                        resultone = fb.name;
                        break;
                    }
                }
            }

        }
        //关闭文件夹。找这个函数找了很久，标准c中用的是closedir
        //经验介绍：一般产生Handle的函数执行后，都要进行关闭的动作。
        _findclose(handle);
    }
    return resultone;
};

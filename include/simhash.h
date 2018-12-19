#ifndef SIMHASH_H
#define SIMHASH_H

#include <string.h>

#include <map>

#define SIMHASH_BIT 64

typedef unsigned long int ul_int;

using namespace std;

class SimHash{
public:
    static ul_int sh_hash(const char *arKey, unsigned int nKeyLength);
    static ul_int sh_simhash(const char *tokens[], unsigned int length);

    static ul_int sh_simhash(vector<char *> tokens);

    /*计算文本文件的simhash值*/
    static ul_int simhash_file(const char *fileName);

    static ul_int simhash_file(const char *fileName, map<string, int> *stopWords);

};
#endif

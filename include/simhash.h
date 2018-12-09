#ifndef SIMHASH_H
#define SIMHASH_H

#include <string.h>

#define SIMHASH_BIT 64

typedef unsigned long int ul_int;

class SimHash{
public:
    static ul_int sh_hash(const char *arKey, unsigned int nKeyLength);
    static ul_int sh_simhash(const char *tokens[], unsigned int length);

};
#endif

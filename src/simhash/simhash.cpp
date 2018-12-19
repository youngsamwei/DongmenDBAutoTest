
#include <Utils.h>
#include <fstream>
#include <vector>
#include <cstring>
#include "simhash.h"


ul_int SimHash::sh_hash(const char *arKey, unsigned int nKeyLength) {
    register ul_int hash = 5381;

    for (; nKeyLength >= 8; nKeyLength -= 8) {
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
    }
    switch (nKeyLength) {
        case 7:
            hash = ((hash << 5) + hash) + *arKey++;
        case 6:
            hash = ((hash << 5) + hash) + *arKey++;
        case 5:
            hash = ((hash << 5) + hash) + *arKey++;
        case 4:
            hash = ((hash << 5) + hash) + *arKey++;
        case 3:
            hash = ((hash << 5) + hash) + *arKey++;
        case 2:
            hash = ((hash << 5) + hash) + *arKey++;
        case 1:
            hash = ((hash << 5) + hash) + *arKey++;
            break;
        case 0:
            break;
    }

    return hash;
}

ul_int SimHash::sh_simhash(const char *tokens[], unsigned int length) {
    float hash_vector[SIMHASH_BIT];
    memset(hash_vector, 0, SIMHASH_BIT * sizeof(float));
    ul_int token_hash = 0;
    ul_int simhash = 0;
    int current_bit = 0;

    for (int i = 0; i < length; i++) {
        token_hash = sh_hash(tokens[i], strlen(tokens[i]));
        for (int j = SIMHASH_BIT - 1; j >= 0; j--) {
            current_bit = token_hash & 0x1;
            if (current_bit == 1) {
                hash_vector[j] += 1;
            } else {
                hash_vector[j] -= 1;
            }
            token_hash = token_hash >> 1;
        }
    }

    for (int i = 0; i < SIMHASH_BIT; i++) {
        if (hash_vector[i] > 0) {
            simhash = (simhash << 1) + 0x1;
        } else {
            simhash = simhash << 1;
        }
    }

    return simhash;
}


ul_int SimHash::sh_simhash(vector<char *> tokens) {
    float hash_vector[SIMHASH_BIT];
    memset(hash_vector, 0, SIMHASH_BIT * sizeof(float));
    ul_int token_hash = 0;
    ul_int simhash = 0;
    int current_bit = 0;

    for (int i = 0; i < tokens.size(); i++) {
        token_hash = sh_hash(tokens[i], strlen(tokens[i]));
        for (int j = SIMHASH_BIT - 1; j >= 0; j--) {
            current_bit = token_hash & 0x1;
            if (current_bit == 1) {
                hash_vector[j] += 1;
            } else {
                hash_vector[j] -= 1;
            }
            token_hash = token_hash >> 1;
        }
    }

    for (int i = 0; i < SIMHASH_BIT; i++) {
        if (hash_vector[i] > 0) {
            simhash = (simhash << 1) + 0x1;
        } else {
            simhash = simhash << 1;
        }
    }

    return simhash;
}

ul_int SimHash::simhash_file(const char *fileName) {
    setlocale(LC_ALL, "Chinese-simplified");
    fstream f(fileName);//创建一个fstream文件流对象
    vector<char *> words; //创建一个vector<string>对象
    string line; //保存读入的每一行
    char seps[] = " ;#　\t.()*:,!=<>/'\\\"";//空格,分号，#，tab键
    while (getline(f, line))//会自动把\n换行符去掉
    {
        char *token;

        char *strTemp = (char *) line.c_str();

        token = std::strtok(strTemp, seps);
        while (token != NULL) {
            words.push_back(token);
            token = std::strtok(NULL, seps);
        }

    }

    f.close();
    return SimHash::sh_simhash(words);
};


ul_int SimHash::simhash_file(const char *fileName, map<string, int> *stopWords) {
    setlocale(LC_ALL, "Chinese-simplified");
    fstream f(fileName);//创建一个fstream文件流对象
    vector<char *> words; //创建一个vector<string>对象
    string line; //保存读入的每一行
    char seps[] = " ;#　\t.()*:,!=<>/'\\\"";//空格,分号，#，tab键
    while (getline(f, line))//会自动把\n换行符去掉
    {
        char *token;

        char *strTemp = (char *) line.c_str();

        token = std::strtok(strTemp, seps);
        while (token != NULL) {
            /*不在stopwords中*/
            if (stopWords->count(token) > 0) {

            }else{
                words.push_back(token);
            }
            token = std::strtok(NULL, seps);
        }

    }

    f.close();
    return SimHash::sh_simhash(words);
};
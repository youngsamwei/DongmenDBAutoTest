//
// Created by sam on 2018/12/19.
//

#include "test_execution_config.h"

pair<string, int> stopWordsPairArray[] =
        {
                make_pair("char", 0),
                make_pair("short ", 0),
                make_pair("int", 0),
                make_pair("long ", 0),
                make_pair("float", 0),
                make_pair("double ", 0),
                make_pair("signed", 0),
                make_pair("unsigned", 0),
                make_pair("enum ", 0),
                make_pair("struct", 0),
                make_pair("union", 0),
                make_pair("void ", 0),
                make_pair("typedef ", 0),
                make_pair("sizeof", 0),

                make_pair("for", 0),
                make_pair("do ", 0),
                make_pair("while ", 0),
                make_pair("break", 0),
                make_pair("continue", 0),
                make_pair("if", 0),
                make_pair("else ", 0),
                make_pair("goto", 0),

                make_pair("switch ", 0),
                make_pair("case", 0),
                make_pair("default", 0),

                make_pair("auto ", 0),
                make_pair("register", 0),
                make_pair("static ", 0),
                make_pair("const ", 0),
                make_pair("volatile", 0),
                make_pair("extern", 0)

        };
map<string, int> TestExecutionConfig::stopWords(stopWordsPairArray,
                                                stopWordsPairArray + sizeof(stopWordsPairArray) / sizeof(stopWordsPairArray[0]));

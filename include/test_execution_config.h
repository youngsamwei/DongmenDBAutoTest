//
// Created by sam on 2018/11/24.
//

#ifndef DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H
#define DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H

#include <cstddef>
#include <cstring>
#include <mysqlconn_manager.h>
#include <map>

using namespace std;

typedef enum OUTPUT_STYLE {
    OUTPUT_CONSOLE,
    OUTPUT_FILE
} OutputStyle;

class TestExecutionConfig {

public:
    MySQLConnManager *connManager;
    wstring expName;
    wstring expTarget;
    wstring expDirName;
    wstring title;
    wstring workDir;
    wstring dongmendbSrcDir;
    wstring outputDir;
    std::map<wstring, wstring> exp_files;
    int round;
    OutputStyle outputStyle;
    static map<string, int> stopWords;
    bool useStopWords;

    TestExecutionConfig(wstring expName,
                        wstring expTarget,
                        wstring expDirName,
                        wstring title,
                        wstring workDir,
                        wstring dongmendbSrcDir,
                        wstring outputDir,
                        bool useStopWords = false) {
        this->expName = expName;
        this->expTarget = expTarget;
        this->expDirName = expDirName;
        this->title = title;
        this->workDir = workDir;
        this->dongmendbSrcDir = dongmendbSrcDir;
        this->outputDir = outputDir;

        /*默认输出测试过程到文件*/
        this->outputStyle = OUTPUT_FILE;
        this->useStopWords = useStopWords;

    };

    TestExecutionConfig(wstring expName,
                        wstring expTarget,
                        wstring expDirName,
                        wstring title,
                        wstring workDir,
                        wstring dongmendbSrcDir,
                        wstring outputDir,
                        int round,
                        MySQLConnManager *connManager,
                        OutputStyle outputStyle,
                        bool useStopWords = false) {
        this->connManager = connManager;
        this->round = round;

        this->expName = expName;
        this->expTarget = expTarget;
        this->expDirName = expDirName;
        this->title = title;
        this->workDir = workDir;
        this->dongmendbSrcDir = dongmendbSrcDir;
        this->outputDir = outputDir;
        this->outputStyle = outputStyle;
        this->useStopWords = useStopWords;
    };

};


#endif //DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H

//
// Created by sam on 2018/11/24.
//

#ifndef DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H
#define DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H

#include <cstddef>
#include <cstring>
#include <mysqlconn_manager.h>

using namespace std;

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

    TestExecutionConfig(wstring expName,
                        wstring expTarget,
                        wstring expDirName,
                        wstring title,
                        wstring workDir,
                        wstring dongmendbSrcDir,
                        wstring outputDir) {
        this->expName = expName;
        this->expTarget = expTarget;
        this->expDirName = expDirName;
        this->title = title;
        this->workDir = workDir;
        this->dongmendbSrcDir = dongmendbSrcDir;
        this->outputDir = outputDir;
    };

    TestExecutionConfig(wstring expName,
                        wstring expTarget,
                        wstring expDirName,
                        wstring title,
                        wstring workDir,
                        wstring dongmendbSrcDir,
                        wstring outputDir,
                        int round,
                        MySQLConnManager *connManager)  {
        this->connManager = connManager;
        this->round = round;

        this->expName = expName;
        this->expTarget = expTarget;
        this->expDirName = expDirName;
        this->title = title;
        this->workDir = workDir;
        this->dongmendbSrcDir = dongmendbSrcDir;
        this->outputDir = outputDir;

    };
};

#endif //DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H

//
// Created by sam on 2018/11/24.
//

#ifndef DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H
#define DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H

#include <cstddef>
#include <cstring>
using namespace std;

class TestExecutionConfig {

public:
    wstring expName;
    wstring expTarget;
    wstring expDirName;
    wstring title;
    wstring workDir;
    wstring dongmendbSrcDir;
    wstring outputDir;
    std::map<wstring, wstring> exp_files;

    TestExecutionConfig(wstring expName,
                        wstring expTarget,
                        wstring expDirName,
                        wstring title,
                        wstring workDir,
                        wstring dongmendbSrcDir,
                        wstring outputDir){
        this->expName = expDirName;
        this->expTarget = expTarget;
        this->expDirName = expDirName;
        this->title = title;
        this->workDir =workDir;
        this->dongmendbSrcDir = dongmendbSrcDir;
        this->outputDir = outputDir;
    };
};

#endif //DONGMENDBAUTOTEST_TEST_EXECUTION_CONFIG_H

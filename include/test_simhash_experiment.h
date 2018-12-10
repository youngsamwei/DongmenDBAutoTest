//
// Created by sam on 2018/12/10.
//

#ifndef DONGMENDBAUTOTEST_SIMHASH_EXPERIMENT_H
#define DONGMENDBAUTOTEST_SIMHASH_EXPERIMENT_H

#include "test_execution_config.h"

class TestSimhashExperiment{
private:
    TestExecutionConfig *config;
public:
    TestSimhashExperiment(TestExecutionConfig *config);

    int run_simhash(TestExecutionConfig *config);
    int run_simhash();

    int run_cluster();
};
#endif //DONGMENDBAUTOTEST_SIMHASH_EXPERIMENT_H

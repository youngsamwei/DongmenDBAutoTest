//
// Created by sam on 2018/12/10.
//

#ifndef DONGMENDBAUTOTEST_DATAPOINT_MYSQLCONN_MANAGER_H
#define DONGMENDBAUTOTEST_DATAPOINT_MYSQLCONN_MANAGER_H

#include <vector>
#include "dbscan/datapoint.h"
#include "mysqlconn_manager.h"

using  namespace std;

class DataPointMysqlConnManager : public MySQLConnManager{

public:
    int getDataPoints(const string &sql_select, vector<DataPoint> *dataSets);

};
#endif //DONGMENDBAUTOTEST_DATAPOINT_MYSQLCONN_MANAGER_H

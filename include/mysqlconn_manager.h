//
// Created by sam on 2018/12/5.
//

#ifndef DONGMENDBAUTOTEST_MYSQLCONN_WRAPPER_H
#define DONGMENDBAUTOTEST_MYSQLCONN_WRAPPER_H

/*
 * 对mysql connector c的封装
 *
 * */

#include <string>
#include <vector>

#include "mysql.h"

using namespace std;

class MySQLConnManager {

public:

    MySQLConnManager();

    ~MySQLConnManager();

    bool init(const string &host, const string &user, const string &pw,
              const string &db, int port = 3306, const string &code = "gbk");

    bool reconnect();

    void close_connect();

    bool execute_sql(const string &sql);

    bool select_db(const string &dbname);

    bool select_data(const string &sql, vector<vector<string> > &result_matrix);

    bool select_data(const string &sql);

    string get_error_msg();

private:
    bool connect();

private:
    MYSQL m_mysql;
    string m_host;
    string m_user;
    string m_pw;
    string m_db;
    string m_code;
    int m_port;


};

#endif //DONGMENDBAUTOTEST_MYSQLCONN_WRAPPER_H

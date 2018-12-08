


#include <mysql.h>
#include <string>
#include "mysqlconn_manager.h"

using namespace std;

MySQLConnManager::MySQLConnManager()
{

}

MySQLConnManager::~MySQLConnManager()
{
    mysql_close(&m_mysql);
}

bool MySQLConnManager::init(const string& host, const string& user, const string& pw,
                       const string& db, int port, const string& code){
    m_host = host;
    m_user = user;
    m_pw = pw;
    m_db = db;
    m_port = port;
    m_code = code;
    return NULL != mysql_init(&m_mysql) && connect() && execute_sql(("set names " + m_code).c_str());
}

bool MySQLConnManager::reconnect()
{
    close_connect();
    return connect() && execute_sql(("set names " + m_code).c_str());
}

void MySQLConnManager::close_connect()
{
    mysql_close(&m_mysql);
}


bool MySQLConnManager::execute_sql(const string& sql)
{
    return 0 == mysql_real_query(&m_mysql, sql.c_str(), sql.size());
}

bool MySQLConnManager::select_db(const string &dbname){
    return mysql_select_db(&m_mysql, dbname.c_str());
}


bool MySQLConnManager::select_data(const string& sql, vector<vector<string> >& result_matrix)
{
    if(!execute_sql(sql))
        return false;

    MYSQL_RES *res = mysql_store_result(&m_mysql);
    if(NULL == res)
    {
        mysql_free_result(res);
        return false;
    }

    int numcols = mysql_num_fields(res);
    MYSQL_ROW row;
    while(row =  mysql_fetch_row(res))
    {
        vector<string> row_vec;
        row_vec.reserve(numcols);
        for(int i = 0; i < numcols; i++)
        {
            row_vec.push_back(row[i]);
        }
        result_matrix.push_back(row_vec);
    }

    mysql_free_result(res);
    return true;
}

bool MySQLConnManager::select_data(const string &sql){
   return execute_sql(sql);
};

string MySQLConnManager::get_error_msg()
{
    char buf[2048] = {0};
    snprintf(buf, 2047, "error_code=%d, error_msg=%s", mysql_errno(&m_mysql), mysql_error(&m_mysql));
    return buf;
}

bool MySQLConnManager::connect()
{
    return NULL != mysql_real_connect(&m_mysql, m_host.c_str(), m_user.c_str(), m_pw.c_str(), m_db.c_str(), m_port, NULL, 0);
}
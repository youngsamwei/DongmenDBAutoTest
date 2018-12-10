
#include "stdio.h"
#include "mysql.h"

#include <string>

#include <iostream>
#include <mysqlconn_manager.h>
#include <Utils.h>
#include "simhash.h"

using namespace std;


int test_simhash(){
    char *a = "我";
    char *b = "喜欢";
    char *c = "吃";
    char *d = "鸭梨";

    char *x = "我";
    char *y = "爱";
    char *z = "吃";
    char *w = "梨";

    const char *test1[4];
    const char *test2[4];
    test1[0] = a, test1[1] = b, test1[2] = c, test1[3] = d;
    test2[0] = x, test2[1] = y, test2[2] = z, test2[3] = w;
    ul_int hash1 = SimHash::sh_simhash(test1, 4);
    ul_int hash2 = SimHash::sh_simhash(test2, 4);
    float similarity = 0.0f;
    if(hash1 < hash2)
        similarity = hash1 * 1.0f / hash2;
    else
        similarity = hash2 * 1.0f / hash1;
    printf("hash1=%x, hash2=%x, similarity=%f\n", hash1, hash2, similarity);
    return 0;
}


int test_simhash_file(){
    wstring file1 = L"F:\\云班课作业 2018\\计算机16-1，2，3-数据库系统-课程设计_实验2_实现u_第7次\\201401060223_孙仕敏/01-exp_01_04_update.c";
    wstring file2 = L"F:\\云班课作业 2018\\计算机16-1，2，3-数据库系统-课程设计_实验2_实现u_第7次\\201501030413_毛锟/04-exp_01_04_update.c";

    string char_file1 = Utils::ws2s(file1);
    string char_file2 = Utils::ws2s(file2);
    ul_int hash1 = SimHash::simhash_file(char_file1.c_str());
    ul_int hash2 = SimHash::simhash_file(char_file2.c_str());
    float similarity = 0.0f;
    if(hash1 < hash2)
        similarity = hash1 * 1.0f / hash2;
    else
        similarity = hash2 * 1.0f / hash1;
    printf("hash1=%x, hash2=%x, similarity=%f\n", hash1, hash2, similarity);
    return 0;
}

int test_mysqlconn_manager(){
    MySQLConnManager conn;
    cout<<conn.init("127.0.0.1", "root", "123456", "mysql", 3366, "utf8")<<endl;
    cout<<conn.reconnect()<<endl;
    cout<<conn.get_error_msg()<<endl;
    vector<vector<string> > v;
    cout<<conn.select_data("select * from user", v)<<endl;
    for(size_t i = 0 ; i < v.size(); i++)
    {
        for(size_t j = 0; j < v[i].size(); j++)
            cout<<v[i][j]<<endl;
        cout<<"---------------"<<endl;
    }
    cout<<conn.get_error_msg()<<endl;
    return 0;
}

int test_mysql_conn_c(){
    MySQLConnManager conn;

    char tmp[400];
    //database configuartion
    string dbuser = "root";//mysql账号名
    string dbpasswd = "123456"; //mysql账号密码
    string dbip = "127.0.0.1";
    string dbname = "mysql";//数据库名
    string tablename = "user";//数据表名
    unsigned int port = 3306;
    char *query = NULL;

    int x;
    int y;
    int rt;//return value
    unsigned int t;

    int count = 0;
    conn.init(dbip,dbuser,dbpasswd,dbname);
    if (conn.reconnect()) {
        if (!conn.select_db(dbname)) {
            cout<<"Select successfully the database: "<<dbname<<endl;
        }else{
            cout<<"select database error: "<<conn.get_error_msg()<<endl;
        }
    }  else {
        cout<<"error: "<<conn.get_error_msg()<<endl;

        exit(0);
    }

    if (!conn.select_db("test")){
        conn.execute_sql("DROP TABLE IF EXISTS test");
        conn.execute_sql("CREATE TABLE test(id INT)");
    }else{
        cout<<"error: "<<conn.get_error_msg()<<endl;
    }
    //sprintf(tmp, "insert into %s values(%s,%d,%d)", tablename, "null", x, y); //注意如何向具有自增字段的数据库中插入记录
//    sprintf(tmp, "insert into bl values(null,'x','x','x','x')");
//
//
//    rt = mysql_real_query(con, tmp, strlen(tmp));
//    if (rt)
//    {
//        printf("Error making query: %s !!!\n", mysql_error(con));
//    }
//    else
//    {
//        printf("%s executed!!!\n", tmp);
//    }

//    sprintf(tmp, "select * from %s", tablename);
//    rt = mysql_real_query(con, tmp, strlen(tmp));
//    if (rt)
//    {
//        printf("Error making query: %s !!!\n", mysql_error(con));
//    }
//    else
//    {
//        printf("%s executed!!!\n", tmp);
//    }
//    res = mysql_store_result(con);//将结果保存在res结构体中
//
//    while (row = mysql_fetch_row(res)) {
//        for (t = 0; t<mysql_num_fields(res); t++) {
//            printf("%s  ", row[t]);
//        }
//        printf(".............\n");
//        count++;
//    }
//
//    printf("number of rows %d\n", count);
//    printf("mysql_free_result...\n");
//    mysql_free_result(res);
//    mysql_close(con);

    return 0;
}

int main()
{
    test_simhash_file();

}

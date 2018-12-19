//
// Created by sam on 2018/12/10.
//

#include <fstream>
#include <iosfwd>
#include <math.h>
#include <iomanip>
#include <Utils.h>
#include <map>
#include "dbscan/dbscan.h"
#include "mysqlconn_manager.h"


int DBSCANClusterAnalysis::getDataPoints(const string &sql_select, vector<DataPoint> *dataSets) {

    if (!this->execute_sql(sql_select))
        return 1;

    MYSQL_RES *res = this->store_result();
    if (NULL == res) {
        mysql_free_result(res);
        return 1;
    }

    MYSQL_ROW row;
    unsigned long i = 0;
    while (row = mysql_fetch_row(res)) {
        DataPoint tempDP(row[0], row[1]);
        double tempDimData[DIME_NUM];
        tempDimData[0] = atof(row[2]);

        tempDP.SetDimension(tempDimData);

        tempDP.SetDpId(i);                    //将数据点对象ID设置为i
        tempDP.SetVisited(false);            //数据点对象isVisited设置为false
        tempDP.SetClusterId(-1);            //设置默认簇ID为-1
        dataSets->push_back(tempDP);
        i++;
    }

    mysql_free_result(res);
    return 0;
};

DBSCANClusterAnalysis::DBSCANClusterAnalysis(string dbip, string dbuser, string dbpasswd, string dbname) {

    /*MySQLConnManager.init*/
    init(dbip, dbuser, dbpasswd, dbname);
    if (reconnect()) {
        if (!select_db(dbname)) {
            cout << "Select successfully the database: " << dbname << endl;
        } else {
            cout << "select database error: " << get_error_msg() << endl;
        }
    } else {
        cout << "error: " << get_error_msg() << endl;

        exit(0);
    }
};

DBSCANClusterAnalysis::~DBSCANClusterAnalysis() {
    close_connect();
};

/*
 * 初始化数据.
 * */
bool
DBSCANClusterAnalysis::initDataPoints(string &sql_select, double radius, int minPTs) {
    this->radius = radius;        //设置半径
    this->minPTs = minPTs;        //设置领域最小数据个数
    this->dimNum = DIME_NUM;    //设置数据维度

    dataSets.clear();

    getDataPoints(sql_select, &dataSets);

    dataNum = dataSets.size();            //设置数据对象集合大小
    for (unsigned long i = 0; i < dataNum; i++) {
        SetArrivalPoints(dataSets[i]);            //计算数据点领域内对象
    }
    return true;
};

/*输出第几轮次的聚类结果*/
bool DBSCANClusterAnalysis::WriteToFile(const int round, const string outputFileName) {
    string sql_select = "select distinct filename from experiments_simhash where round = " + to_string(round);

    if (!this->execute_sql(sql_select))
        return 1;

    MYSQL_RES *res = this->store_result();
    if (NULL == res) {
        mysql_free_result(res);
        return 1;
    }

    ofstream of1(outputFileName);

    MYSQL_ROW row;

    unsigned long *l = mysql_fetch_lengths(res);

//    of1<<WS2S(L"将对")<<*l<<WS2S(L"个文件聚类.")<<endl;
    while (row = mysql_fetch_row(res)) {
        string filename = row[0];
        WriteToOStream(filename, of1);
    }
    of1.close();    //关闭输出文件流
    mysql_free_result(res);
    return 0;
}

/*
函数：将已经过聚类算法处理的数据集合写回文件
说明：将已经过聚类结果写回文件
参数：
 string fileName 要分类的文件
char* outputFileName;    //要写入的文件名
返回值： true    */
bool DBSCANClusterAnalysis::WriteToOStream(const string fileName, ofstream &of1) {

    map<long, vector<DataPoint *> *> *cluster = new map<long, vector<DataPoint *> *>();
    map<long, vector<DataPoint *> *>::iterator it;


    for (unsigned long i = 0; i < dataSets.size(); i++) {
        long cid = dataSets[i].GetClusterId();

        vector<DataPoint *> *vdp;
        it = cluster->find(cid);
        if (it == cluster->end()) {
            vdp = new vector<DataPoint *>();
            cluster->insert(pair<long, vector<DataPoint *> *>(cid, vdp));
        } else {
            vdp = it->second;
        }
        vdp->push_back(&(dataSets[i]));
    }
    of1 << endl;
    of1 << "*************************************************************************************" << endl;
    of1 << WS2S(L"文件") << fileName << WS2S(L"的相似分组") << endl;
    of1 << "*************************************************************************************" << endl;

    cout<<"datasets size: "<<dataSets.size()<<", cluster size: "<<cluster->size()<<endl;

    it = cluster->begin();

    while (it != cluster->end()) {
        /*聚类id为-1说明不与其他相似*/
        if (it->first > -1) {
            vector<DataPoint *> *vdp = it->second;
            of1 << endl << endl << fileName << WS2S(L"相似分组 ") << to_string(it->first) << "("<<vdp->size()<<"):" << endl;

            if (vdp != NULL) {
                of1 << "\t";
                int i = 1;
                for (vector<DataPoint *>::iterator iter = vdp->begin(); iter != vdp->end(); iter++) {

                    of1 << (*iter)->getSname() << "(" << (*iter)->getSno() << ")" << ", ";

                    if (i % 4 == 0) {
                        of1 << endl << "\t";
                    }
                    i++;
                }

            }
        }
        it++;

    }

    of1 << endl;
    return true;    //返回
}

bool DBSCANClusterAnalysis::WriteToMysql(int test_round, string file_name) {
//对处理过的每个数据点写入数据库
    for (unsigned long i = 0; i < dataSets.size(); i++) {
        string sql_update = "update experiments_simhash set clusterid = "
                            + to_string(dataSets[i].GetClusterId())
                            + " where sno = '" + dataSets[i].getSno() + "' "
                            + " and round = " + to_string(test_round)
                            + " and filename = '" + file_name + "';";

//        cout << endl << sql_update << endl;
        if (!execute_sql(sql_update)) {
            cout << "error in DBSCANClusterAnalysis::WriteToMysql. sno: " << dataSets[i].getSno() << "\t sname: "
                 << dataSets[i].getSname() << endl << "error message"
                 << get_error_msg() << endl;
        };
    }
    return true;
}

/*
函数：设置数据点的领域点列表
说明：设置数据点的领域点列表
参数：
返回值： true;    */
void DBSCANClusterAnalysis::SetArrivalPoints(DataPoint &dp) {
    for (unsigned long i = 0; i < dataNum; i++)                //对每个数据点执行
    {
        double distance = GetDistance(dataSets[i], dp);    //获取与特定点之间的距离
        if (distance <= radius && i != dp.GetDpId())        //若距离小于半径，并且特定点的id与dp的id不同执行
            dp.GetArrivalPoints().push_back(i);            //将特定点id压力dp的领域列表中
    }
    if (dp.GetArrivalPoints().size() >= minPTs)            //若dp领域内数据点数据量> minPTs执行
    {
        dp.SetKey(true);    //将dp核心对象标志位设为true
        return;                //返回
    }
    dp.SetKey(false);    //若非核心对象，则将dp核心对象标志位设为false
}

bool DBSCANClusterAnalysis::DoDBSCANRecursive(int testRound, double radius, int minPTs){
    string sql_select = "select distinct filename from experiments_simhash where round = " + to_string(testRound);

    if (!this->execute_sql(sql_select))
        return 1;

    MYSQL_RES *res = this->store_result();
    if (NULL == res) {
        mysql_free_result(res);
        return 1;
    }

    MYSQL_ROW row;

    unsigned long *l = mysql_fetch_lengths(res);

//    of1<<WS2S(L"将对")<<*l<<WS2S(L"个文件聚类.")<<endl;
    while (row = mysql_fetch_row(res)) {
        string filename = row[0];

        string sql_select = "select sno, sname, simhash from experiments_simhash where round = " + to_string(testRound) +
                            " and filename='" + filename + "'";

        initDataPoints(sql_select, radius, minPTs);        //算法初始化操作，指定半径为10，领域内最小数据点个数为1，（在程序中已指定数据维度为1）
        DoDBSCANRecursiveOnDataset();                    //执行聚类算法
        WriteToMysql(testRound, filename);    //将聚类结果写入数据库
    }

    mysql_free_result(res);
    return 0;
}


bool DBSCANClusterAnalysis::DoDBSCANRecursive(int testRound, double radius, int minPTs, string outputFileName){
    string sql_select = "select distinct filename from experiments_simhash where round = " + to_string(testRound);

    if (!this->execute_sql(sql_select))
        return 1;

    MYSQL_RES *res = this->store_result();
    if (NULL == res) {
        mysql_free_result(res);
        return 1;
    }

    ofstream of1(outputFileName);

    MYSQL_ROW row;

    unsigned long *l = mysql_fetch_lengths(res);

//    of1<<WS2S(L"将对")<<*l<<WS2S(L"个文件聚类.")<<endl;
    while (row = mysql_fetch_row(res)) {
        string filename = row[0];

        string sql_select = "select sno, sname, simhash from experiments_simhash where round = " + to_string(testRound) +
                            " and filename='" + filename + "'";

        initDataPoints(sql_select, radius, minPTs);        //算法初始化操作，指定半径为10，领域内最小数据点个数为1，（在程序中已指定数据维度为1）
        DoDBSCANRecursiveOnDataset();                    //执行聚类算法
        WriteToMysql(testRound, filename);    //将聚类结果写入数据库
        WriteToOStream(filename, of1);
    }
    of1.close();    //关闭输出文件流
    mysql_free_result(res);
    return 0;
}
/*
函数：执行聚类操作
说明：执行聚类操作
参数：
返回值： true;    */
bool DBSCANClusterAnalysis::DoDBSCANRecursiveOnDataset() {
    unsigned long clusterId = 0;                        //聚类id计数，初始化为0
    for (unsigned long i = 0; i < dataNum; i++)            //对每一个数据点执行
    {
        DataPoint &dp = dataSets[i];                    //取到第i个数据点对象
        if (!dp.isVisited() && dp.IsKey())            //若对象没被访问过，并且是核心对象执行
        {
            dp.SetClusterId(clusterId);                //设置该对象所属簇ID为clusterId
            dp.SetVisited(true);                    //设置该对象已被访问过
            KeyPointCluster(i, clusterId);            //对该对象领域内点进行聚类
            clusterId++;                            //clusterId自增1
        }
        //cout << "孤立点\T" << i << endl;
    }

    cout << WS2S(L"共聚类") << clusterId << WS2S(L"个") << endl;        //算法完成后，输出聚类个数
    return true;    //返回
}

/*
函数：对数据点领域内的点执行聚类操作
说明：采用递归的方法，深度优先聚类数据
参数：
unsigned long dpID;            //数据点id
unsigned long clusterId;    //数据点所属簇id
返回值： void;    */
void DBSCANClusterAnalysis::KeyPointCluster(unsigned long dpID, unsigned long clusterId) {
    DataPoint &srcDp = dataSets[dpID];        //获取数据点对象
    if (!srcDp.IsKey()) return;
    vector<unsigned long> &arrvalPoints = srcDp.GetArrivalPoints();        //获取对象领域内点ID列表
    for (unsigned long i = 0; i < arrvalPoints.size(); i++) {
        DataPoint &desDp = dataSets[arrvalPoints[i]];    //获取领域内点数据点
        if (!desDp.isVisited())                            //若该对象没有被访问过执行
        {
            //cout << "数据点\t"<< desDp.GetDpId()<<"聚类ID为\t" <<clusterId << endl;
            desDp.SetClusterId(clusterId);        //设置该对象所属簇的ID为clusterId，即将该对象吸入簇中
            desDp.SetVisited(true);                //设置该对象已被访问
            if (desDp.IsKey())                    //若该对象是核心对象
            {
                KeyPointCluster(desDp.GetDpId(), clusterId);    //递归地对该领域点数据的领域内的点执行聚类操作，采用深度优先方法
            }
        }
    }
}

//两数据点之间距离
/*
函数：获取两数据点之间距离
说明：获取两数据点之间的欧式距离
参数：
DataPoint& dp1;        //数据点1
DataPoint& dp2;        //数据点2
返回值： double;    //两点之间的距离        */
double DBSCANClusterAnalysis::GetDistance(DataPoint &dp1, DataPoint &dp2) {
    double distance = 0;        //初始化距离为0
    for (int i = 0; i < DIME_NUM; i++)    //对数据每一维数据执行
    {
        distance += pow(dp1.GetDimension()[i] - dp2.GetDimension()[i], 2);    //距离+每一维差的平方
    }
    return pow(distance, 0.5);        //开方并返回距离
}
#ifndef _SQLRANK_
#define _SQLRANK_
#include <iostream>
#include <mysql/mysql.h>
#include <string.h>
using namespace std;
class SqlRank{
public:
    SqlRank();
    ~SqlRank();
    bool addRecord(string tableName, string policyName, int runTime);
private:
    void Init();
    const char* host;
    const char* userName;
    const char* passWord;
    const char* dbName;
    int port;
    MYSQL *conn;
    bool isDbExists = false; // 标记是否存在数据库
};

#endif

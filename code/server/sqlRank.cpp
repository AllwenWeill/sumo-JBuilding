#include "sqlRank.h"
SqlRank::SqlRank()
    :host("localhost"),
    userName("root"),
    passWord("1"),
    dbName("RunRank")
{
    Init();
}
void SqlRank::Init(){
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, host, userName, passWord, NULL, 0, NULL, 0) == NULL) { //connect failed
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    // 检查是否存在指定名称的数据库
    MYSQL_RES* res = mysql_list_dbs(conn, dbName);
    if (res != NULL)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            if (strcmp(row[0], dbName) == 0)
            {
                isDbExists = true;
                break;
            }
        }
        mysql_free_result(res);
    }
    // 如果数据库不存在，则创建它
    if (!isDbExists)
    {
        if (mysql_query(conn, "CREATE DATABASE RunRank"))
        {
            std::cerr << "Failed to create MySQL database: " << mysql_error(conn) << std::endl;
        }
        std::cout << "MySQL database created successfully." << std::endl;
    }
    else
    {
        std::cout << "MySQL database already exists." << std::endl;
    }
    // 切换到RunRank数据库
    if (mysql_select_db(conn, "RunRank")) {
        std::cerr << "Error: " << mysql_error(conn) << std::endl;
    }
    // 创建五种路网的BenchMark表
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS BenchMark_intersection (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50), RunTime INT)")) {
        std::cerr << "Error: " << mysql_error(conn) << std::endl;
    }
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS BenchMark_motorway (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50), RunTime INT)")) {
        std::cerr << "Error: " << mysql_error(conn) << std::endl;
    }
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS BenchMark_offramp (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50), RunTime INT)")) {
        std::cerr << "Error: " << mysql_error(conn) << std::endl;
    }
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS BenchMark_onofframp (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50), RunTime INT)")) {
        std::cerr << "Error: " << mysql_error(conn) << std::endl;
    }
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS BenchMark_onramp (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50), RunTime INT)")) {
        std::cerr << "Error: " << mysql_error(conn) << std::endl;
    }
}

bool SqlRank::addRecord(string tableName, string policyName, int runTime){
    string commandStr = "INSERT INTO RunRank.";
    commandStr += tableName;
    commandStr += " (name";
    commandStr += ", RunTime) VALUES ('";
    commandStr += policyName;
    commandStr += "', ";
    commandStr += to_string(runTime);
    commandStr += ");";
    cout<<commandStr<<endl;
    if (mysql_query(conn, commandStr.c_str())) {
        std::cerr << "Error: " << mysql_error(conn) << std::endl;
        return false;
    }
    cout<<"Processing the command: "<<commandStr<<endl;
    return true;
}

SqlRank::~SqlRank(){
    mysql_close(conn);
    std::cout<<"MySQL database already closed."<<std::endl; 
}
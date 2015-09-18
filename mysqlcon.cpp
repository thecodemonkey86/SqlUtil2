#include "mysqlcon.h"
#include "mysqlquery.h"

MySqlCon::MySqlCon()
{

}

MySqlCon::~MySqlCon()
{

}

SqlQuery *MySqlCon::buildQuery()
{
    MySqlQuery* mysqlQuery=new MySqlQuery(this);
    return mysqlQuery;
}


#include "mysqlcon.h"
#include "mysqlquery.h"

MySqlCon::MySqlCon()
{

}

MySqlCon::~MySqlCon()
{

}

std::unique_ptr<SqlQuery> MySqlCon::buildQuery()
{
     return std::move(std::unique_ptr<SqlQuery>(new MySqlQuery(this)));
}




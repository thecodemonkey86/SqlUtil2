#include "mysqlcon.h"
#include "mysqlquery.h"

MySqlCon::MySqlCon()
{

}

MySqlCon::~MySqlCon()
{

}

std::shared_ptr<SqlQuery> MySqlCon::buildQuery()
{
     return make_shared<MySqlQuery>(this);
     //
}




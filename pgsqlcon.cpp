#include "pgsqlcon.h"
#include "pgsqlquery.h"

PgSqlCon::PgSqlCon()
{

}

PgSqlCon::~PgSqlCon()
{

}

std::shared_ptr<SqlQuery> PgSqlCon::buildQuery()
{
    return std::make_shared<PgSqlQuery>(this);
}


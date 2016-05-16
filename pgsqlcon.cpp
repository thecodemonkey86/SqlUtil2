#include "pgsqlcon.h"
#include "pgsqlquery.h"

PgSqlCon::PgSqlCon()
{

}

PgSqlCon::~PgSqlCon()
{

}

std::unique_ptr<SqlQuery> PgSqlCon::buildQuery()
{
    return std::unique_ptr<SqlQuery>(new PgSqlQuery(this));
}


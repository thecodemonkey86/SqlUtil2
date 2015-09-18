#include "pgsqlcon.h"
#include "pgsqlquery.h"

PgSqlCon::PgSqlCon()
{

}

PgSqlCon::~PgSqlCon()
{

}

SqlQuery *PgSqlCon::buildQuery()
{
    PgSqlQuery * pg=new PgSqlQuery(this);
    return pg;
}


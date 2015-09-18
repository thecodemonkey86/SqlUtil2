#ifndef PGSQLQUERY_H
#define PGSQLQUERY_H

#include "sqlquery.h"

class PgSqlQuery : public SqlQuery
{
public:
    PgSqlQuery(Sql*sql);
    ~PgSqlQuery();
    virtual QString toString();
};

#endif // PGSQLQUERY_H

#ifndef PGSQLQUERY_H
#define PGSQLQUERY_H

#include "sqlquery.h"

class SQLUTIL2SHARED_EXPORT PgSqlQuery : public SqlQuery
{
public:
    PgSqlQuery(Sql*sql);
    ~PgSqlQuery();
    virtual QString toString();
};

#endif // PGSQLQUERY_H

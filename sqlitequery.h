#ifndef SQLITEQUERY_H
#define SQLITEQUERY_H
#include "sqlquery.h"

class SqliteQuery : public SqlQuery
{
public:
    SqliteQuery(Sql*sql);

    // SqlQuery interface
public:
    QString toString();
};

#endif // SQLITEQUERY_H

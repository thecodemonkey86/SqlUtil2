#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include "sqlquery.h"

class MySqlQuery : public SqlQuery
{
public:
    MySqlQuery(Sql*sql);
    ~MySqlQuery();
    virtual QString toString();
};

#endif // MYSQLQUERY_H

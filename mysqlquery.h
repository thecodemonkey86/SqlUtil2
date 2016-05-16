#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include "sqlquery.h"

class SQLUTIL2SHARED_EXPORT MySqlQuery : public SqlQuery
{
public:
    MySqlQuery(Sql*sql);
    ~MySqlQuery();
    virtual QString toString();
};

#endif // MYSQLQUERY_H

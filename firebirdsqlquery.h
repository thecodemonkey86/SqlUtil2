#ifndef FIREBIRDSQLQUERY_H
#define FIREBIRDSQLQUERY_H
#include "sqlquery.h"

class FirebirdSqlQuery : public SqlQuery
{
public:
    FirebirdSqlQuery(Sql*sql);

    // SqlQuery interface
public:
    virtual QString toString() override;
};

#endif // FIREBIRDSQLQUERY_H

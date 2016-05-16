#ifndef PGSQLCON_H
#define PGSQLCON_H

#include "sqlcon.h"

class SQLUTIL2SHARED_EXPORT PgSqlCon : public Sql
{
public:
    PgSqlCon();
    ~PgSqlCon();
    virtual std::unique_ptr<SqlQuery> buildQuery();
};

#endif // PGSQLCON_H

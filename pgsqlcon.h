#ifndef PGSQLCON_H
#define PGSQLCON_H

#include "sqlcon.h"

class PgSqlCon : public Sql
{
public:
    PgSqlCon();
    ~PgSqlCon();
     virtual SqlQuery* buildQuery();
};

#endif // PGSQLCON_H

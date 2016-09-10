#ifndef PGSQLCON_H
#define PGSQLCON_H

#include "sqlcon.h"
#include "pgsqlquery.h"
#include <memory>
using namespace std;
class SQLUTIL2SHARED_EXPORT PgSqlCon : public Sql
{
public:
    PgSqlCon();
    ~PgSqlCon();
    virtual shared_ptr<SqlQuery> buildQuery();
};

#endif // PGSQLCON_H

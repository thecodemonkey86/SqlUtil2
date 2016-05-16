#ifndef MYSQLCON_H
#define MYSQLCON_H

#include "sqlcon.h"


class SQLUTIL2SHARED_EXPORT MySqlCon : public Sql
{
public:
    MySqlCon();
    ~MySqlCon();
    virtual std::unique_ptr<SqlQuery> buildQuery();
};

#endif // MYSQLCON_H

#ifndef MYSQLCON_H
#define MYSQLCON_H

#include "sqlcon.h"


class MySqlCon : public Sql
{
public:
    MySqlCon();
    ~MySqlCon();
    virtual SqlQuery* buildQuery();
};

#endif // MYSQLCON_H

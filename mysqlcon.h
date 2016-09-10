#ifndef MYSQLCON_H
#define MYSQLCON_H

#include "sqlcon.h"
#include "mysqlquery.h"
#include <memory>
using namespace std;

class SQLUTIL2SHARED_EXPORT MySqlCon : public Sql
{
public:
    MySqlCon();
    ~MySqlCon();
    virtual shared_ptr<SqlQuery> buildQuery();
};

#endif // MYSQLCON_H

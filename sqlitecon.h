#ifndef SQLITECON_H
#define SQLITECON_H
#include "sqlcon.h"

class SqliteCon : public Sql
{
public:
    SqliteCon();
    virtual ~SqliteCon();
    // Sql interface
public:
    std::shared_ptr<SqlQuery> buildQuery();
};

#endif // SQLITECON_H

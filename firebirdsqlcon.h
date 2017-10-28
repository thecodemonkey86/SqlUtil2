#ifndef FIREBIRDSQLCON_H
#define FIREBIRDSQLCON_H
#include "sqlcon.h"
#include "firebirdsqlquery.h"
#include <memory>

class SQLUTIL2SHARED_EXPORT FirebirdSqlCon : public Sql
{
public:
    FirebirdSqlCon();

    // Sql interface
public:
    virtual std::shared_ptr<SqlQuery> buildQuery() override;
};

#endif // FIREBIRDSQLCON_H

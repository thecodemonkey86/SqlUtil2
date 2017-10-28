#include "firebirdsqlcon.h"

FirebirdSqlCon::FirebirdSqlCon()
{

}


std::shared_ptr<SqlQuery> FirebirdSqlCon::buildQuery()
{
    return make_shared<FirebirdSqlQuery>(this);
}

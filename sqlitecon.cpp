#include "sqlitecon.h"
#include "sqlitequery.h"

SqliteCon::SqliteCon()
{

}

SqliteCon::~SqliteCon()
{

}

std::shared_ptr<SqlQuery> SqliteCon::buildQuery()
{
    return make_shared<SqliteQuery>(this);
}

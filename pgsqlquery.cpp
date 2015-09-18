#include "pgsqlquery.h"

PgSqlQuery::PgSqlQuery(Sql*sql):SqlQuery(sql)
{

}

PgSqlQuery::~PgSqlQuery()
{

}

QString PgSqlQuery::toString()
{
    QString query;
    if (!selectFields.isEmpty()) {
        query+="SELECT "+selectFields+ " FROM "+fromTable;
    } else if (!deleteFromTable.isEmpty()) {
         query+="DELETE FROM "+deleteFromTable;
    }

    for(int i=0;i<joinTables.size();i++) {
        query+=joinTables.at(i);
    }

    if (!conditions.empty()) {
        query+=" WHERE ";

        foreach (QString cond, conditions) {
            query += cond;
        }
    }
    if (group.size()>0) {
        query += " GROUP BY " + group.at(0);
        for(int i=1;i<group.size();i++) {
            query += ",";
            query += group.at(i);
        }
    }
    if (limitResults>0) {
        query += "LIMIT "+ limitResults;
    }
    return query;

}


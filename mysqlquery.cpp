#include "mysqlquery.h"

MySqlQuery::MySqlQuery(Sql*sql):SqlQuery(sql)
{

}

MySqlQuery::~MySqlQuery()
{

}

QString MySqlQuery::toString()
{
    QString query;
    query+="SELECT "+selectFields+ " FROM "+fromTable;

    for(int i=0;i<joinTables.size();i++) {
        query+=joinTables.at(i);
    }
    query+=" WHERE ";

    foreach (QString cond, conditions) {
        query += cond;
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

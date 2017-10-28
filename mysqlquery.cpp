#include "mysqlquery.h"

MySqlQuery::MySqlQuery(Sql * sql): SqlQuery(sql) {

}

MySqlQuery::~MySqlQuery() {

}

QString MySqlQuery::toString() {
    QString query;
    query += QStringLiteral("SELECT %1 FROM %2").arg(selectFields, fromTable);
    for(const QString & jointable : joinTables) {
        query += jointable;
    }

    if(!conditions.isEmpty()) {
        query += " WHERE ";
        for(const QString & cond : conditions) {
            query += cond;
        }
    }

    if(group.size() > 0) {
        query += QStringLiteral(" GROUP BY %1").arg(group.at(0));
        for(int i = 1; i < group.size(); i++) {
            query += QStringLiteral(", %1").arg(group.at(i));
        }
    }
    if(limitResults > 0) {
        query += QStringLiteral("LIMIT %1").arg(limitResults);
    }
    return query;

}

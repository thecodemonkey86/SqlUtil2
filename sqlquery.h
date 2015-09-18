#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QString>
#include <QList>
#include <QPair>
#include <QVariant>
#include "sqlutil2_global.h"
#include <QSqlQuery>
#include "sqlexception.h"
#include "sqlcon.h"

class SQLUTIL2SHARED_EXPORT SqlQuery
{
public:
    SqlQuery(Sql*sql);
    virtual ~SqlQuery();
    SqlQuery* select();
    SqlQuery* select(const QString & selectFields);
    SqlQuery* from(const QString &  fromTable);
    SqlQuery* from(const QString &  fromTable,const QString &  alias);
    SqlQuery* join(const QString &  joinTable, const QString &alias, const QString &  on);
    SqlQuery* leftJoin(const QString &  joinTable, const QString &alias, const QString &  on);
    SqlQuery* where(const QString &  whereCond);
    SqlQuery* where(const QString &  whereCond, const QVariant&param);
    SqlQuery* where(const QString &  whereCond, const QList<QVariant>& params);
    SqlQuery* andWhere(const QString &  whereCond);
    SqlQuery* andWhere(const QString &  whereCond, const QVariant&param);
    SqlQuery* andWhere(const QString &  whereCond, const QList<QVariant>& params);
    SqlQuery* orWhere(const QString &  whereCond);
    SqlQuery* leftParentheses(const QString &  expression);
    SqlQuery* rightParentheses();
    SqlQuery* limit(int limitResults);
    SqlQuery* deleteFrom(const QString &  table);
    QSqlQuery *execQuery();
    bool execute();
    int fetchInt();
    virtual QString toString()=0;
protected:
    static const QString AND;
    static const QString OR;
    static const QChar LP;
    static const QChar RP;
    static const QString ON;
    static const QString JOIN;
    QString selectFields;
    QString fromTable;
    QList<QString > joinTables;
    QList<QString> conditions;
    QList<QString> group;
    int limitResults;
    QString deleteFromTable;
    QList<QVariant> params;
    Sql*sql;
};

#endif // SQLQUERY_H

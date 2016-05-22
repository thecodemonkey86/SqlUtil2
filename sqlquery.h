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
#include <memory>


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
    SqlQuery* join(const QString &  joinTableAlias, const QString &  on);
    SqlQuery* join(const QString &  joinTable, const QString &alias, const QString &  on, const QVariant&param);
    SqlQuery* join(const QString &  joinTableAlias, const QString &  on, const QVariant&param);

    SqlQuery* leftJoin(const QString &  joinTable, const QString &alias, const QString &  on);
    SqlQuery* leftJoin(const QString &  joinTable, const QString &alias, const QString &  on, const QVariant&param);
    SqlQuery* leftJoin(const QString &  joinTable, const QString &alias, const QString &  on, const QList<QVariant>& params);


    SqlQuery* leftJoin(const QString &  joinTableAlias, const QString &  on);
    SqlQuery* leftJoin(const QString &  joinTableAlias, const QString &  on, const QVariant&param);
    SqlQuery* leftJoin(const QString &  joinTableAlias, const QString &  on, const QList<QVariant>& params);
    SqlQuery* where(const QString &  whereCond);
    SqlQuery* where(const QString &  whereCond, const QVariant&param);
    SqlQuery* where(const QString &  whereCond, const QList<QVariant>& params);
    SqlQuery* andWhere(const QString &  whereCond);
    SqlQuery* andWhere(const QString &  whereCond, const QVariant&param);
    SqlQuery* andWhere(const QString &  whereCond, const QList<QVariant>& params);
    SqlQuery* orWhere(const QString &  whereCond);
    SqlQuery* whereIn(const QString &  expression, const QList<QVariant>& inParams );
    SqlQuery* whereIn(const QStringList &  columns, const QList<QVariant>& inParams );
    SqlQuery* andWhereIn(const QString &  expression, const QList<QVariant>& inParams );
    SqlQuery* andWhereIn(const QStringList &  columns, const QList<QVariant>& inParams );
    SqlQuery* leftParentheses(const QString &  expression);
    SqlQuery* rightParentheses();
    SqlQuery* limit(int limitResults);
    SqlQuery* deleteFrom(const QString &  table);
    std::unique_ptr<QSqlQuery> execQuery();
    bool execute();
    int fetchInt();
    virtual QString toString()=0;
    void debug();
protected:
    static const QString IN;
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

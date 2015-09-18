#ifndef SQL_H
#define SQL_H

#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "sqlexception.h"
#include <QDebug>
#include <QSqlError>
#include "sqlresult.h"
#include "sqlutil2_global.h"
class SqlQuery;
class Sql;

#include "sqlquery.h"

class SQLUTIL2SHARED_EXPORT Sql
{
protected:
 QSqlDatabase con;

public:
    Sql();
    virtual ~Sql();
    static Sql* connectMySql(const QString& host, const QString& user, const QString& pass, const QString& dbname);
    static Sql* connectPg(const QString& host, const QString& user, const QString& pass, const QString& dbname, int port=5432);

    SqlResult* fetchAll(const QString& sql, const QList<QVariant>&  params) ;
    SqlResult* fetchAll(const QString& sql, const QVariant&);
    SqlResult* fetchAll(const QString& sql);


    QSqlRecord fetchRow(const QString& sql, const QList<QVariant>&  params);
    QSqlRecord fetchRow(const QString& sql, const QVariant&);
    QSqlRecord fetchRow(const QString& sql);

    bool execute(const QString& sql, const QList<QVariant>&  params);
    bool execute(const QString& sql, const QVariant&);
    bool execute(const QString& sql);

    int fetchInt(const QString& sql, const QList<QVariant>&  params);

    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
    QSqlQuery* query(const QString& sql, const QVariant&);
    QSqlQuery* query(const QString& sql, const QList<QVariant>&  params);
    QSqlQuery* prepare(const QString& sql);
    void bindParams(QSqlQuery* query, const QList<QVariant>&  params);
    void bindParam(QSqlQuery* query, const QVariant&);
    int getErrorNr();

    virtual SqlQuery* buildQuery() = 0;

    QString printDebug(const QString& sql, const QList<QVariant>&  params );
    QString error();
    int insert(const QString& sql, const QList<QVariant>&  params);
    QSqlDatabase getCon();

};

#endif // SQL_H

#ifndef SQL_H
#define SQL_H

#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include "exception/sqlexception.h"
#include <QDebug>
#include <QSqlError>
#include "sqlutil2_global.h"
class SqlQuery;
class Sql;
class SqlException;

#include <memory>
#include "sqlquery.h"

using namespace std;

class SQLUTIL2SHARED_EXPORT Sql
{
protected:
 QSqlDatabase con;

public:
    Sql();
    virtual ~Sql();
    static Sql* connectMySql(const QString& host, const QString& user, const QString& pass, const QString& dbname);
    static Sql* connectPg(const QString& host, const QString& user, const QString& pass, const QString& dbname, int port=5432);
    static Sql* connectPg(const QString& host, const QString& user, const QString& pass, int port=5432);
    static Sql* connectFirebird(const QString & host, const QString & user, const QString & pass, const QString & dbFile, int port);
    static Sql* connectSqlite(const QString & user, const QString & pass, const QString & dbFile);
    static Sql *connectSqlite(const QString &dbFile);
    static unique_ptr<Sql> connectPgUniquePtr(const QString& host, const QString& user, const QString& pass, int port=5432);
    static shared_ptr<Sql> connectPgSharedPtr(const QString& host, const QString& user, const QString& pass, int port=5432);
    static unique_ptr<Sql> connectPgUniquePtr(const QString& host, const QString& user, const QString& pass, const QString& dbname, int port=5432);
    static shared_ptr<Sql> connectPgSharedPtr(const QString& host, const QString& user, const QString& pass, const QString& dbname, int port=5432);
    static shared_ptr<Sql> connectFirebirdSharedPtr(const QString& host, const QString& user, const QString& pass, const QString& dbFile, int port=3050);


    QVector<QSqlRecord> fetchAll(const QString& sql, const QList<QVariant>&  params) const ;
    QVector<QSqlRecord> fetchAll(const QString& sql, const QVariant&) const;
    QVector<QSqlRecord> fetchAll(const QString& sql) const;


    QSqlRecord fetchRow(const QString& sql, const QList<QVariant>&  params) const;
    QSqlRecord fetchRow(const QString& sql, const QList<QPair<QString,QVariant>>&  params) const;
    QSqlRecord fetchRow(const QString& sql, const QVariant&) const;
    QSqlRecord fetchRow(const QString& sql) const;
    void useDatabase(const QString & db) ;
    void execute(const QString& sql, const QList<QVariant>&  params);
    void execute(const QString& sql, const QVariant&);
    void execute(const QString& sql, int param);
    void execute(const QString& sql);

    int fetchInt(const QString& sql, const QList<QVariant>&  params) const;
    int fetchInt(const QString& sql,  const QList<QPair<QString,QVariant>>&  params) const;
    QString fetchString(const QString& sql, const QList<QVariant>&  params) const;

    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
    QSqlQuery query(const QString& sql, const QVariant&);
    QSqlQuery query(const QString& sql);
    QSqlQuery query(const QString& sql, const QList<QVariant>&  params);
    QSqlQuery prepare(const QString& sql);
    void bindParams( QSqlQuery& query, const QList<QVariant>&  params);
    void bindParam( QSqlQuery& query, const QVariant&);
    int getErrorNr() const;

    virtual std::shared_ptr<SqlQuery> buildQuery() = 0;

    QString printDebug(const QString& sql, const QList<QVariant>&  params );
    QString error() const;
    int insert(const QString& sql, const QList<QVariant>&  params);
    QSqlDatabase getCon() const;
    bool isOpen() const;
    void remove();

};

#endif // SQL_H

#include "sqlcon.h"
#include <QSqlDriver>
#include "mysqlcon.h"
#include "pgsqlcon.h"
#include "sqlitecon.h"
#include "firebirdsqlcon.h"

Sql::Sql() {

}

Sql::~Sql() {
    if(con.isOpen()) {
        con.close();
    }
}

Sql * Sql::connectMySql(const QString & host, const QString & user, const QString & pass, const QString & dbname) {
    Sql * sql = new MySqlCon();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QMYSQL"));
    sql->con.setHostName(host);
    sql->con.setDatabaseName(dbname);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

Sql * Sql::connectPg(const QString & host, const QString & user, const QString & pass, int port) {
    Sql * sql = new PgSqlCon();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    sql->con.setHostName(host);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    sql->con.setPort(port);
    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

unique_ptr<Sql> Sql::connectPgUniquePtr(const QString & host, const QString & user, const QString & pass, int port) {
    auto sql = make_unique<PgSqlCon>();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    sql->con.setHostName(host);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    sql->con.setPort(port);
    if(sql->con.open()) {
        return move(sql);
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

shared_ptr<Sql> Sql::connectPgSharedPtr(const QString & host, const QString & user, const QString & pass, const QString & dbname, int port) {
    auto sql = make_shared<PgSqlCon>();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    sql->con.setHostName(host);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    sql->con.setPort(port);
    sql->con.setDatabaseName(dbname);
    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

shared_ptr<Sql> Sql::connectFirebirdSharedPtr(const QString & host, const QString & user, const QString & pass, const QString & dbFile, int port) {
    auto sql = make_shared<FirebirdSqlCon>();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("qtfirebird"));
     sql->con.setDatabaseName(QStringLiteral("%1/%2:%3").arg(host, QString::number(port), dbFile));


     sql->con.setUserName(user);
     sql->con.setPassword(pass);

    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

Sql* Sql::connectFirebird(const QString & host, const QString & user, const QString & pass, const QString & dbFile, int port) {
    auto sql = new FirebirdSqlCon();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("qtfirebird"));
     sql->con.setDatabaseName(QStringLiteral("%1/%2:%3").arg(host, QString::number(port), dbFile));

  sql->con.setConnectOptions("CHARSET=UNICODE_FSS");
     sql->con.setUserName(user);
     sql->con.setPassword(pass);

    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

Sql *Sql::connectSqlite(const QString &dbFile)
{
    auto sql = new SqliteCon();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
     sql->con.setDatabaseName(dbFile);


    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

Sql *Sql::connectSqlite(const QString &dbFile, const QString &connectionName)
{
    auto sql = new SqliteCon();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"),connectionName);
     sql->con.setDatabaseName(dbFile);


    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

Sql *Sql::connectSqlite(const QString &user, const QString &pass, const QString &dbFile)
{
    auto sql = new SqliteCon();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
     sql->con.setDatabaseName(dbFile);


     sql->con.setUserName(user);
     sql->con.setPassword(pass);

    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

unique_ptr<Sql> Sql::connectPgUniquePtr(const QString & host, const QString & user, const QString & pass, const QString & dbname, int port) {
    auto sql = make_unique<PgSqlCon>();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    sql->con.setHostName(host);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    sql->con.setPort(port);
    sql->con.setDatabaseName(dbname);
    if(sql->con.open()) {
        return move(sql);
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

shared_ptr<Sql> Sql::connectPgSharedPtr(const QString & host, const QString & user, const QString & pass, int port) {
    auto sql = make_shared<PgSqlCon>();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    sql->con.setHostName(host);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    sql->con.setPort(port);
    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}



Sql * Sql::connectPg(const QString & host, const QString & user, const QString & pass, const QString & dbname, int port) {
    Sql * sql = new PgSqlCon();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    sql->con.setHostName(host);
    sql->con.setDatabaseName(dbname);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    sql->con.setPort(port);
    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

Sql * Sql::connectPg(const QString & host, const QString & user, const QString & pass, const QString & dbname, const QString&conName, int port) {
    Sql * sql = new PgSqlCon();
    sql->con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"),conName);
    sql->con.setHostName(host);
    sql->con.setDatabaseName(dbname);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    sql->con.setPort(port);
    if(sql->con.open()) {
        return sql;
    } else {
        throw SqlException(sql->getErrorNr(), sql-> error());
    }
}

QVector<QSqlRecord>  Sql::fetchAll(const QString & sql, const QVariant & param) const {
    QSqlQuery q(con);
    QVector<QSqlRecord> res;
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        q.addBindValue(param);
        if(q.exec()) {

            while(q.next()) {
                res.append(q.record());
            }
        } else if(q.lastError().number() != QSqlError::NoError) {
            const QString & msg = q.lastError().text();

            throw SqlException(q.lastError().number(), msg);
        }

    } else if(q.lastError().number() != QSqlError::NoError) {
        const QString & msg = q.lastError().text();

        throw SqlException(q.lastError().number(), msg);
    }
    return res;
}

QVector<QSqlRecord>Sql::fetchAll(const QString & sql) const {
    QSqlQuery q(con);
    QVector<QSqlRecord> res;
    q.setForwardOnly(true);
    if(q.exec(sql)) {

        while(q.next()) {
            res.append(q.record());
        }

    } else if(q.lastError().number() != QSqlError::NoError) {
        throw SqlException(q.lastError().number(), q.lastError().text());
    }

    return res;
}

QVector<QSqlRecord>  Sql::fetchAll(const QString & sql, const QList<QVariant> & params) const{
    QSqlQuery q(con);
    QVector<QSqlRecord> res;
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        for(int i = 0; i < params.size(); i++) {
            q.addBindValue(params.at(i));

        }
        if(q.exec()) {

            while(q.next()) {
                res.append(q.record());
            }
        } else if(q.lastError().number() != QSqlError::NoError) {
            const QString & msg = q.lastError().text();

            throw SqlException(q.lastError().number(), msg);
        }

    } else if(q.lastError().number() != QSqlError::NoError) {
        throw SqlException(q.lastError().number(), q.lastError().text());
    }

    return res;
}

QString Sql::error() const{
    return con.lastError().text().isEmpty() ? con.driver()->lastError().text() : con.lastError().text();
}

int Sql::getErrorNr() const{
    return con.driver()->lastError().number();
}

QSqlRecord Sql::fetchRow(const QString & sql, const QVariant & param) const{
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        q.addBindValue(param);
        if(q.exec()) {

            if(q.next()) {
                return q.record();
            }
        }

    }

    throw SqlException(getErrorNr(),  error(), sql);
}

QSqlRecord Sql::fetchRow(const QString &sql, const QString &param) const
{
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        q.addBindValue(param);
        if(q.exec()) {

            if(q.next()) {
                return q.record();
            }
        }

    }

    throw SqlException(getErrorNr(), error(), sql);
}

QSqlRecord Sql::fetchRow(const QString & sql) const{
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if(q.prepare(sql) &&  q.exec() && q.next()) {
        return q.record();
    }

    throw SqlException(getErrorNr(), error(), sql);
}

void Sql::useDatabase(const QString & db) {
    bool reopen = false;;
    if(con.isOpen()) {
        con.close();
        reopen = true;
    }
    con.setDatabaseName(db);
    if(reopen) {
        con.open();
    }
}

QSqlRecord Sql::fetchRow(const QString & sql, const QList<QVariant> & params) const{
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {

        for(int i = 0; i < params.size(); i++) {
            q.addBindValue(params.at(i));

        }
        if(q.exec()) {

            if(q.next()) {
                return q.record();
            }
        }

    }

    throw SqlException(getErrorNr(),  error(), sql);
}

QSqlRecord Sql::fetchRow(const QString &sql, const QList<QPair<QString, QVariant> > &params) const
{
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {

        for(int i = 0; i < params.size(); i++) {
            q.bindValue(QStringLiteral(":%1").arg(params[i].first),params[i].second);

        }
        if(q.exec()) {

            if(q.next()) {
                return q.record();
            }
        }

    }

    throw SqlException(getErrorNr(),  error(), sql);
}

void Sql::execute(const QString & sql, const QList<QVariant> & params) {
    QSqlQuery q(con);
    bool res = q.prepare(sql);
    for(int i = 0; i < params.size(); i++) {
        q.addBindValue(params.at(i));

    }

    res = res & q.exec();
#ifdef QT_DEBUG
    qDebug() << q.lastError().text();
#endif
    if(!res) {
        qDebug() << printDebug(sql,params);
        throw SqlException(q.lastError().number(), q.lastError().text().isEmpty() ? q.driver()->lastError().text() :q.lastError().text());
    }
}

void Sql::execute(const QString & sql, const QVariant & param) {
    QSqlQuery q(con);
    bool res = q.prepare(sql);
    q.addBindValue(param);

    res = res & q.exec();


    if(!res) {
        throw SqlException(q.lastError().number(), q.lastError().text());
    }
}

void Sql::execute(const QString & sql, int param) {
    QSqlQuery q(con);
    bool res = q.prepare(sql);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throw SqlException(q.lastError().number(), q.lastError().text());
    }
}

void Sql::execute(const QString & sql) {
    QSqlQuery q(con);
    bool res = q.exec(sql);
    if(!res) {
        throw SqlException(q.lastError().number(), q.lastError().text());
    }
}

int Sql::fetchInt(const QString &sql, const QVariant &param) const
{
    bool ok;
    int val = fetchRow(sql, param).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException(-1, "Invalid query");
    }
    return val;
}

int Sql::fetchInt(const QString &sql, const QString &param) const
{
    bool ok;
    int val = fetchRow(sql, param).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException(-1, "Invalid query");
    }
    return val;
}

int Sql::fetchInt(const QString & sql, const QList<QVariant> & params) const{
    bool ok;
    int val = fetchRow(sql, params).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException(-1, "Invalid query");
    }
    return val;
}

int Sql::fetchInt(const QString &sql, const QList<QPair<QString, QVariant> > &params) const
{
    bool ok;
    int val = fetchRow(sql, params).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException(-1, "Invalid query");
    }
    return val;
}

int Sql::fetchInt(const QString & sql) const{
    bool ok;
    int val = fetchRow(sql).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException(-1, "Invalid query");
    }
    return val;
}

QString Sql::fetchString(const QString &sql, const QList<QVariant> &params) const
{
    return fetchRow(sql, params).value(0).toString();
}

QString Sql::fetchString(const QString &sql, const QVariant &param) const
{
    return fetchRow(sql, param).value(0).toString();
}

QString Sql::fetchString(const QString &sql) const
{
    return fetchRow(sql).value(0).toString();
}

bool Sql::beginTransaction() {
    return con.driver()->beginTransaction();
}

bool Sql::commitTransaction() {
    return con.driver()->commitTransaction();
}

bool Sql::rollbackTransaction() {
    return con.driver()->rollbackTransaction();
}

QSqlQuery Sql::query(const QString & sql, const QVariant & param) {
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        q.addBindValue(param);
        if(!q.exec()) {

            throw SqlException(q.lastError().number(), q.lastError().text());
        }
        return q;

    }

    throw SqlException(q.lastError().number(), q.lastError().text());
}
QSqlQuery Sql::query(const QString & sql) {
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        if(!q.exec()) {
            throw SqlException(q.lastError().number(), q.lastError().text());
        }
        return q;

    }

    throw SqlException(q.lastError().number(), q.lastError().text());
}

QSqlQuery Sql::query(const QString & sql, const QList<QVariant> & params) {
    QSqlQuery q(con);
    q.setForwardOnly(true);
#ifdef QT_DEBUG
    qDebug() << sql;
#endif
    if(q.prepare(sql)) {
        for(int i = 0; i < params.size(); i++) {
            q.addBindValue(params.at(i));

        }
        if(!q.exec()) {
            throw SqlException(q.lastError().number(), q.lastError().text());
        }
        return q;

    }
    throw SqlException(q.lastError().number(), q.lastError().text());
}

QSqlQuery Sql::prepare(const QString & sql) {
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        return q;
    } else {
        throw SqlException(q.lastError().number(), q.lastError().text());
    }
}

void Sql::bindParams(QSqlQuery & query, const QList<QVariant> & params) {
    for(int i = 0; i < params.size(); i++) {
        query.addBindValue(params.at(i));
    }
}

void Sql::bindParam(QSqlQuery & query, const QVariant & param) {
    query.addBindValue(param);
}

QString Sql::printDebug(const QString & sql, const QList<QVariant> & params) {
    QString result(sql);
    for(int i = 0; i < params.size(); i++) {
        //       qDebug()<<params.at(i).typeName();
        QString v = QString(params.at(i).typeName()) != QStringLiteral("QByteArray") ? params.at(i).toString() : QString(params.at(i).toByteArray().toHex());
        QRegExp e("^[0-9][0-9]*$");
        result.replace(result.indexOf(QChar('?')), 1,
                       v.isNull() ? QStringLiteral("NULL") : e.exactMatch(v) ? v : QStringLiteral("'") + v + QStringLiteral("'"));
    }
    return result;
}



int Sql::insert(const QString & sql, const QList<QVariant> & params) {
    QSqlQuery q(con);
    bool res = q.prepare(sql);
    for(int i = 0; i < params.size(); i++) {
        q.addBindValue(params.at(i));

    }



    res &= q.exec();
    if(res) {
        int id = q.lastInsertId().toInt();

        return id;
    }

    throw SqlException(q.lastError().number(),q.lastError().text());
}


QSqlDatabase Sql::getCon() const{
    return con;
}


bool Sql::isOpen() const
{
    return con.isOpen();
}

void Sql::remove()
{
    QSqlDatabase::removeDatabase(con.connectionName());
}

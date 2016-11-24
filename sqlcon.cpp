#include "sqlcon.h"
#include <QSqlDriver>
#include "mysqlcon.h"
#include "pgsqlcon.h"

Sql::Sql() {

}

Sql::~Sql()
{
    if (con.isOpen())
        con.close();
}

Sql * Sql::connectMySql(const QString& host, const QString& user, const QString& pass, const QString& dbname) {
     Sql*sql=new MySqlCon();
     sql->con = QSqlDatabase::addDatabase("QMYSQL");
    sql->con.setHostName(host);
    sql->con.setDatabaseName(dbname);
    sql->con.setUserName(user);
    sql->con.setPassword(pass);
    if (sql->con.open()) {
        return sql;
    } else {
        throw SqlException( sql->getErrorNr(),sql->con.driver()->lastError().text());
    }
}

Sql * Sql::connectPg(const QString& host, const QString& user, const QString& pass, const QString& dbname,int port) {
    Sql*sql=new PgSqlCon();
    sql->con = QSqlDatabase::addDatabase("QPSQL");
   sql->con.setHostName(host);
   sql->con.setDatabaseName(dbname);
   sql->con.setUserName(user);
   sql->con.setPassword(pass);
   sql->con.setPort(port);
   if (sql->con.open()) {
       return sql;
   } else {
       throw SqlException(sql->getErrorNr(),sql->con.driver()->lastError().text());
   }
}

SqlResult*  Sql::fetchAll(const QString& sql, const QVariant&param) {
    QSqlQuery q(con);
    SqlResult* res=new SqlResult();
    q.setForwardOnly(true);
    if (q.prepare(sql)) {
         q.addBindValue(param);
        if ( q.exec()) {

            while (q.next()) {
                res->append(q.record());
            }
        }

    }else if (q.lastError().number() != QSqlError::NoError) {
        const QString& msg=q.lastError().text();

        throw QtException(msg);
    }
    return res;
}

SqlResult *Sql::fetchAll(const QString &sql)
{
    QSqlQuery q(con);
   SqlResult* res=new SqlResult();
   q.setForwardOnly(true);
   if (q.prepare(sql)) {
       if ( q.exec()) {

           while (q.next()) {
               res->append(q.record());
           }
       }

   } else if (q.lastError().number() != QSqlError::NoError) {
       throw QtException(q.lastError().text());
   }

   return res;
}

SqlResult*  Sql::fetchAll(const QString& sql, const QList<QVariant>&  params){
     QSqlQuery q(con);
    SqlResult* res=new SqlResult();
    q.setForwardOnly(true);
    if (q.prepare(sql)) {
        for(int i=0;i<params.size();i++) {
            q.addBindValue(params.at(i));

        }
        if ( q.exec()) {

            while (q.next()) {
                res->append(q.record());
            }
        }

    } else if (q.lastError().number() != QSqlError::NoError) {
        throw QtException(q.lastError().text());
    }

    return res;
}

QString Sql::error()
{
    return con.lastError().text().isEmpty() ? con.driver()->lastError().text() : con.lastError().text();
}

int Sql::getErrorNr()
{
return con.driver()->lastError().number();
}

QSqlRecord Sql::fetchRow(const QString& sql, const QVariant&param)
{
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if (q.prepare(sql)) {
        q.addBindValue(param );
        if ( q.exec()) {

            if (q.next()) {
                QSqlRecord res=q.record();

                return res;
            }
        }

    }

    throw SqlException(getErrorNr(),con.driver()->lastError().text(),sql);
}

QSqlRecord Sql::fetchRow(const QString &sql)
{
    QSqlQuery q(con);
    q.setForwardOnly(true);
    if (q.prepare(sql) && q.exec() && q.next()) {
        QSqlRecord res=q.record();
        return res;
    }

    throw SqlException(getErrorNr(),con.driver()->lastError().text(),sql);
}

QSqlRecord Sql::fetchRow(const QString& sql, const QList<QVariant>& params)
{
     QSqlQuery q(con);
    q.setForwardOnly(true);
    if (q.prepare(sql)) {

        for(int i=0;i<params.size();i++) {
            q.addBindValue(params.at(i));

        }
        if ( q.exec()) {

            if (q.next()) {
                return q.record();
            }
        }

    }

   throw SqlException(getErrorNr(),con.driver()->lastError().text(),sql);
}

bool Sql::execute(const QString& sql, const QList<QVariant>&  params) {
      QSqlQuery q(con);
     bool res= q.prepare(sql);
     for(int i=0;i<params.size();i++) {
         q.addBindValue(params.at(i));

     }

    res = res & q.exec();


    return res;
}

bool Sql::execute(const QString& sql, const QVariant&param)
{
     QSqlQuery q(con);
    bool res= q.prepare(sql);
     q.addBindValue(param );

   res = res & q.exec();


   return res;
}

bool Sql::execute(const QString& sql)
{
    QSqlQuery q(con);
   bool res= q.exec(sql);
   return res;
}

int Sql::fetchInt(const QString &sql, const QList<QVariant> &params)
{
    bool ok;
    int count = fetchRow(sql,params).value(0).toInt(&ok);
    if (!ok) {
        throw QtException("Invalid query");
    }
    return count;
}

bool Sql::beginTransaction()
{
   return con.driver()->beginTransaction();
}

bool Sql::commitTransaction()
{
   return con.driver()->commitTransaction();
}

bool Sql::rollbackTransaction()
{
    return con.driver()->rollbackTransaction();
}

QSqlQuery* Sql::query(const QString& sql, const QVariant&param)
{
     QSqlQuery *q=new QSqlQuery (con);
    q->setForwardOnly(true);
    if (q->prepare(sql)) {
         q->addBindValue(param );
        if (!q->exec()) {
            const QString& msg=q->lastError().text();

            throw QtException(msg);
        }
       return q;

    }
    const QString& msg=q->lastError().text();

    throw QtException(msg);
}
QSqlQuery* Sql::query(const QString& sql)
{
    QSqlQuery *q=new QSqlQuery (con);
    q->setForwardOnly(true);
    if (q->prepare(sql)) {
        if (!q->exec()) {
            const QString& msg=q->lastError().text();

            throw QtException(msg);
        }
        return q;

    }
    const QString& msg=q->lastError().text();

    throw QtException(msg);
}

QSqlQuery* Sql::query(const QString& sql, const QList<QVariant>& params)
{
    QSqlQuery* q = new QSqlQuery(con);
    q->setForwardOnly(true);
    if (q->prepare(sql)) {
        for(int i=0;i<params.size();i++) {
            q->addBindValue(params.at(i));

        }
        if (!q->exec()) {
            const QString& msg=q->lastError().text();

            throw QtException(msg);
        }
       return q;

    }
    const QString& msg=q->lastError().text();

    throw QtException(msg);
}

QSqlQuery *Sql::prepare(const QString& sql)
{
    QSqlQuery* q = new QSqlQuery(con);
    q->setForwardOnly(true);
    if (q->prepare(sql)) {
         return q;
    } else {
        const QString& msg=q->lastError().text();

        throw QtException(msg);
    }
}

void Sql::bindParams(QSqlQuery *query, const QList<QVariant>& params)
{
    for(int i=0;i<params.size();i++) {
        query->addBindValue(params.at(i));
    }
}

void Sql::bindParam(QSqlQuery *query, const QVariant&param)
{
     query->addBindValue(param );
}

QString Sql::printDebug(const QString& sql, const QList<QVariant>& params)
{
    QString result(sql);
   for(int i=0;i<params.size();i++) {
//       qDebug()<<params.at(i).typeName();
       QString v= QString(params.at(i).typeName())!= QString( "QByteArray") ? params.at(i).toString() :QString(params.at(i).toByteArray().toHex());
       QRegExp e("^[0-9][0-9]*$");
        result.replace(result.indexOf(QChar('?')),1,
                      v.isNull()?QString("NULL"): e.exactMatch(v)?v:QString("'")+ v+ QString("'"));
   }
   return result;
}



int Sql::insert(const QString& sql, const QList<QVariant>&  params)
{
     QSqlQuery q(con);
    bool res= q.prepare(sql);
    for(int i=0;i<params.size();i++) {
        q.addBindValue(params.at(i));

    }



   res = res & q.exec();
   if (res) {
        int id=q.lastInsertId().toInt();

        return id;
    }

    return -1;
}


QSqlDatabase Sql::getCon()
{
    return con;
}


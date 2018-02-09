#include "sqlquery.h"
#include <QFile>
#include <QSqlDriver>
#include <QDebug>

SqlQuery::SqlQuery(Sql*sql)
{
    this->limitResults = 0;
    this->sql = sql;
}

SqlQuery::~SqlQuery() {

}

SqlQuery *SqlQuery::select()
{
    this->selectFields = QStringLiteral("*");
    return this;
}

SqlQuery *SqlQuery::select(const QString &selectFields)
{
    this->selectFields = selectFields;
    return this;
}

SqlQuery *SqlQuery::from(const QString &fromTable)
{
    this->fromTable = fromTable;
    return this;
}

SqlQuery *SqlQuery::from(const QString &fromTable, const QString &alias)
{
    this->fromTable = fromTable+QStringLiteral("%1 %2").arg(alias);
    return this;
}

SqlQuery *SqlQuery::join(const QString &joinTable, const QString &alias, const QString & on)
{
    this->joinTables.append(QStringLiteral(" JOIN %1 %2 ON %3").arg( joinTable, alias, on));
    return this;
}

SqlQuery *SqlQuery::join(const QString &joinTableAlias, const QString &on)
{
    this->joinTables.append(QStringLiteral(" JOIN %1 ON %2").arg( joinTableAlias,on));
    return this;
}

SqlQuery *SqlQuery::join(const QString &joinTable, const QString &alias, const QString &on, const QVariant &param)
{
    this->params.append(param);
    return join(joinTable,alias,on);
}

SqlQuery *SqlQuery::join(const QString &joinTableAlias, const QString &on, const QVariant &param)
{
    this->params.append(param);
    return join(joinTableAlias,on);
}

SqlQuery *SqlQuery::leftJoin(const QString &joinTable, const QString &alias, const QString & on)
{
    this->joinTables.append(QStringLiteral(" LEFT JOIN %1 %2 ON %3").arg(joinTable, alias,on));
    return this;
}

SqlQuery *SqlQuery::leftJoin(const QString &joinTable, const QString &alias, const QString &on, const QVariant &param)
{
    this->params.append(param);
    return leftJoin(joinTable,alias,on);
}

SqlQuery *SqlQuery::leftJoin(const QString &joinTable, const QString &alias, const QString &on, const QList<QVariant> &params)
{
    this->params.append(params);
    return leftJoin(joinTable,alias,on);
}

SqlQuery *SqlQuery::leftJoin(const QString &joinTableAlias, const QString &on)
{
    this->joinTables.append(QStringLiteral(" LEFT JOIN %1 ON %2").arg(joinTableAlias,on));
    return this;
}

SqlQuery *SqlQuery::leftJoin(const QString &joinTableAlias, const QString &on, const QVariant &param)
{
    this->params.append(param);
    return leftJoin(joinTableAlias,on);
}

SqlQuery *SqlQuery::leftJoin(const QString &joinTableAlias, const QString &on, const QList<QVariant> &params)
{
    this->params.append(params);
    return leftJoin(joinTableAlias,on);
}

SqlQuery *SqlQuery::where(const QString &whereCond)
{
    if (!conditions.empty()) {
        this->conditions.append(AND);
    }
    this->conditions.append(whereCond);
    return this;
}

SqlQuery *SqlQuery::where(const QString &whereCond, const QVariant &param)
{

    this->params.append(param);
    return where(whereCond);
}

SqlQuery *SqlQuery::where(const QString &whereCond, const QList<QVariant>& params)
{

    this->params.append(params);
    return where(whereCond);
}

SqlQuery *SqlQuery::andWhere(const QString &whereCond)
{
    this->conditions.append(AND);
    this->conditions.append(whereCond);
    return this;
}

SqlQuery *SqlQuery::andWhere(const QString &whereCond, const QList<QVariant>& params)
{
    this->params.append(params);
    this->conditions.append(AND);
    this->conditions.append(whereCond);
    return this;
}

SqlQuery *SqlQuery::andWhere(const QString &whereCond, const QVariant &param)
{
    this->conditions.append(AND);
    this->conditions.append(whereCond);
    this->params.append(param);
    return this;
}


SqlQuery *SqlQuery::orWhere(const QString &whereCond)
{
    this->conditions.append(OR);
    this->conditions.append(whereCond);
    return this;
}
SqlQuery *SqlQuery::whereIn(const QStringList &columns, const QList<QVariant> &inParams)
{
    QStringList placeholdersList;
    placeholdersList.reserve(columns.size());

    for(int j=0;j<inParams.size()/ columns.size();j++) {
        QString placeholders;
        placeholders.reserve(columns.size()*2+1);
        placeholders[0] = LP;
        for(int i=1;i<placeholders.capacity()-1; i++) {
            if (i%2==0) {
                placeholders[i] = ',';
            } else {
                placeholders[i] = '?';
            }
        }
        placeholders[placeholders.capacity()-1] = RP;
        placeholdersList.append(placeholders);
    }

    this->conditions.append(LP);
    this->conditions.append(columns.join(QChar(',')));
    this->conditions.append(RP);
    this->conditions.append(IN);
    this->conditions.append(LP);
    this->conditions.append(placeholdersList.join(QChar(',')));
    this->conditions.append(RP);
    this->params.append(inParams);
    return this;
}

SqlQuery *SqlQuery::whereIn(const QString &expression, const QList<QVariant> &inParams)
{
    QString placeholders;
    placeholders.reserve(inParams.size()*2+3);
    placeholders[0] = LP;
    for(int i=1;i<placeholders.capacity()-1; i++) {
        if (i%2==0) {
            placeholders[i] = ',';
        } else {
            placeholders[i] = '?';
        }
    }
    placeholders[placeholders.capacity()-1] = RP;
    this->conditions.append(expression);
    this->conditions.append(IN);
    this->conditions.append(placeholders);
    this->params.append(inParams);
    return this;
}

SqlQuery *SqlQuery::andWhereIn(const QString &expression, const QList<QVariant> &inParams)
{
    this->conditions.append(AND);
    return whereIn(expression, inParams);
}

SqlQuery *SqlQuery::andWhereIn(const QStringList &columns, const QList<QVariant> &inParams)
{
    this->conditions.append(AND);
    return whereIn(columns, inParams);
}


SqlQuery *SqlQuery::leftParentheses(const QString &expression)
{
    this->conditions.append(LP);
    this->conditions.append(expression);
    return this;
}

SqlQuery *SqlQuery::rightParentheses()
{
    this->conditions.append(RP);
    return this;
}

SqlQuery *SqlQuery::limit(int limitResults)
{
    this->limitResults = limitResults;
    return this;
}

SqlQuery *SqlQuery::orderBy(const QString &orderBy, OrderDirection direction)
{
    this->orderByExpression = QStringLiteral("%1 %2 ").arg(orderBy, direction == SqlQuery::ORDER_ASC ? "asc" : "desc");
    return this;
}

SqlQuery *SqlQuery::orderBy(const QString &orderByExpression)
{
    this->orderByExpression = orderByExpression;
    return this;
}

SqlQuery *SqlQuery::deleteFrom(const QString &table)
{
    this->deleteFromTable = table;
    return this;
}

QSqlQuery SqlQuery::execQuery()
{
    QSqlQuery q(sql->getCon());
    q.setForwardOnly(true);
  //   qDebug()<<toString();
    if (q.prepare(toString())) {


        for(int i=0;i<params.size();i++) {
            q.addBindValue(params.at(i));

        }
        if (!q.exec()) {
            QString msg=q.lastError().text();
            qDebug()<<msg;
            qDebug()<<q.driver()->lastError().text();
            throw SqlException(sql->getErrorNr(),q.driver()->lastError().text(), toString());
        }
        return q;

    } else {
        /*  QFile f;
         f.setFileName("C:\\Temp\\test.txt");
        f.open(QFile::Truncate| QFile::WriteOnly);
        f.write(toString().toUtf8());
        f.close();*/
        QString msg=q.lastError().text();
        qDebug()<<msg;
        //qDebug()<<q.driver()->lastError().text();
        throw SqlException(sql->getErrorNr(), q.driver()->lastError().text(),toString());
    }

}


void SqlQuery::execute()
{
    this->sql->execute(toString(),params);
}

int SqlQuery::fetchInt()
{
    return this->sql->fetchInt(toString(),params);
}

void SqlQuery::debug()
{

    QString result(toString());
   for(int i=0;i<params.size();i++) {
//       qDebug()<<params.at(i).typeName();
       QString v= QString(params.at(i).typeName())!= QString( "QByteArray") ? params.at(i).toString() :QString(params.at(i).toByteArray().toHex());
       QRegExp e("^[0-9][0-9]*$");
        result.replace(result.indexOf(QChar('?')),1,
                      v.isNull()?QString("NULL"): e.exactMatch(v)?v:QString("'")+ v+ QString("'"));
   }
   std::cout<<result.toUtf8().data();

}

QString SqlQuery::debugAsString()
{
    QString result(toString());
   for(int i=0;i<params.size();i++) {
//       qDebug()<<params.at(i).typeName();
       QString v= QString(params.at(i).typeName())!= QString( "QByteArray") ? params.at(i).toString() :QString(params.at(i).toByteArray().toHex());
       QRegExp e("^[0-9][0-9]*$");
        result.replace(result.indexOf(QChar('?')),1,
                      v.isNull()?QString("NULL"): e.exactMatch(v)?v:QString("'")+ v+ QString("'"));
   }
   return result;
}
const QString SqlQuery::IN = QStringLiteral(" IN ");
const QString SqlQuery::AND = QStringLiteral(" AND ");
const QString SqlQuery::OR = QStringLiteral(" OR ");
const QChar SqlQuery::LP = QChar('(');
const QChar SqlQuery::RP = QChar(')');
//const QString SqlQuery::ON = QString(" ON ");
//const QString SqlQuery::JOIN = QString(" JOIN ");

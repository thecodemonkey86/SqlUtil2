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
    this->selectFields = QString("*");
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
    this->fromTable = fromTable+QChar(' ') + alias;
    return this;
}

SqlQuery *SqlQuery::join(const QString &joinTable, const QString &alias, const QString & on)
{
    this->joinTables.append(JOIN + joinTable+QChar(' ') + alias+SqlQuery::ON+ on);
    return this;
}

SqlQuery *SqlQuery::join(const QString &joinTableAlias, const QString &on)
{
    this->joinTables.append(JOIN + joinTableAlias+SqlQuery::ON+ on);
    return this;
}

SqlQuery *SqlQuery::leftJoin(const QString &joinTable, const QString &alias, const QString & on)
{
    this->joinTables.append(QString(" LEFT")+JOIN + joinTable+QChar(' ') + alias+SqlQuery::ON+on);
    return this;
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

SqlQuery *SqlQuery::deleteFrom(const QString &table)
{
    this->deleteFromTable = table;
    return this;
}

std::unique_ptr<QSqlQuery>SqlQuery::execQuery()
{
    std::unique_ptr<QSqlQuery> q(new QSqlQuery(sql->getCon()));
    q->setForwardOnly(true);
    // qDebug()<<toString();
    if (q->prepare(toString())) {


        for(int i=0;i<params.size();i++) {
            q->addBindValue(params.at(i));

        }
        if (!q->exec()) {
            QString msg=q->lastError().text();
            qDebug()<<msg;
            qDebug()<<q->driver()->lastError().text();
            throw SqlException(sql, toString());
        }
        return q;

    } else {
        /*  QFile f;
         f.setFileName("C:\\Temp\\test.txt");
        f.open(QFile::Truncate| QFile::WriteOnly);
        f.write(toString().toUtf8());
        f.close();*/
        QString msg=q->lastError().text();
        qDebug()<<msg;
        //qDebug()<<q->driver()->lastError().text();
        throw SqlException(sql, toString());
    }

}

bool SqlQuery::execute()
{
    return this->sql->execute(toString(),params);
}

int SqlQuery::fetchInt()
{
    return this->sql->fetchInt(toString(),params);
}

void SqlQuery::debug()
{

    qDebug()<<toString()<<"\n"<<params;

}
const QString SqlQuery::IN = QString(" IN ");
const QString SqlQuery::AND = QString(" AND ");
const QString SqlQuery::OR = QString(" OR ");
const QChar SqlQuery::LP = QChar('(');
const QChar SqlQuery::RP = QChar(')');
const QString SqlQuery::ON = QString(" ON ");
const QString SqlQuery::JOIN = QString(" JOIN ");

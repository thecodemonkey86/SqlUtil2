#include "sqlexception.h"



SqlException::SqlException(Sql*s, QString query) throw() : QtException(s->error())
{
    this->errorNr= s->getErrorNr();
    this->query = query;
}

SqlException::SqlException(Sql *s) throw() : QtException(s->error())
{
    this->errorNr= s->getErrorNr();
    this->query = QString("no query");
}

SqlException::~SqlException()  throw()
{

}





int SqlException::getErrorNr()
{
    return errorNr;
}

QString SqlException::getQuery()
{
    return query;
}

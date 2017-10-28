#include "sqlexception.h"



QString SqlException::getQuery() const
{
    return query;
}

void SqlException::setQuery(const QString &value)
{
    query = value;
}

SqlException::SqlException(int errorNr,const QString&error,const QString&query) throw() : QtException(error)
{
    this->errorNr= errorNr;
    this->query = query;
}

SqlException::SqlException(int errorNr, const QString &error) throw() : QtException(error)
{
     this->errorNr= errorNr;
}


SqlException::~SqlException()  throw()
{

}



int SqlException::getErrorNr()
{
    return errorNr;
}


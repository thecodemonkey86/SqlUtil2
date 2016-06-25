#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include "exception/qtexception.h"
#include "sqlcon.h"
#include "sqlutil2_global.h"

class Sql;
class QtException;

class SQLUTIL2SHARED_EXPORT SqlException : public QtException
{
private: int errorNr;
private: QString query;
public:
    SqlException(int errorNr, const QString&error,const QString&query)  throw();
    SqlException(int errorNr, const QString&error) throw();
    virtual ~SqlException() throw();
    int getErrorNr();
    QString getQuery() const;
    void setQuery(const QString &value);
};

#endif // SQLEXCEPTION_H

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
    SqlException(Sql*, QString)  throw();
    SqlException(Sql*)  throw();
    virtual ~SqlException() throw();
    int getErrorNr();
    QString getQuery();
};

#endif // SQLEXCEPTION_H

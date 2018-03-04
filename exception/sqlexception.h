#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include "exception/qtexception.h"
#include "sqlcon.h"
#include "sqlutil2_global.h"

class Sql;

class SQLUTIL2SHARED_EXPORT SqlException : public QtCommon2::QtException
{
private: int errorNr;
private: QString query;
public:
    SqlException(int errorNr, const QString&error,const QString&query)  noexcept;
    SqlException(int errorNr, const QString&error) noexcept;
    virtual ~SqlException() noexcept;
    int getErrorNr();
    QString getQuery() const;
    void setQuery(const QString &value);
};

#endif // SQLEXCEPTION_H

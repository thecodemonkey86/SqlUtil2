#ifndef SQLRESULT_H
#define SQLRESULT_H

#include <QList>
#include <QSqlRecord>

class Q_DECL_EXPORT SqlResult : public QList<QSqlRecord>
{

public:
    SqlResult() {

    }




};

#endif // SQLRESULT_H

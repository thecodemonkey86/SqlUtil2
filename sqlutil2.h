#ifndef SQLUTIL2_H
#define SQLUTIL2_H

#include "sqlutil2_global.h"

class SQLUTIL2SHARED_EXPORT SqlUtil2
{

public:
    SqlUtil2();
    static QString getPlaceholders(int count);
};

#endif // SQLUTIL2_H

#include "sqlutil2.h"
#include <QString>

SqlUtil2::SqlUtil2()
{
}

QString SqlUtil2::getPlaceholders(int count)
{
    QString placeholders;
    placeholders.reserve(count*2+1);
    placeholders[0] = '(';
    for(int i=1;i<placeholders.capacity()-1; i++) {
        if (i%2==0) {
            placeholders[i] = ',';
        } else {
            placeholders[i] = '?';
        }
    }
    placeholders[placeholders.capacity()-1] = ')';
    return placeholders;
}

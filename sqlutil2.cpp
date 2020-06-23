#include "sqlutil2.h"
#include <QString>

SqlUtil2::SqlUtil2()
{
}

QString SqlUtil2::getPlaceholders(int count)
{
  QString placeholders;
  placeholders.resize(count*2+1,QChar('\0'));
  placeholders[0] = '(';
  for(int i=1;i<placeholders.length()-1; i++) {
    if (i%2==0) {
      placeholders[i] = ',';
    } else {
      placeholders[i] = '?';
    }
  }
  placeholders[placeholders.length()-1] = ')';
  return placeholders;
}

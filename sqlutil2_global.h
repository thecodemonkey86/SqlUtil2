#ifndef SQLUTIL2_GLOBAL_H
#define SQLUTIL2_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLUTIL2_LIBRARY)
#  define SQLUTIL2SHARED_EXPORT Q_DECL_EXPORT
#else
#  define SQLUTIL2SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLUTIL2_GLOBAL_H

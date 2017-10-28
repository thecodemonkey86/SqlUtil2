#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T18:53:41
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = SqlUtil2
TEMPLATE = lib

DEFINES += SQLUTIL2_LIBRARY
DEFINES *= QT_USE_QSTRINGBUILDER

CONFIG += c++14

win32 {
    CONFIG += dll
}


CONFIG(release, debug|release) {
    QMAKE_CFLAGS_RELEASE -= -O
    QMAKE_CFLAGS_RELEASE -= -O1
    QMAKE_CFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
}


SOURCES += sqlutil2.cpp \
    exception/sqlexception.cpp \
    sqlcon.cpp \
    mysqlcon.cpp \
    sqlquery.cpp \
    mysqlquery.cpp \
    pgsqlcon.cpp \
    pgsqlquery.cpp \
    firebirdsqlcon.cpp \
    firebirdsqlquery.cpp


HEADERS += sqlutil2.h\
        sqlutil2_global.h \
    exception/sqlexception.h \
    sqlcon.h \
    mysqlcon.h \
    sqlquery.h \
    mysqlquery.h \
    pgsqlcon.h \
    pgsqlquery.h \
    nullable.h \
    firebirdsqlcon.h \
    firebirdsqlquery.h




CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtCommon-Desktop_Qt_5_9_0_MinGW_32bit/release/ -lQtCommon
CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtCommon-Desktop_Qt_5_9_0_MinGW_32bit/debug/ -lQtCommon

INCLUDEPATH += ../QtCommon

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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

CONFIG += c++11

win32 {
    CONFIG += dll
}


SOURCES += sqlutil2.cpp \
    sqlexception.cpp \
    sqlcon.cpp \
    mysqlcon.cpp \
    sqlquery.cpp \
    mysqlquery.cpp \
    pgsqlcon.cpp \
    pgsqlquery.cpp


HEADERS += sqlutil2.h\
        sqlutil2_global.h \
    sqlexception.h \
    sqlcon.h \
    sqlresult.h \
    mysqlcon.h \
    sqlquery.h \
    mysqlquery.h \
    pgsqlcon.h \
    pgsqlquery.h \
    nullable.h




unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtCommon-Desktop_Qt_5_5_0_GCC_64bit/release/ -lQtCommon
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtCommon-Desktop_Qt_5_5_0_GCC_64bit/debug/ -lQtCommon

INCLUDEPATH += ../QtCommon


unix {
    target.path = /usr/lib
    INSTALLS += target
}

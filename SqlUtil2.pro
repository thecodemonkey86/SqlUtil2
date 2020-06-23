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
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
CONFIG += c++14

win32 {
    CONFIG += dll
}

gcc{
CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
}
}

COMPILER = ""
ARCH = ""

msvc {

 COMPILER = "MSVC2017"
 MSVC_VER = $$(VisualStudioVersion)
 equals(MSVC_VER, 16.0){
     COMPILER = "MSVC2019"
 }

    equals(QT_ARCH, "x86_64"){
        ARCH = "64bit"
    } else {
         ARCH = "32bit"
    }

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
    firebirdsqlquery.cpp \
    sqlitecon.cpp \
    sqlitequery.cpp


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
    firebirdsqlquery.h \
    sqlitecon.h \
    sqlitequery.h



CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/release/ -lQtCommon2
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/debug/ -lQtCommon2

INCLUDEPATH += ../QtCommon2

unix {
    target.path = /usr/lib
    INSTALLS += target
}

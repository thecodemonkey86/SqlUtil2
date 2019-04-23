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



gcc {
contains(QT_ARCH, "x86_64"): {
CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_MinGW_64_bit/release/ -lQtCommon2
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_MinGW_64_bit/debug/ -lQtCommon2
} else {
CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_MinGW_32bit/release/ -lQtCommon2
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_MinGW_32bit/debug/ -lQtCommon2
}


}

msvc {
CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_MSVC2017_64bit/release/ -lQtCommon2
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_MSVC2017_64bit/debug/ -lQtCommon2
}


unix {

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_GCC_64bit/release/ -lQtCommon2
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_GCC_64bit/debug/ -lQtCommon2
}

INCLUDEPATH += ../QtCommon2

unix {
    target.path = /usr/lib
    INSTALLS += target
}

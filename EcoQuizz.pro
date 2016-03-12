#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T11:54:16
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EcoQuizz
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    testwindow.cpp \
    resultdialog.cpp \
    test.cpp \
    testsession.cpp \
    question.cpp \
    sessionreport.cpp \
    interruptdialog.cpp

HEADERS  += loginwindow.h \
    testwindow.h \
    resultdialog.h \
    test.h \
    testsession.h \
    question.h \
    sessionreport.h \
    interruptdialog.h

FORMS    += loginwindow.ui \
    testwindow.ui \
    resultdialog.ui \
    interruptdialog.ui

RESOURCES += \
    res.qrc

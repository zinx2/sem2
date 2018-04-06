#-------------------------------------------------
#
# Project created by QtCreator 2018-03-29T19:47:54
#
#-------------------------------------------------

QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sem2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
src/main.cpp \
src/view_home.cpp \
src/cs_networker.cpp \
src/cs_initializer.cpp

HEADERS += \
src/view_home.h \
src/cs_qheader.h \
src/cs_model.h \
src/cs_style.h \
src/cs_dialog.h \
src/cs_component.h \
src/cs_file.h \
src/cs_networker.h \
src/cs_checktable.h \
src/cs_command.h \
src/cs_dialog.h \
src/cs_metatable.h

RESOURCES += \
    res.qrc

#CONFIG += resources_big

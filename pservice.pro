#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T17:02:41
#
#-------------------------------------------------

QT       += core gui xml sql printsupport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets axcontainer webkit webkitwidgets

lessThan(QT_MAJOR_VERSION, 5): QT += webkit webkitwidgets


QMAKE_CXXFLAGS += -std=c++11

TARGET = pservice
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    user_form.cpp \
    getlist.cpp \
    add_forms/add_branch_form.cpp \
    add_forms/add_customer_form.cpp \
    add_forms/add_in_oper_form.cpp \
    add_forms/add_pservice_form.cpp \
    list_forms/list_form.cpp \
    list_forms/list_in_oper_form.cpp \
    list_forms/list_out_oper_form.cpp \
    add_forms/add_location_form.cpp \
    add_forms/add_out_oper_form.cpp \
    add_forms/add_tickets_out_form.cpp \
    list_forms/list_tickets_out_form.cpp \
    add_forms/add_tickets_reports_form.cpp \
    list_forms/list_tickets_reports_form.cpp \
    add_forms/add_tickets_form.cpp \
    tickets.cpp \
    home.cpp \
    diagram.cpp \
    footer.cpp

HEADERS  += mainwindow.h \
    user_form.h \
    getlist.h \
    add_forms/add_branch_form.h \
    add_forms/add_customer_form.h \
    add_forms/add_in_oper_form.h \
    add_forms/add_pservice_form.h \
    list_forms/list_form.h \
    list_forms/list_in_oper_form.h \
    list_forms/list_out_oper_form.h \
    add_forms/add_location_form.h \
    add_forms/add_out_oper_form.h \
    add_forms/add_tickets_out_form.h \
    list_forms/list_tickets_out_form.h \
    add_forms/add_tickets_reports_form.h \
    list_forms/list_tickets_reports_form.h \
    add_forms/add_tickets_form.h \
    tickets.h \
    home.h \
    diagram.h \
    footer.h

DISTFILES += \
    images/.directory.lock \
    images/cross (2).gif \
    images/cross.gif \
    images/home1.png \
    images/.directoryV10098.new

RESOURCES += \
    img.qrc \
    qss.qrc \
    doc.qrc

#ifndef ADD_IN_OPER_FORM_H
#define ADD_IN_OPER_FORM_H

#include "getlist.h"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QDebug>
#include <QMessageBox>
#include <QStatusBar>
#include <QSqlError>

class add_in_oper_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_in_oper_form(QWidget *parent = 0);
    ~add_in_oper_form();

    QSqlDatabase db;

    QLabel *lb_date_in_oper;
    QDateEdit *de_date_in_oper;
    QLabel *lb_sum_in_oper;
    QLineEdit *le_sum_in_oper;
    QLabel *lb_branches_list;
    QComboBox *cb_branches_list;
    QLabel *lb_doctype_list;
    QComboBox *cb_doctype_list;
    QLabel *lb_contract_num;
    QLineEdit *le_contract_num;
    QLabel *lb_contract_date;
    QDateEdit *de_contract_date;
    QLabel *lb_customer_list;
    QComboBox *cb_customer_list;
    QLabel *lb_pservice_list;
    QComboBox *cb_pservice_list;
    QLabel *lb_event_date;
    QDateEdit *de_event_date;
    QLabel *lb_annotation;
    QLineEdit *le_annotation;


signals:

public slots:
    int add_in_oper_form_show();
    int lb_doctype_list_changed(int i);
    int add_in_oper();
};

#endif // ADD_IN_OPER_FORM_H

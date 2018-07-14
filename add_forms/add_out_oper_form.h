#ifndef ADD_OUT_OPER_FORM_H
#define ADD_OUT_OPER_FORM_H

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

class add_out_oper_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_out_oper_form(QWidget *parent = 0);
    ~add_out_oper_form();

    QSqlDatabase db;

    QLabel *lb_date_out_oper;
    QDateEdit *de_date_out_oper;
    QLabel *lb_sum_out_oper;
    QLineEdit *le_sum_out_oper;
    QLabel *lb_branches_list;
    QComboBox *cb_branches_list;
    QLabel *lb_contract_num;
    QLineEdit *le_contract_num;
    QLabel *lb_contract_date;
    QDateEdit *de_contract_date;
    QLabel *lb_seller;
    QLineEdit *le_seller;
    QLabel *lb_goods;
    QLineEdit *le_goods;
    QLabel *lb_annotation;
    QLineEdit *le_annotation;

signals:

public slots:
    int add_out_oper_form_show();
    int add_out_oper();
};

#endif // ADD_OUT_OPER_FORM_H

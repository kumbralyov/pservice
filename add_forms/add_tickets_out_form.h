#ifndef ADD_TICKETS_OUT_FORM_H
#define ADD_TICKETS_OUT_FORM_H

#include "getlist.h"
#include "tickets.h"
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

class add_tickets_out_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_tickets_out_form(QWidget *parent = 0);
    ~add_tickets_out_form();

    QSqlDatabase db;

    QLabel *lb_tickets_out_date;
    QDateEdit *de_tickets_out_date;
    QLabel *lb_branches_list;
    QComboBox *cb_branches_list;
    QLabel *lb_amount;
    QLineEdit *le_amount;
    QLabel *lb_cost;
    QLineEdit *le_cost;
    QLabel *lb_numbers;
    QLineEdit *le_numbers;
    QLabel *lb_sum_text;
    QLabel *lb_sum;

    tickets *t;

signals:

public slots:
    int form_show();
    int add_tickets_out();
    int add_view();
    int change_sum();
};

#endif // ADD_TICKETS_OUT_FORM_H

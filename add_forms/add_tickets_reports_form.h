#ifndef ADD_TICKETS_REPORTS_FORM_H
#define ADD_TICKETS_REPORTS_FORM_H

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

class add_tickets_reports_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_tickets_reports_form(QWidget *parent = 0);
    ~add_tickets_reports_form();

    QSqlDatabase db;

    QLabel *lb_tickets_reports_date;
    QDateEdit *de_tickets_reports_date;
    QLabel *lb_branches_list;
    QComboBox *cb_branches_list;
    QLabel *lb_stub_amount;
    QLineEdit *le_stub_amount;
    QLabel *lb_stub_numbers;
    QLineEdit *le_stub_numbers;
    QLabel *lb_shortage_amount;
    QLineEdit *le_shortage_amount;
    QLabel *lb_shortage_numbers;
    QLineEdit *le_shortage_numbers;
    QLabel *lb_return_amount;
    QLineEdit *le_return_amount;
    QLabel *lb_return_numbers;
    QLineEdit *le_return_numbers;
    QLabel *lb_cost;
    QLineEdit *le_cost;
    QLabel *lb_annotation;
    QLineEdit *le_annotation;

signals:

public slots:
    int form_show();
    int add_tickets_reports();
};

#endif // ADD_TICKETS_REPORTS_FORM_H

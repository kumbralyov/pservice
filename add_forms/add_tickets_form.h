#ifndef ADD_TICKETS_FORM_H
#define ADD_TICKETS_FORM_H

#include "getlist.h"
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QStatusBar>
#include <QSqlError>

class add_tickets_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_tickets_form(QWidget *parent = 0);
    ~add_tickets_form();

    QSqlDatabase db;

    QLabel *lb_series;
    QLineEdit *le_series;
    QLabel *lb_numbers;
    QLineEdit *le_from;
    QLineEdit *le_to;

signals:

public slots:
    int form_show();
    int add_tickets();
};

#endif // ADD_TICKETS_FORM_H

#ifndef ADD_PSERVICE_FORM_H
#define ADD_PSERVICE_FORM_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QPushButton>
#include <QSqlQuery>
#include <QStatusBar>
#include <QDebug>
#include <QSqlError>

class add_pservice_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_pservice_form(QWidget *parent = 0);
    ~add_pservice_form();

    QSqlDatabase db;

    QLabel *lb_pservice;
    QLineEdit *le_pservice;
    QLabel *lb_price;
    QLineEdit *le_price;

signals:

public slots:
    int add_pservice_form_show();       // форма добавления платной услуги
    int add_pservice();                 // добавление платной услуги
};

#endif // ADD_PSERVICE_FORM_H

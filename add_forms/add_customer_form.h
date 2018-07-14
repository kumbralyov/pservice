#ifndef ADD_CUSTOMER_FORM_H
#define ADD_CUSTOMER_FORM_H

#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QPushButton>
#include <QSqlQuery>
#include <QStatusBar>
#include <QDebug>
#include <QSqlError>

class add_customer_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_customer_form(QWidget *parent = 0);
    ~add_customer_form();

    QSqlDatabase db;

    QRadioButton *rb_ip;
    QRadioButton *rb_org;
    QLabel *lb_full_name;
    QLineEdit *le_full_name;
    QLabel *lb_abbr_name;
    QLineEdit *le_abbr_name;
    QLabel *lb_director_position;
    QLineEdit *le_director_position;
    QLabel *lb_director_surname;
    QLineEdit *le_director_surname;
    QLabel *lb_director_first_name;
    QLineEdit *le_director_first_name;
    QLabel *lb_director_father_name;
    QLineEdit *le_director_father_name;
    QLabel *lb_address;
    QLineEdit *le_address;
    QLabel *lb_tin;
    QLineEdit *le_tin;
    QLabel *lb_kpp;
    QLineEdit *le_kpp;
    QLabel *lb_bank_account;
    QLineEdit *le_bank_account;
    QLabel *lb_cor_account;
    QLineEdit *le_cor_account;
    QLabel *lb_bic;
    QLineEdit *le_bic;
    QLabel *lb_bank_name;
    QLineEdit *le_bank_name;
    QLabel *lb_tel;
    QLineEdit *le_tel;
    QLabel *lb_other;
    QLineEdit *le_other;

signals:

public slots:
    int add_customer_form_show();       // форма добавления заказчика
    int add_customer();                 // добавление заказчика
    void rb_org_click();
    void rb_ip_click();
};

#endif // ADD_CUSTOMER_FORM_H

#ifndef LIST_IN_OPER_FORM_H
#define LIST_IN_OPER_FORM_H

#include "list_form.h"

class list_in_oper_form : public list_form
{
    Q_OBJECT
public:
    explicit list_in_oper_form(QWidget *parent = 0);

    QLabel *lb_date_in_oper;
    QDateEdit *de_date_in_oper_from;
    QDateEdit *de_date_in_oper_to;
    QLabel *lb_sum_in_oper;
    QLineEdit *le_sum_in_oper_from;
    QLineEdit *le_sum_in_oper_to;
    QLabel *lb_branches_list;
    QComboBox *cb_branches_list;
    QLabel *lb_doctype_list;
    QComboBox *cb_doctype_list;
    QLabel *lb_contract_num;
    QLineEdit *le_contract_num;
    QLabel *lb_contract_date;
    QDateEdit *de_contract_date_from;
    QDateEdit *de_contract_date_to;
    QLabel *lb_customer_list;
    QComboBox *cb_customer_list;
    QLabel *lb_pservice_list;
    QComboBox *cb_pservice_list;
    QLabel *lb_event_date;
    QDateEdit *de_event_date_from;
    QDateEdit *de_event_date_to;
    QLabel *lb_annotation;
    QLineEdit *le_annotation;

signals:

public slots:
    int form_show();

    int filter_create();
    QString filter_string();
    int filter_clear();

    int add();
    QVector<str_replace> replace(int row);
};

#endif // LIST_IN_OPER_FORM_H

#ifndef LIST_OUT_OPER_FORM_H
#define LIST_OUT_OPER_FORM_H

#include "list_form.h"

class list_out_oper_form : public list_form
{
    Q_OBJECT
public:
    explicit list_out_oper_form(QWidget *parent = 0);

    QLabel *lb_date_out_oper;
    QDateEdit *de_date_out_oper_from;
    QDateEdit *de_date_out_oper_to;
    QLabel *lb_sum_out_oper;
    QLineEdit *le_sum_out_oper_from;
    QLineEdit *le_sum_out_oper_to;
    QLabel *lb_branches_list;
    QComboBox *cb_branches_list;
    QLabel *lb_doctype_list;
    QComboBox *cb_doctype_list;
    QLabel *lb_contract_num;
    QLineEdit *le_contract_num;
    QLabel *lb_contract_date;
    QDateEdit *de_contract_date_from;
    QDateEdit *de_contract_date_to;

signals:

public slots:
    int form_show();

    int filter_create();
    QString filter_string();
    int filter_clear();

    int add();
};

#endif // LIST_OUT_OPER_FORM_H

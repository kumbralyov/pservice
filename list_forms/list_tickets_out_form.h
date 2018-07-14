#ifndef LIST_TICKETS_OUT_FORM_H
#define LIST_TICKETS_OUT_FORM_H

#include "list_form.h"

class list_tickets_out_form : public list_form
{
    Q_OBJECT
public:
    explicit list_tickets_out_form(QWidget *parent = 0);

    QLabel *lb_date_tickets_out;
    QDateEdit *de_date_tickets_out_from;
    QDateEdit *de_date_tickets_out_to;
    QLabel *lb_branches_list;
    QComboBox *cb_branches_list;

public slots:
    int form_show();

    int filter_create();
    QString filter_string();
    int filter_clear();

    int add();
    QVector<str_replace> replace(int row);
};

#endif // LIST_TICKETS_OUT_FORM_H

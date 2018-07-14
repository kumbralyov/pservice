#ifndef LIST_TICKETS_REPORTS_FORM_H
#define LIST_TICKETS_REPORTS_FORM_H

#include "list_form.h"

class list_tickets_reports_form : public list_form
{
    Q_OBJECT
public:
    explicit list_tickets_reports_form();

    QLabel *lb_date_tickets_reports;
    QDateEdit *de_date_tickets_reports_from;
    QDateEdit *de_date_tickets_reports_to;
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

#endif // LIST_TICKETS_REPORTS_FORM_H

#include "list_out_oper_form.h"

#include <add_forms/add_out_oper_form.h>

list_out_oper_form::list_out_oper_form(QWidget *parent) : list_form(parent)
{
    form_show();
}

int list_out_oper_form::form_show()
{
    filter_create();
    QVector<QString> s(8);
    s = {"Дата оплаты", "Сумма", "Дом культуры", "Номер договора", "Дата договора", "Продавец", "Товар / Услуга", "Пояснение"};
    table_show(s);
    list_footer->set_footer_sum(1);

    return 0;
}

int list_out_oper_form::filter_create()
{
    QVBoxLayout *vbl = new QVBoxLayout;
    getlist *g = new getlist;

    QGroupBox *gb_date_out_oper = new QGroupBox(tr("Дата оплаты:"));
    QHBoxLayout *hbl_date_out_oper = new QHBoxLayout;
    hbl_date_out_oper->addWidget(new QLabel("c"));
    de_date_out_oper_from = new QDateEdit();
    de_date_out_oper_from->setCalendarPopup(true);
    de_date_out_oper_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_date_out_oper_from->setDisplayFormat("dd MMMM yyyy");
    de_date_out_oper_from->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_date_out_oper->addWidget(de_date_out_oper_from);
    hbl_date_out_oper->addWidget(new QLabel("по"));
    de_date_out_oper_to = new QDateEdit();
    de_date_out_oper_to->setCalendarPopup(true);
    de_date_out_oper_to->setDate(QDate::currentDate());
    de_date_out_oper_to->setDisplayFormat("dd MMMM yyyy");
    de_date_out_oper_to->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_date_out_oper->addWidget(de_date_out_oper_to);
    gb_date_out_oper->setLayout(hbl_date_out_oper);
    gb_date_out_oper->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_date_out_oper);

    QGroupBox *gb_sum_out_oper = new QGroupBox(tr("Сумма:"));
    QHBoxLayout *hbl_sum_out_oper = new QHBoxLayout;
    hbl_sum_out_oper->addWidget(new QLabel("от"));
    le_sum_out_oper_from = new QLineEdit;
    hbl_sum_out_oper->addWidget(le_sum_out_oper_from);
    hbl_sum_out_oper->addWidget(new QLabel("до"));
    le_sum_out_oper_to = new QLineEdit;
    hbl_sum_out_oper->addWidget(le_sum_out_oper_to);
    gb_sum_out_oper->setLayout(hbl_sum_out_oper);
    gb_sum_out_oper->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_sum_out_oper);

    QGroupBox *gb_branches_list = new QGroupBox(tr("Дом культуры:"));
    QHBoxLayout *hbl_branches_list = new QHBoxLayout;
    cb_branches_list = new QComboBox;
    cb_branches_list->insertItem(-1, "Все");
    g->branches(cb_branches_list);
    hbl_branches_list->addWidget(cb_branches_list);
    gb_branches_list->setLayout(hbl_branches_list);
    gb_branches_list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_branches_list);

    QGroupBox *gb_contract_date = new QGroupBox(tr("Дата договора:"));
    QHBoxLayout *hbl_contract_date = new QHBoxLayout;
    hbl_contract_date->addWidget(new QLabel("c"));
    de_contract_date_from = new QDateEdit();
    de_contract_date_from->setCalendarPopup(true);
    de_contract_date_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_contract_date_from->setDisplayFormat("dd MMMM yyyy");
    de_contract_date_from->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_contract_date->addWidget(de_contract_date_from);
    hbl_contract_date->addWidget(new QLabel("по"));
    de_contract_date_to = new QDateEdit();
    de_contract_date_to->setCalendarPopup(true);
    de_contract_date_to->setDate(QDate::currentDate());
    de_contract_date_to->setDisplayFormat("dd MMMM yyyy");
    de_contract_date_to->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_contract_date->addWidget(de_contract_date_to);
    gb_contract_date->setLayout(hbl_contract_date);
    gb_contract_date->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_contract_date);

    QGroupBox *gb_buttons = new QGroupBox(tr(""));
    QHBoxLayout *hbl_buttons = new QHBoxLayout;
    // кнопка "очистить"
    QPushButton *pb_clear = new QPushButton("Очистить");
    pb_clear->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_clear, SIGNAL(clicked()), this, SLOT(filter_clear()));
    hbl_buttons->addWidget(pb_clear);
    QLabel *lb_bspace = new QLabel;
    hbl_buttons->addWidget(lb_bspace);
    // кнопка "обновить"
    QPushButton *pb_reload = new QPushButton("Обновить");
    pb_reload->setShortcut(QKeySequence(Qt::Key_Return));
    pb_reload->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_reload, SIGNAL(clicked()), this, SLOT(reload()));
    hbl_buttons->addWidget(pb_reload);
    gb_buttons->setLayout(hbl_buttons);
    gb_buttons->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_buttons);

    QLabel *lb_space = new QLabel;
    vbl->addWidget(lb_space);

    filter->setLayout(vbl);

    return 0;
}

QString list_out_oper_form::filter_string()
{
    QString strf;
    strf = "";
    if (de_date_out_oper_from->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " date_out_oper >= \'%1\'";
        strf = strf.arg(de_date_out_oper_from->date().toString("yyyy-MM-dd"));
    }
    if (de_date_out_oper_to->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " date_out_oper <= \'%1\'";
        strf = strf.arg(de_date_out_oper_to->date().toString("yyyy-MM-dd"));
    }
    if (le_sum_out_oper_from->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " sum_out_oper >= \'%1\'";
        strf = strf.arg(le_sum_out_oper_from->text());
    }
    if (le_sum_out_oper_to->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " sum_out_oper <= \'%1\'";
        strf = strf.arg(le_sum_out_oper_to->text());
    }
    if (cb_branches_list->currentIndex() != -1 && cb_branches_list->currentIndex() != 0)
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " out_operations.id_branch = \'%1\'";
        strf = strf.arg(cb_branches_list->currentIndex());
    }
    if (de_contract_date_from->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " contract_date >= \'%1\'";
        strf = strf.arg(de_contract_date_from->date().toString("yyyy-MM-dd"));
    }
    if (de_contract_date_to->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " contract_date <= \'%1\'";
        strf = strf.arg(de_contract_date_to->date().toString("yyyy-MM-dd"));
    }

    if (strf != "")
        strf = " where" + strf;

    strf = "select date_out_oper, sum_out_oper, branch_name, contract_num, contract_date, seller, goods, annotation from out_operations "
           "left join branches on out_operations.id_branch = branches.id_branch " + strf + " order by date_out_oper";

    return strf;
}

int list_out_oper_form::filter_clear()
{
    de_date_out_oper_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_date_out_oper_to->setDate(QDate::currentDate());
    le_sum_out_oper_from->setText("");
    le_sum_out_oper_to->setText("");
    cb_branches_list->setCurrentIndex(0);
    de_contract_date_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_contract_date_to->setDate(QDate::currentDate());
    reload();
    return 0;
}

int list_out_oper_form::add()
{
    add_out_oper_form *aoof = new add_out_oper_form;
    aoof->show();
    return 0;
}

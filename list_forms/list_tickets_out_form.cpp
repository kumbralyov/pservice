#include "list_tickets_out_form.h"

#include <add_forms/add_tickets_out_form.h>

list_tickets_out_form::list_tickets_out_form(QWidget *parent) : list_form(parent)
{
    form_show();
}

int list_tickets_out_form::form_show()
{
    file_path_doc = ":/docs/to-doc";
    file_path_html = ":/docs/to-html";
    file_doc = "to.docx";

    filter_create();
    QVector<QString> s(8);
    s = {"Дата выдачи", "Дом культуры", "Заведующий", "Количество билетов", "Цена", "Сумма", "Номера"};
    table_show(s);
    list_footer->set_footer_sum(2);
    list_footer->set_footer_sum(4);

    return 0;
}

int list_tickets_out_form::filter_create()
{
    QVBoxLayout *vbl = new QVBoxLayout;
    getlist *g = new getlist;

    QGroupBox *gb_date_tickets_out = new QGroupBox(tr("Дата оплаты:"));
    QHBoxLayout *hbl_date_tickets_out = new QHBoxLayout;
    hbl_date_tickets_out->addWidget(new QLabel("c"));
    de_date_tickets_out_from = new QDateEdit();
    de_date_tickets_out_from->setCalendarPopup(true);
    de_date_tickets_out_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_date_tickets_out_from->setDisplayFormat("dd MMMM yyyy");
    de_date_tickets_out_from->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_date_tickets_out->addWidget(de_date_tickets_out_from);
    hbl_date_tickets_out->addWidget(new QLabel("по"));
    de_date_tickets_out_to = new QDateEdit();
    de_date_tickets_out_to->setCalendarPopup(true);
    de_date_tickets_out_to->setDate(QDate::currentDate());
    de_date_tickets_out_to->setDisplayFormat("dd MMMM yyyy");
    de_date_tickets_out_to->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_date_tickets_out->addWidget(de_date_tickets_out_to);
    gb_date_tickets_out->setLayout(hbl_date_tickets_out);
    gb_date_tickets_out->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_date_tickets_out);

    QGroupBox *gb_branches_list = new QGroupBox(tr("Дом культуры:"));
    QHBoxLayout *hbl_branches_list = new QHBoxLayout;
    cb_branches_list = new QComboBox;
    cb_branches_list->insertItem(-1, "Все");
    g->branches(cb_branches_list);
    hbl_branches_list->addWidget(cb_branches_list);
    gb_branches_list->setLayout(hbl_branches_list);
    gb_branches_list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_branches_list);

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

QString list_tickets_out_form::filter_string()
{
    QString strf;
    strf = "";
    if (de_date_tickets_out_from->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " tickets_out_date >= \'%1\'";
        strf = strf.arg(de_date_tickets_out_from->date().toString("yyyy-MM-dd"));
    }
    if (de_date_tickets_out_to->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " tickets_out_date <= \'%1\'";
        strf = strf.arg(de_date_tickets_out_to->date().toString("yyyy-MM-dd"));
    }
    if (cb_branches_list->currentIndex() != -1 && cb_branches_list->currentIndex() != 0)
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " tickets_out.id_branch = \'%1\'";
        strf = strf.arg(cb_branches_list->currentIndex());
    }

    if (strf != "")
        strf = " where" + strf;

    strf = "select tickets_out_date, branch_name, director_name, tickets_out_amount, tickets_out_cost, tickets_out_amount*tickets_out_cost, tickets_out_numbers from tickets_out "
           "left join branches on tickets_out.id_branch = branches.id_branch " + strf + " order by tickets_out_date";

    return strf;
}

int list_tickets_out_form::filter_clear()
{
    de_date_tickets_out_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_date_tickets_out_to->setDate(QDate::currentDate());
    cb_branches_list->setCurrentIndex(0);
    reload();

    return 0;
}

int list_tickets_out_form::add()
{
    add_tickets_out_form *atof = new add_tickets_out_form;
    atof->show();
    return 0;
}

QVector<list_form::str_replace> list_tickets_out_form::replace(int row)
{
    QVector<str_replace> r = {
        {"%full_name%", "МБУ \"Управление культуры и организации досуга населения\""},
        {"%branch%", m->data(m->index(row, 2)).toString()},
        {"%director_name%", m->data(m->index(row, 3)).toString()},
        {"%sum_str%", money(m->data(m->index(row, 2)).toDouble())},
        {"%num%", QString::number(row)},
        {"%date%", m->data(m->index(row, 1)).toString()},
        {"%surname%", user_surname},
        {"%first_name%", user_first_name},
        {"%father_name%", user_father_name},
        {"%position%", user_position},
        {"%amount%", m->data(m->index(row, 4)).toString()},
        {"%numbers%", m->data(m->index(row, 7)).toString()}
    };
    return r;
}

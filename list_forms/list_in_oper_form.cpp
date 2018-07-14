#include "list_in_oper_form.h"

#include <add_forms/add_in_oper_form.h>

list_in_oper_form::list_in_oper_form(QWidget *parent) : list_form(parent)
{
    form_show();
}

int list_in_oper_form::form_show()
{
    file_path_doc = ":/docs/pko-doc";
    file_path_html = ":/docs/pko-html";
    file_doc = "pko.docx";

    filter_create();
    QVector<QString> s(8);
    s = {"Дата вноса денег", "Сумма", "Дом культуры", "Заведующий", "Тип документа", "Номер договора", "Дата договора", "Заказчик", "Услуга", "Дата мероприятия", "Пояснение"};
    table_show(s);
    list_footer->set_footer_sum(1);

    return 0;
}

int list_in_oper_form::filter_create()
{
    QVBoxLayout *vbl = new QVBoxLayout;
    getlist *g = new getlist;

    QGroupBox *gb_date_in_oper = new QGroupBox(tr("Дата вноса денег:"));
    QHBoxLayout *hbl_date_in_oper = new QHBoxLayout;
    hbl_date_in_oper->addWidget(new QLabel("c"));
    de_date_in_oper_from = new QDateEdit();
    de_date_in_oper_from->setCalendarPopup(true);
    de_date_in_oper_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_date_in_oper_from->setDisplayFormat("dd MMMM yyyy");
    de_date_in_oper_from->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_date_in_oper->addWidget(de_date_in_oper_from);
    hbl_date_in_oper->addWidget(new QLabel("по"));
    de_date_in_oper_to = new QDateEdit();
    de_date_in_oper_to->setCalendarPopup(true);
    de_date_in_oper_to->setDate(QDate::currentDate());
    de_date_in_oper_to->setDisplayFormat("dd MMMM yyyy");
    de_date_in_oper_to->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_date_in_oper->addWidget(de_date_in_oper_to);
    gb_date_in_oper->setLayout(hbl_date_in_oper);
    gb_date_in_oper->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_date_in_oper);

    QGroupBox *gb_sum_in_oper = new QGroupBox(tr("Сумма:"));
    QHBoxLayout *hbl_sum_in_oper = new QHBoxLayout;
    hbl_sum_in_oper->addWidget(new QLabel("от"));
    le_sum_in_oper_from = new QLineEdit;
    hbl_sum_in_oper->addWidget(le_sum_in_oper_from);
    hbl_sum_in_oper->addWidget(new QLabel("до"));
    le_sum_in_oper_to = new QLineEdit;
    hbl_sum_in_oper->addWidget(le_sum_in_oper_to);
    gb_sum_in_oper->setLayout(hbl_sum_in_oper);
    gb_sum_in_oper->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_sum_in_oper);

    QGroupBox *gb_branches_list = new QGroupBox(tr("Дом культуры:"));
    QHBoxLayout *hbl_branches_list = new QHBoxLayout;
    cb_branches_list = new QComboBox;
    cb_branches_list->insertItem(-1, "Все");
    g->branches(cb_branches_list);
    hbl_branches_list->addWidget(cb_branches_list);
    gb_branches_list->setLayout(hbl_branches_list);
    gb_branches_list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_branches_list);

    QGroupBox *gb_doctype_list = new QGroupBox(tr("Тип документа:"));
    QHBoxLayout *hbl_doctype_list = new QHBoxLayout;
    cb_doctype_list = new QComboBox;
    cb_doctype_list->insertItem(-1, "Все");
    g->doctypes(cb_doctype_list);
    connect(cb_doctype_list, SIGNAL(currentIndexChanged(int)), SLOT(lb_doctype_list_changed(int)));
    hbl_doctype_list->addWidget(cb_doctype_list);
    gb_doctype_list->setLayout(hbl_doctype_list);
    gb_doctype_list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_doctype_list);

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

    QGroupBox *gb_customer_list = new QGroupBox(tr("Заказчик:"));
    QHBoxLayout *hbl_customer_list = new QHBoxLayout;
    cb_customer_list = new QComboBox;
    cb_customer_list->insertItem(-1, "Все");
    g->customers(cb_customer_list);
    hbl_customer_list->addWidget(cb_customer_list);
    gb_customer_list->setLayout(hbl_customer_list);
    gb_customer_list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_customer_list);

    QGroupBox *gb_pservice_list = new QGroupBox(tr("Услуга:"));
    QHBoxLayout *hbl_pservice_list = new QHBoxLayout;
    cb_pservice_list = new QComboBox;
    cb_pservice_list->insertItem(-1, "Все");
    g->pservices(cb_pservice_list);
    hbl_pservice_list->addWidget(cb_pservice_list);
    gb_pservice_list->setLayout(hbl_pservice_list);
    gb_pservice_list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_pservice_list);

    QGroupBox *gb_event_date = new QGroupBox(tr("Дата предоставления услуги:"));
    QHBoxLayout *hbl_event_date = new QHBoxLayout;
    hbl_event_date->addWidget(new QLabel("c"));
    de_event_date_from = new QDateEdit();
    de_event_date_from->setCalendarPopup(true);
    de_event_date_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_event_date_from->setDisplayFormat("dd MMMM yyyy");
    de_event_date_from->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_event_date->addWidget(de_event_date_from);
    hbl_event_date->addWidget(new QLabel("по"));
    de_event_date_to = new QDateEdit();
    de_event_date_to->setCalendarPopup(true);
    de_event_date_to->setDate(QDate::currentDate());
    de_event_date_to->setDisplayFormat("dd MMMM yyyy");
    de_event_date_to->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    hbl_event_date->addWidget(de_event_date_to);
    gb_event_date->setLayout(hbl_event_date);
    gb_event_date->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_event_date);

    QGroupBox *gb_buttons = new QGroupBox(tr(""));
    QHBoxLayout *hbl_buttons = new QHBoxLayout;
    // кнопка "очистить"
    QPushButton *pb_clear = new QPushButton("Очистить");
    pb_clear->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_clear, SIGNAL(clicked()), this, SLOT(filter_clear()));   // вызов функции создания базы данных и пользователя
    hbl_buttons->addWidget(pb_clear);
    QLabel *lb_bspace = new QLabel;
    hbl_buttons->addWidget(lb_bspace);
    // кнопка "обновить"
    QPushButton *pb_reload = new QPushButton("Обновить");
    pb_reload->setShortcut(QKeySequence(Qt::Key_Return));
    pb_reload->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_reload, SIGNAL(clicked()), this, SLOT(reload()));   // вызов функции создания базы данных и пользователя
    hbl_buttons->addWidget(pb_reload);
    gb_buttons->setLayout(hbl_buttons);
    gb_buttons->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vbl->addWidget(gb_buttons);

    QLabel *lb_space = new QLabel;
    vbl->addWidget(lb_space);

    filter->setLayout(vbl);

    return 0;
}

QString list_in_oper_form::filter_string()
{
    QString strf;
    strf = "";
    if (de_date_in_oper_from->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " date_in_oper >= \'%1\'";
        strf = strf.arg(de_date_in_oper_from->date().toString("yyyy-MM-dd"));
    }
    if (de_date_in_oper_to->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " date_in_oper <= \'%1\'";
        strf = strf.arg(de_date_in_oper_to->date().toString("yyyy-MM-dd"));
    }
    if (le_sum_in_oper_from->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " sum_in_oper >= \'%1\'";
        strf = strf.arg(le_sum_in_oper_from->text());
    }
    if (le_sum_in_oper_to->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " sum_in_oper <= \'%1\'";
        strf = strf.arg(le_sum_in_oper_to->text());
    }
    if (cb_branches_list->currentIndex() != -1 && cb_branches_list->currentIndex() != 0)
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " in_operations.id_branch = \'%1\'";
        strf = strf.arg(cb_branches_list->currentIndex());
    }
    if (cb_doctype_list->currentIndex() != -1 && cb_doctype_list->currentIndex() != 0)
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " in_operations.id_doc_type = \'%1\'";
        strf = strf.arg(cb_doctype_list->currentIndex());
    }
    if (cb_doctype_list->currentIndex() == 2)   // если тип документа - договор, фильтруется дата договора
    {
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
    }
    if (cb_customer_list->currentIndex() != -1 && cb_customer_list->currentIndex() != 0)
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " in_operations.id_customer = \'%1\'";
        strf = strf.arg(cb_customer_list->currentIndex());
    }
    if (cb_pservice_list->currentIndex() != -1 && cb_pservice_list->currentIndex() != 0)
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " in_operations.id_pservice = \'%1\'";
        strf = strf.arg(cb_pservice_list->currentIndex());
    }
    if (de_event_date_from->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " event_date >= \'%1\'";
        strf = strf.arg(de_event_date_from->date().toString("yyyy-MM-dd"));
    }
    if (de_event_date_to->text() != "")
    {
        if (strf != "")
            strf = strf + " and";
        strf = strf + " event_date <= \'%1\'";
        strf = strf.arg(de_event_date_to->date().toString("yyyy-MM-dd"));
    }

    if (strf != "")
        strf = " where" + strf;

    strf = "select date_in_oper, sum_in_oper, branch_name, director_name, doc_type, contract_num, contract_date, abbr_name, pservice_name, event_date, annotation "
           "from (((in_operations "
           "left join branches on in_operations.id_branch = branches.id_branch) "
           "left join doc_type on in_operations.id_doc_type = doc_type.id_doc_type) "
           "left join customers on in_operations.id_customer = customers.id_customer) "
           "left join paid_services on in_operations.id_pservice = paid_services.id_pservice "
            + strf + " order by date_in_oper";

    return strf;
}

int list_in_oper_form::filter_clear()
{
    de_date_in_oper_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_date_in_oper_to->setDate(QDate::currentDate());
    le_sum_in_oper_from->setText("");
    le_sum_in_oper_to->setText("");
    cb_branches_list->setCurrentIndex(0);
    cb_doctype_list->setCurrentIndex(0);
    de_contract_date_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_contract_date_to->setDate(QDate::currentDate());
    cb_customer_list->setCurrentIndex(0);
    cb_pservice_list->setCurrentIndex(0);
    de_event_date_from->setDate(QDate(QDate::currentDate().year(), 1, 1));
    de_event_date_to->setDate(QDate::currentDate());
    reload();
    return 0;
}

int list_in_oper_form::add()
{
    add_in_oper_form *aiof = new add_in_oper_form;
    aiof->show();
    return 0;
}

QVector<list_form::str_replace> list_in_oper_form::replace(int row)
{
    double rub;
    QVector<str_replace> r = {
        {"%full_name%", "МБУ \"Управление культуры и организации досуга населения\""},
        {"%branch%", m->data(m->index(row, 3)).toString()},
        {"%director_name%", m->data(m->index(row, 4)).toString()},
        {"%sum_str%", money(m->data(m->index(row, 2)).toDouble())},
        {"%num%", QString::number(row)},
        {"%date%", m->data(m->index(row, 1)).toString()},
        {"%day%", QString::number(m->data(m->index(row, 1)).toDate().day())},
        {"%month%", QString::number(m->data(m->index(row, 1)).toDate().month())},
        {"%year%", QString::number(m->data(m->index(row, 1)).toDate().year())},
        {"%kop%", QString::number(modf(m->data(m->index(row, 2)).toFloat(), &rub))},
        {"%rub%", QString::number(rub)}
    };
    qDebug() << __FILE__ << __LINE__ << m->data(m->index(row, 3)).toString() << "  " << m->data(m->index(row, 4)).toString();
    return r;
}

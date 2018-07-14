#include "add_in_oper_form.h"

add_in_oper_form::add_in_oper_form(QWidget *parent)
    : QMainWindow(parent)
{
    add_in_oper_form_show();
}

add_in_oper_form::~add_in_oper_form()
{
    db.close();
}

// форма добавления приходной операции
int add_in_oper_form::add_in_oper_form_show()
{
    QGridLayout *gl = new QGridLayout;
    getlist *g = new getlist;

    lb_date_in_oper = new QLabel("Дата вноса денег");
    gl->addWidget(lb_date_in_oper, 0, 0, 1, 1);
    de_date_in_oper = new QDateEdit();
    de_date_in_oper->setCalendarPopup(true);
    de_date_in_oper->setDate(QDate::currentDate());
    de_date_in_oper->setDisplayFormat("dd MMMM yyyy");
    de_date_in_oper->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    gl->addWidget(de_date_in_oper, 0, 1, 1, 1);

    lb_sum_in_oper = new QLabel("Сумма");
    gl->addWidget(lb_sum_in_oper, 1, 0, 1, 1);
    le_sum_in_oper = new QLineEdit;
    gl->addWidget(le_sum_in_oper, 1, 1, 1, 1);
    le_sum_in_oper->setFocus();

    lb_branches_list = new QLabel("Дом культуры");
    gl->addWidget(lb_branches_list, 2, 0, 1, 1);
    cb_branches_list = new QComboBox;
    gl->addWidget(cb_branches_list, 2, 1, 1, 1);
    cb_branches_list->insertSeparator(-1);
    g->branches(cb_branches_list);

    lb_doctype_list = new QLabel("Тип документа");
    gl->addWidget(lb_doctype_list, 3, 0, 1, 1);
    cb_doctype_list = new QComboBox;
    gl->addWidget(cb_doctype_list, 3, 1, 1, 1);
    cb_doctype_list->insertSeparator(-1);
    g->doctypes(cb_doctype_list);
    connect(cb_doctype_list, SIGNAL(currentIndexChanged(int)), SLOT(lb_doctype_list_changed(int)));

    lb_contract_num = new QLabel("Номер договора");
    gl->addWidget(lb_contract_num, 4, 0, 1, 1);
    lb_contract_num->hide();
    le_contract_num = new QLineEdit;
    gl->addWidget(le_contract_num, 4, 1, 1, 1);
    le_contract_num->hide();

    lb_contract_date = new QLabel("Дата договора");
    gl->addWidget(lb_contract_date, 5, 0, 1, 1);
    lb_contract_date->hide();
    de_contract_date = new QDateEdit();
    de_contract_date->setCalendarPopup(true);
    de_contract_date->setDate(QDate::currentDate());
    de_contract_date->setDisplayFormat("dd MMMM yyyy");
    de_contract_date->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    gl->addWidget(de_contract_date, 5, 1, 1, 1);
    de_contract_date->hide();

    lb_customer_list = new QLabel("Заказчик");
    gl->addWidget(lb_customer_list, 6, 0, 1, 1);
    lb_customer_list->hide();
    cb_customer_list = new QComboBox;
    gl->addWidget(cb_customer_list, 6, 1, 1, 1);
    cb_customer_list->insertSeparator(-1);
    cb_customer_list->hide();
    g->customers(cb_customer_list);

    lb_pservice_list = new QLabel("Услуга");
    gl->addWidget(lb_pservice_list, 7, 0, 1, 1);
    cb_pservice_list = new QComboBox;
    gl->addWidget(cb_pservice_list, 7, 1, 1, 1);
    cb_pservice_list->insertSeparator(-1);
    g->pservices(cb_pservice_list);

    lb_event_date = new QLabel("Дата предоставления услуги");
    gl->addWidget(lb_event_date, 8, 0, 1, 1);
    de_event_date = new QDateEdit();
    de_event_date->setCalendarPopup(true);
    de_event_date->setDate(QDate::currentDate());
    de_event_date->setDisplayFormat("dd MMMM yyyy");
    de_event_date->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    gl->addWidget(de_event_date, 8, 1, 1, 1);

    lb_annotation = new QLabel("Пояснение");
    gl->addWidget(lb_annotation, 9, 0, 1, 1);
    le_annotation = new QLineEdit;
    gl->addWidget(le_annotation, 9, 1, 1, 1);

    QPushButton *pb_add = new QPushButton("Добавить");
    gl->addWidget(pb_add, 10, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_in_oper()));   // вызов функции создания базы данных и пользователя

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 11, 0, 1, 1);

    QWidget *wgt = new QWidget ();
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->minimumHeight();
    this->setWindowTitle("Добавление приходной операции");

    return 0;
}


// показ полей для ввода реквизитов договора
int add_in_oper_form::lb_doctype_list_changed(int i)
{
    if (i == 1)
    {
        lb_contract_num->hide();
        le_contract_num->hide();
        lb_contract_date->hide();
        de_contract_date->hide();
        lb_customer_list->hide();
        cb_customer_list->hide();
    }
    else if (i == 2)
    {
        lb_contract_num->show();
        le_contract_num->show();
        lb_contract_date->show();
        de_contract_date->show();
        lb_customer_list->show();
        cb_customer_list->show();
    }
    return 0;
}

// добавление приходной операции
int add_in_oper_form::add_in_oper()
{
    // проверка полей
    QString errors;
    errors = "";
    if (le_sum_in_oper->text() == "")
        errors = errors + "Не введена сумма\n";
    if (cb_branches_list->currentIndex() == false)
        errors = errors + "Не выбран дом культуры\n";
    if (cb_doctype_list->currentIndex() == false)
        errors = errors + "Не выбран тип документа\n";
    if (cb_pservice_list->currentIndex() == false)
        errors = errors + "Не выбрана услуга\n";
    if (cb_doctype_list->currentIndex() == 2)
    {
        if (cb_customer_list->currentIndex() == false)
            errors = errors + "Не выбран заказчик\n";
    }
    if (errors != "")
    {
        QMessageBox::critical(this, "Ошибка!", errors, QMessageBox::Ok);
        return 1;
    }

    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    // если тип документа - договор, то ставится дата договора
    QString contract_date;
    if (cb_doctype_list->currentIndex() == 2)
        contract_date = de_contract_date->date().toString("yyyy-MM-dd");
    else
        contract_date = "0000-00-00";

    // запись информации о приходной операции
    strsql.clear();
    strsql = "insert into in_operations (date_in_oper, sum_in_oper, id_branch, id_doc_type, contract_num, contract_date, id_customer, id_pservice, event_date, annotation) "
             "values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10')";
    strsql = strsql.arg(de_date_in_oper->date().toString("yyyy-MM-dd"))
                   .arg(le_sum_in_oper->text())
                   .arg(cb_branches_list->currentIndex())
                   .arg(cb_doctype_list->currentIndex())
                   .arg(le_contract_num->text())
                   .arg(contract_date)
                   .arg(cb_customer_list->currentIndex())
                   .arg(cb_pservice_list->currentIndex())
                   .arg(de_event_date->date().toString("yyyy-MM-dd"))
                   .arg(le_annotation->text());
    quer->exec(strsql);
    if (quer->isActive())
    {
        statusBar()->showMessage("Запись успешно добавлена");
    }
    else
    {
        statusBar()->showMessage("Ошибка при добавлении записи");
        qDebug() << __FILE__ << __LINE__ << quer->lastError().text();
    }

    return 0;
}

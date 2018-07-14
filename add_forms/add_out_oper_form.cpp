#include "add_out_oper_form.h"

add_out_oper_form::add_out_oper_form(QWidget *parent) : QMainWindow(parent)
{
    add_out_oper_form_show();
}

add_out_oper_form::~add_out_oper_form()
{
    db.close();
}

int add_out_oper_form::add_out_oper_form_show()
{
    QGridLayout *gl = new QGridLayout;
    getlist *g = new getlist;

    lb_date_out_oper = new QLabel("Дата оплаты");
    gl->addWidget(lb_date_out_oper, 0, 0, 1, 1);
    de_date_out_oper = new QDateEdit();
    de_date_out_oper->setCalendarPopup(true);
    de_date_out_oper->setDate(QDate::currentDate());
    de_date_out_oper->setDisplayFormat("dd MMMM yyyy");
    de_date_out_oper->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    gl->addWidget(de_date_out_oper, 0, 1, 1, 1);

    lb_sum_out_oper = new QLabel("Сумма");
    gl->addWidget(lb_sum_out_oper, 1, 0, 1, 1);
    le_sum_out_oper = new QLineEdit;
    gl->addWidget(le_sum_out_oper, 1, 1, 1, 1);
    le_sum_out_oper->setFocus();

    lb_branches_list = new QLabel("Дом культуры");
    gl->addWidget(lb_branches_list, 2, 0, 1, 1);
    cb_branches_list = new QComboBox;
    gl->addWidget(cb_branches_list, 2, 1, 1, 1);
    cb_branches_list->insertSeparator(-1);
    g->branches(cb_branches_list);

    lb_contract_num = new QLabel("Номер договора");
    gl->addWidget(lb_contract_num, 3, 0, 1, 1);
    le_contract_num = new QLineEdit;
    gl->addWidget(le_contract_num, 3, 1, 1, 1);

    lb_contract_date = new QLabel("Дата договора");
    gl->addWidget(lb_contract_date, 4, 0, 1, 1);
    de_contract_date = new QDateEdit();
    de_contract_date->setCalendarPopup(true);
    de_contract_date->setDate(QDate::currentDate());
    de_contract_date->setDisplayFormat("dd MMMM yyyy");
    de_contract_date->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    gl->addWidget(de_contract_date, 4, 1, 1, 1);

    lb_seller = new QLabel("Продавец");
    gl->addWidget(lb_seller, 5, 0, 1, 1);
    le_seller = new QLineEdit;
    gl->addWidget(le_seller, 5, 1, 1, 1);

    lb_goods = new QLabel("Товар / услуга");
    gl->addWidget(lb_goods, 6, 0, 1, 1);
    le_goods = new QLineEdit;
    gl->addWidget(le_goods, 6, 1, 1, 1);

    lb_annotation = new QLabel("Пояснение");
    gl->addWidget(lb_annotation, 7, 0, 1, 1);
    le_annotation = new QLineEdit;
    gl->addWidget(le_annotation, 7, 1, 1, 1);

    QPushButton *pb_add = new QPushButton("Добавить");
    gl->addWidget(pb_add, 8, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_out_oper()));

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 9, 0, 1, 1);

    QWidget *wgt = new QWidget ();
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->minimumHeight();
    this->setWindowTitle("Добавление расходной операции");

    return 0;
}

int add_out_oper_form::add_out_oper()
{
    // проверка полей
    QString errors;
    errors = "";
    if (le_sum_out_oper->text() == "")
        errors = errors + "Не введена сумма\n";
    if (cb_branches_list->currentIndex() == false)
        errors = errors + "Не выбран дом культуры\n";
    if (le_seller->text() == "")
        errors = errors + "Не введён продавец\n";
    if (le_goods->text() == "")
    {
        errors = errors + "Не введён товар (услуга)\n";
    }
    if (errors != "")
    {
        QMessageBox::critical(this, "Ошибка!", errors, QMessageBox::Ok);
        return 1;
    }

    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    // запись информации о приходной операции
    strsql.clear();
    strsql = "insert into out_operations (date_out_oper, sum_out_oper, id_branch, contract_num, contract_date, seller, goods, annotation) "
             "values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')";
    strsql = strsql.arg(de_date_out_oper->date().toString("yyyy-MM-dd"))
                   .arg(le_sum_out_oper->text())
                   .arg(cb_branches_list->currentIndex())
                   .arg(le_contract_num->text())
                   .arg(de_contract_date->date().toString("yyyy-MM-dd"))
                   .arg(le_seller->text())
                   .arg(le_goods->text())
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

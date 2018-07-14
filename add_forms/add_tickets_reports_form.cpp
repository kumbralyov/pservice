#include "add_tickets_reports_form.h"

add_tickets_reports_form::add_tickets_reports_form(QWidget *parent) : QMainWindow(parent)
{
    form_show();
}

add_tickets_reports_form::~add_tickets_reports_form()
{
    db.close();
}

int add_tickets_reports_form::form_show()
{
    QGridLayout *gl = new QGridLayout;
    getlist *g = new getlist;

    lb_tickets_reports_date = new QLabel("Дата отчёта");
    gl->addWidget(lb_tickets_reports_date, 0, 0, 1, 1);
    de_tickets_reports_date = new QDateEdit();
    de_tickets_reports_date->setCalendarPopup(true);
    de_tickets_reports_date->setDate(QDate::currentDate());
    de_tickets_reports_date->setDisplayFormat("dd MMMM yyyy");
    de_tickets_reports_date->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    gl->addWidget(de_tickets_reports_date, 0, 1, 1, 1);

    lb_branches_list = new QLabel("Дом культуры");
    gl->addWidget(lb_branches_list, 1, 0, 1, 1);
    cb_branches_list = new QComboBox;
    gl->addWidget(cb_branches_list, 1, 1, 1, 1);
    cb_branches_list->insertSeparator(-1);
    g->branches(cb_branches_list);

    lb_stub_amount = new QLabel("Количество\nкорешков");
    gl->addWidget(lb_stub_amount, 2, 0, 1, 1);
    le_stub_amount = new QLineEdit;
    gl->addWidget(le_stub_amount, 2, 1, 1, 1);
    le_stub_amount->setFocus();

    lb_stub_numbers = new QLabel("Номера\nкорешков");
    gl->addWidget(lb_stub_numbers, 3, 0, 1, 1);
    le_stub_numbers = new QLineEdit;
    gl->addWidget(le_stub_numbers, 3, 1, 1, 1);

    lb_shortage_amount = new QLabel("Количество\nиспорченных\n\(утерянных)\nбилетов");
    gl->addWidget(lb_shortage_amount, 4, 0, 1, 1);
    le_shortage_amount = new QLineEdit;
    gl->addWidget(le_shortage_amount, 4, 1, 1, 1);
    le_shortage_amount->setFocus();

    lb_shortage_numbers = new QLabel("Номера\nиспорченных\n\(утерянных)\nбилетов");
    gl->addWidget(lb_shortage_numbers, 5, 0, 1, 1);
    le_shortage_numbers = new QLineEdit;
    gl->addWidget(le_shortage_numbers, 5, 1, 1, 1);

    lb_return_amount = new QLabel("Количество\nвозвращённых\nбилетов");
    gl->addWidget(lb_return_amount, 6, 0, 1, 1);
    le_return_amount = new QLineEdit;
    gl->addWidget(le_return_amount, 6, 1, 1, 1);
    le_return_amount->setFocus();

    lb_return_numbers = new QLabel("Номера\nвозвращённых\nбилетов");
    gl->addWidget(lb_return_numbers, 7, 0, 1, 1);
    le_return_numbers = new QLineEdit;
    gl->addWidget(le_return_numbers, 7, 1, 1, 1);

    lb_cost = new QLabel("Номинальная цена");
    gl->addWidget(lb_cost, 8, 0, 1, 1);
    le_cost = new QLineEdit;
    gl->addWidget(le_cost, 8, 1, 1, 1);

    lb_annotation = new QLabel("Пояснение");
    gl->addWidget(lb_annotation, 9, 0, 1, 1);
    le_annotation = new QLineEdit;
    gl->addWidget(le_annotation, 9, 1, 1, 1);

    QPushButton *pb_add = new QPushButton("Добавить");
    gl->addWidget(pb_add, 10, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_tickets_reports()));

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 11, 0, 1, 1);

    QWidget *wgt = new QWidget ();
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->minimumHeight();
    this->setWindowTitle("Получение отчёта");

    return 0;
}

int add_tickets_reports_form::add_tickets_reports()
{
    // проверка полей
    QString errors;
    errors = "";
    if (cb_branches_list->currentIndex() == false)
        errors = errors + "Не выбран дом культуры\n";
    if (le_cost->text() == "")
        errors = errors + "Не введена цена билетов\n";
    if (errors != "")
    {
        QMessageBox::critical(this, "Ошибка!", errors, QMessageBox::Ok);
        return 1;
    }

    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    // запись информации о выданных билетах
    strsql.clear();
    strsql = "insert into tickets_reports(tickets_report_date, id_branch, tickets_stub_amount, "
             "tickets_stub_numbers, tickets_shortage_amount, tickets_shortage_numbers, tickets_return_amount, "
             "tickets_return_numbers, tickets_cost, annotation) "
             "values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10')";
    qDebug() << __FILE__ << __LINE__ << strsql;
    strsql = strsql.arg(de_tickets_reports_date->date().toString("yyyy-MM-dd"))
                   .arg(cb_branches_list->currentIndex())
                   .arg(le_stub_amount->text().toInt())
                   .arg(le_stub_numbers->text())
                   .arg(le_shortage_amount->text().toInt())
                   .arg(le_shortage_numbers->text())
                   .arg(le_return_amount->text().toInt())
                   .arg(le_return_numbers->text())
                   .arg(le_cost->text().toInt())
                   .arg(le_annotation->text());
    qDebug() << __FILE__ << __LINE__ << strsql;
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

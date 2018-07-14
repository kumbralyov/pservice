#include "add_tickets_out_form.h"

add_tickets_out_form::add_tickets_out_form(QWidget *parent) : QMainWindow(parent)
{
    form_show();
}

add_tickets_out_form::~add_tickets_out_form()
{
    db.close();
}

int add_tickets_out_form::form_show()
{
    QGridLayout *gl = new QGridLayout;
    getlist *g = new getlist;
    t = new tickets;

    lb_tickets_out_date = new QLabel("Дата оплаты");
    gl->addWidget(lb_tickets_out_date, 0, 0, 1, 1);
    de_tickets_out_date = new QDateEdit();
    de_tickets_out_date->setCalendarPopup(true);
    de_tickets_out_date->setDate(QDate::currentDate());
    de_tickets_out_date->setDisplayFormat("dd MMMM yyyy");
    de_tickets_out_date->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    gl->addWidget(de_tickets_out_date, 0, 1, 1, 1);

    lb_branches_list = new QLabel("Дом культуры");
    gl->addWidget(lb_branches_list, 1, 0, 1, 1);
    cb_branches_list = new QComboBox;
    gl->addWidget(cb_branches_list, 1, 1, 1, 1);
    cb_branches_list->insertSeparator(-1);
    g->branches(cb_branches_list);

    lb_amount = new QLabel("Количество");
    gl->addWidget(lb_amount, 2, 0, 1, 1);
    le_amount = new QLineEdit;
    gl->addWidget(le_amount, 2, 1, 1, 1);
    le_amount->setFocus();
//    connect(le_amount, SIGNAL(textChanged(QString)), this, SLOT(change_sum()));

    lb_cost = new QLabel("Цена");
    gl->addWidget(lb_cost, 3, 0, 1, 1);
    le_cost = new QLineEdit;
    gl->addWidget(le_cost, 3, 1, 1, 1);
    connect(le_cost, SIGNAL(textChanged(QString)), this, SLOT(change_sum()));

    lb_sum_text = new QLabel("Сумма");
    gl->addWidget(lb_sum_text, 4, 0, 1, 1);
    lb_sum = new QLabel("0");
    gl->addWidget(lb_sum, 4, 1, 1, 1);

    lb_numbers = new QLabel("Номера билетов");
    gl->addWidget(lb_numbers, 5, 0, 1, 1);
    le_numbers = new QLineEdit;
    t->set_le_tickets_format(le_numbers);
    gl->addWidget(le_numbers, 5, 1, 1, 1);
//    connect(le_numbers, SIGNAL(textChanged(QString)), this, SLOT(change_sum()));

    QPushButton *pb_add = new QPushButton("Добавить");
    gl->addWidget(pb_add, 6, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_tickets_out()));

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 7, 0, 1, 1);

    QWidget *wgt = new QWidget ();
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->minimumHeight();
    this->setWindowTitle("Выдача билетов");

    return 0;
}

int add_tickets_out_form::add_tickets_out()
{
    // проверка полей
    QString errors;
    errors = "";
    if (cb_branches_list->currentIndex() == false)
        errors = errors + "Не выбран дом культуры\n";
    if (le_amount->text() == "")
        errors = errors + "Не введено количество билетов\n";
    if (le_cost->text() == "")
        errors = errors + "Не введена цена билетов\n";
    if (le_numbers->text() == "")
        errors = errors + "Не введены номера билетов\n";
    if (errors != "")
    {
        QMessageBox::critical(this, "Ошибка!", errors, QMessageBox::Ok);
        return 1;
    }

//    if (add_view() == 1) return 2;

    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    // запись информации о выданных билетах
    strsql.clear();
    strsql = "insert into tickets_out(tickets_out_date, id_branch, tickets_out_amount, tickets_out_cost, tickets_out_numbers) "
             "values('%1', '%2', '%3', '%4', '%5')";
    strsql = strsql.arg(de_tickets_out_date->date().toString("yyyy-MM-dd"))
                   .arg(cb_branches_list->currentIndex())
                   .arg(le_amount->text())
                   .arg(le_cost->text())
                   .arg(le_numbers->text());
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

int add_tickets_out_form::add_view()
{
    QMessageBox* mb = new QMessageBox("Проверьте вводимую информацию",
                                      "text",
                                      QMessageBox::Icon(),
                                      QMessageBox::Yes,
                                      0,
                                      QMessageBox::Cancel | QMessageBox::Escape);
    int n = mb->exec();
    qDebug() << __FILE__ << __LINE__ << " n=" << n;
    delete mb;
    if (n == QMessageBox::Yes)
    {
        qDebug() << __FILE__ << __LINE__;
        return 0;
    }
    else if (n == QMessageBox::Cancel)
    {
        qDebug() << __FILE__ << __LINE__;
        return 1;
    }
    return 0;
}

int add_tickets_out_form::change_sum()
{
    float sum = 0;
//    t = new tickets(le_numbers->text());
//    le_amount->setText(QString::number(t->get_count()));
    sum = le_amount->text().toFloat() * le_cost->text().toFloat();
    lb_sum->setText(QString::number(sum));
    return 0;
}

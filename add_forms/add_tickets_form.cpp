#include "add_tickets_form.h"

#include <QRegExpValidator>

add_tickets_form::add_tickets_form(QWidget *parent) : QMainWindow(parent)
{
    form_show();
}

add_tickets_form::~add_tickets_form()
{
    db.close();
}

int add_tickets_form::form_show()
{
    QGridLayout *gl = new QGridLayout;

    lb_series = new QLabel("Серия");
    gl->addWidget(lb_series, 0, 0, 1, 1);
    le_series = new QLineEdit;
    le_series->setValidator(new QRegExpValidator(QRegExp("[А-Я,а-я,A-Z,a-z]{1,5}")));
    gl->addWidget(le_series, 0, 1, 1, 1);
    le_series->setFocus();

    lb_numbers = new QLabel("Номера");
    gl->addWidget(lb_numbers, 1, 0, 1, 1);

    gl->addWidget(new QLabel("с"), 2, 0, 1, 1);
    le_from = new QLineEdit;
    le_from->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,6}")));
    gl->addWidget(le_from, 2, 1, 1, 1);

    gl->addWidget(new QLabel("по"), 3, 0, 1, 1);
    le_to = new QLineEdit;
    le_to->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,6}")));
    gl->addWidget(le_to, 3, 1, 1, 1);

    QPushButton *pb_add = new QPushButton("Добавить");
    gl->addWidget(pb_add, 4, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_tickets()));

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 5, 0, 1, 1);

    QWidget *wgt = new QWidget ();
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->minimumHeight();
    this->setWindowTitle("Добавление билетов");

    return 0;
}

int add_tickets_form::add_tickets()
{
    // проверка полей
    QString errors;
    errors = "";
    if (le_series->text() == "")
        errors = errors + "Не введена серия\n";
    if (le_from->text() == "")
        errors = errors + "Не введены номера билетов (поле \"с\"\n";
    if (le_to->text() == "")
        errors = errors + "Не введены номера билетов (поле \"по\"\n";
    if (le_to->text().toInt() < le_from->text().toInt())
        errors = errors + "Неверный диапозон номеров билетов\n";
    if (errors != "")
    {
        QMessageBox::critical(this, "Ошибка!", errors, QMessageBox::Ok);
        return 1;
    }

    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    // запись информации о выданных билетах
    strsql.clear();
    QString series = "";
    series = le_series->text().toUpper();
    int from = 0;
    int to = 0;
    from = le_from->text().toInt();
    to = le_to->text().toInt();

    strsql = "insert into tickets(tickets_series, tickets_number, status, id_branch) "
             "values('%1', '%2', '0', '0')";
    strsql = strsql.arg(series)
                   .arg(le_from->text());

    for (int i = 0; i < to-from; i++)
    {
        strsql = strsql + ",('" + series + "', '" + QString::number(from+1+i) + "', '0', '0')";
    }

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

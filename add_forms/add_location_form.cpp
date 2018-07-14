#include "add_location_form.h"

add_location_form::add_location_form(QWidget *parent) : QMainWindow(parent)
{
    add_location_form_show();
}

add_location_form::~add_location_form()
{
    db.close();
}

int add_location_form::add_location_form_show()
{
    QGridLayout *gl = new QGridLayout;

    lb_location = new QLabel("Поселение");
    gl->addWidget(lb_location, 1, 0, 1, 1);
    le_location = new QLineEdit;
    gl->addWidget(le_location, 1, 1, 1, 1);

    QPushButton *pb_add = new QPushButton("Создать");
    gl->addWidget(pb_add, 2, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_location()));

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 3, 0, 1, 1);

    QWidget *wgt = new QWidget (this);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Добавление поселения");

    return 0;
}

int add_location_form::add_location()
{
    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    // запись информации о доме культуры
    strsql.clear();
    strsql = "insert into locations (location_name) values('%1')";
    strsql = strsql.arg(le_location->text());
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

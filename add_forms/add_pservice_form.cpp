#include "add_pservice_form.h"

add_pservice_form::add_pservice_form(QWidget *parent)
    : QMainWindow(parent)
{
    add_pservice_form_show();
}

add_pservice_form::~add_pservice_form()
{
    db.close();
}

int add_pservice_form::add_pservice_form_show()
{
    QGridLayout *gl = new QGridLayout;

    lb_pservice = new QLabel("Наименование");
    gl->addWidget(lb_pservice, 0, 0, 1, 1);
    le_pservice = new QLineEdit;
    gl->addWidget(le_pservice, 0, 1, 1, 1);
    le_pservice->setFocus();

    lb_price = new QLabel("Стоимость");
    gl->addWidget(lb_price, 1, 0, 1, 1);
    le_price = new QLineEdit;
    gl->addWidget(le_price, 1, 1, 1, 1);

    QPushButton *pb_add = new QPushButton("Создать");
    gl->addWidget(pb_add, 2, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_pservice()));   // вызов функции создания платной услуги

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 3, 0, 1, 1);

    QWidget *wgt = new QWidget (this);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Добавление платной услуги");

    return 0;
}

int add_pservice_form::add_pservice()
{
    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    // запись информации о платной услуге
    strsql.clear();
    strsql = "insert into paid_services (pservice_name, price) values('%1', '%2')";
    strsql = strsql.arg(le_pservice->text())
                   .arg(le_price->text());
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

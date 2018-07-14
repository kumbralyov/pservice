#include "add_branch_form.h"

add_branch_form::add_branch_form(QWidget *parent)
    : QMainWindow(parent)
{
    add_branch_form_show();
}

add_branch_form::~add_branch_form()
{
    db.close();
}

// форма добавления филиала
int add_branch_form::add_branch_form_show()
{
    QGridLayout *gl = new QGridLayout;
    getlist *g = new getlist;

    lb_branch = new QLabel("Название");
    gl->addWidget(lb_branch, 0, 0, 1, 1);
    le_branch = new QLineEdit;
    gl->addWidget(le_branch, 0, 1, 1, 1);
    le_branch->setFocus();

    lb_director = new QLabel("ФИО заведующего");
    gl->addWidget(lb_director, 1, 0, 1, 1);
    le_director = new QLineEdit;
    gl->addWidget(le_director, 1, 1, 1, 1);

    lb_location_list = new QLabel("Поселение");
    gl->addWidget(lb_location_list, 2, 0, 1, 1);
    cb_location_list = new QComboBox;
    gl->addWidget(cb_location_list, 2, 1, 1, 1);
    cb_location_list->insertSeparator(-1);
    g->locations(cb_location_list);

    lb_address = new QLabel("Адрес");
    gl->addWidget(lb_address, 3, 0, 1, 1);
    le_address = new QLineEdit;
    gl->addWidget(le_address, 3, 1, 1, 1);

    QPushButton *pb_add = new QPushButton("Создать");
    gl->addWidget(pb_add, 4, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_branch()));   // вызов функции создания базы данных и пользователя

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 5, 0, 1, 1);

    QWidget *wgt = new QWidget (this);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Добавление дома культуры");

    return 0;
}

// добавление филиала
int add_branch_form::add_branch()
{
    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    // запись информации о доме культуры
    strsql.clear();
    strsql = "insert into branches (branch_name, director_name, address, id_location) values('%1', '%2', '%3', '%4')";
    strsql = strsql.arg(le_branch->text())
                   .arg(le_director->text())
                   .arg(le_address->text())
                   .arg(cb_location_list->currentIndex());
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

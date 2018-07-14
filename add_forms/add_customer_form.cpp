#include "add_customer_form.h"

add_customer_form::add_customer_form(QWidget *parent)
    : QMainWindow(parent)
{
    add_customer_form_show();
}

add_customer_form::~add_customer_form()
{
    db.close();
}

int add_customer_form::add_customer_form_show()
{
    QGridLayout *gl = new QGridLayout;

    rb_org = new QRadioButton("юр. лицо");
    rb_org->setChecked(true);
    gl->addWidget(rb_org, 0, 0, 1, 1);
    connect(rb_org, SIGNAL(clicked()), this, SLOT(rb_org_click()));

    rb_ip = new QRadioButton("ИП / физ. лицо");
    rb_ip->setChecked(false);
    gl->addWidget(rb_ip, 0, 1, 1, 1);
    connect(rb_ip, SIGNAL(clicked()), this, SLOT(rb_ip_click()));

    lb_full_name = new QLabel("Полное название");
    gl->addWidget(lb_full_name, 2, 0, 1, 1);
    le_full_name = new QLineEdit;
    gl->addWidget(le_full_name, 2, 1, 1, 1);

    lb_abbr_name = new QLabel("Сокращённое название / имя");
    gl->addWidget(lb_abbr_name, 3, 0, 1, 1);
    le_abbr_name = new QLineEdit;
    gl->addWidget(le_abbr_name, 3, 1, 1, 1);

    lb_director_position = new QLabel("Должность руководителя");
    gl->addWidget(lb_director_position, 4, 0, 1, 1);
    le_director_position = new QLineEdit;
    gl->addWidget(le_director_position, 4, 1, 1, 1);

    lb_director_surname = new QLabel("Фамилия руководителя (или ИП)");
    gl->addWidget(lb_director_surname, 5, 0, 1, 1);
    le_director_surname = new QLineEdit;
    gl->addWidget(le_director_surname, 5, 1, 1, 1);

    lb_director_first_name = new QLabel("Имя руководителя (или ИП)");
    gl->addWidget(lb_director_first_name, 6, 0, 1, 1);
    le_director_first_name = new QLineEdit;
    gl->addWidget(le_director_first_name, 6, 1, 1, 1);

    lb_director_father_name = new QLabel("Отчество руководителя (или ИП)");
    gl->addWidget(lb_director_father_name, 7, 0, 1, 1);
    le_director_father_name = new QLineEdit;
    gl->addWidget(le_director_father_name, 7, 1, 1, 1);

    lb_address = new QLabel("Адрес");
    gl->addWidget(lb_address, 8, 0, 1, 1);
    le_address = new QLineEdit;
    gl->addWidget(le_address, 8, 1, 1, 1);

    lb_tin = new QLabel("ИНН");
    gl->addWidget(lb_tin, 9, 0, 1, 1);
    le_tin = new QLineEdit;
    gl->addWidget(le_tin, 9, 1, 1, 1);

    lb_kpp = new QLabel("КПП");
    gl->addWidget(lb_kpp, 10, 0, 1, 1);
    le_kpp = new QLineEdit;
    gl->addWidget(le_kpp, 10, 1, 1, 1);

    lb_bank_account = new QLabel("Расчётный счёт");
    gl->addWidget(lb_bank_account, 11, 0, 1, 1);
    le_bank_account = new QLineEdit;
    gl->addWidget(le_bank_account, 11, 1, 1, 1);

    lb_cor_account = new QLabel("Корреспондентский счёт");
    gl->addWidget(lb_cor_account, 12, 0, 1, 1);
    le_cor_account = new QLineEdit;
    gl->addWidget(le_cor_account, 12, 1, 1, 1);

    lb_bic = new QLabel("БИК");
    gl->addWidget(lb_bic, 13, 0, 1, 1);
    le_bic = new QLineEdit;
    gl->addWidget(le_bic, 13, 1, 1, 1);

    lb_bank_name = new QLabel("Название банка");
    gl->addWidget(lb_bank_name, 14, 0, 1, 1);
    le_bank_name = new QLineEdit;
    gl->addWidget(le_bank_name, 14, 1, 1, 1);

    lb_tel = new QLabel("Телефон");
    gl->addWidget(lb_tel, 15, 0, 1, 1);
    le_tel = new QLineEdit;
    gl->addWidget(le_tel, 15, 1, 1, 1);

    lb_other = new QLabel("Прочее");
    gl->addWidget(lb_other, 16, 0, 1, 1);
    le_other = new QLineEdit;
    gl->addWidget(le_other, 16, 1, 1, 1);

    QPushButton *pb_add = new QPushButton("Создать");
    gl->addWidget(pb_add, 17, 1, 1, 1);
    pb_add->setShortcut(QKeySequence(Qt::Key_Return));
    pb_add->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add, SIGNAL(clicked()), this, SLOT(add_customer()));   // вызов функции добавления заказчика

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 18, 0, 1, 1);

    QWidget *wgt = new QWidget (this);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->resize(700, this->height());
    this->setWindowTitle("Добавление заказчика");

    return 0;
}

int add_customer_form::add_customer()
{
    QString strsql;
    QSqlQuery *quer = new QSqlQuery(db);

    QString director_position = (le_director_position->text() != "") ? le_director_position->text() : "Индивидуальный предприниматель";

    // запись информации о заказчике
    strsql.clear();
    strsql = "insert into customers (`full_name`,  `abbr_name`,  `director_position`,  `director_surname`,  "
             "`director_first_name`,  `director_father_name`,  `address`,  `tin`,  `kpp`,  `bank_account`,  "
             "`cor_account`,  `bic`,  `bank_name`,  `tel`,  `other`) "
             "values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15')";
    strsql = strsql.arg(le_full_name->text())
                .arg(le_abbr_name->text())
                .arg(director_position)
                .arg(le_director_surname->text())
                .arg(le_director_first_name->text())
                .arg(le_director_father_name->text())
                .arg(le_address->text())
                .arg(le_tin->text())
                .arg(le_kpp->text())
                .arg(le_bank_account->text())
                .arg(le_cor_account->text())
                .arg(le_bic->text())
                .arg(le_bank_name->text())
                .arg(le_tel->text())
                .arg(le_other->text());
    quer->exec(strsql);
    if (quer->isActive())
    {
        statusBar()->showMessage("Запись успешно добавлена");
    }
    else
    {
        statusBar()->showMessage("Ошибка при добавлении записи");
        qDebug() << __FILE__ << __LINE__ << quer->lastError().text() << strsql;
    }

    return 0;
}

void add_customer_form::rb_org_click()
{
    lb_full_name->show();
    le_full_name->show();
    lb_director_position->show();
    le_director_position->show();
}

void add_customer_form::rb_ip_click()
{
    lb_full_name->hide();
    le_full_name->hide();
    lb_director_position->hide();
    le_director_position->hide();
}

#include "user_form.h"
#include "mainwindow.h"

user_form::user_form(QWidget *parent)
    : QMainWindow(parent)
{
    menu_cre();
    frm_cre();

    this->setWindowTitle("Внебюджетная деятельность");
}

user_form::~user_form()
{
    db.close();
}

// меню окна пользователя
int user_form::menu_cre()
{
    menu_bar = new QMenuBar;

    menu_bar->addAction("&Главная", this, SLOT(frm_cre()));

    QMenu *mnu_money = new QMenu("Учёт &денег", this);
    menu_bar->addMenu(mnu_money);
    mnu_money->addAction("добавить &приходную операцию", this, SLOT(add_in_oper_form_show()));
    mnu_money->addAction("добавить &расходную операцию", this, SLOT(add_out_oper_form_show()));
    mnu_money->addSeparator();
    mnu_money->addAction("реестр пр&иходных операций", this, SLOT(list_in_oper_form_show()));
    mnu_money->addAction("реестр р&асходных операций", this, SLOT(list_out_oper_form_show()));

    QMenu *mnu_tickets = new QMenu("&Учёт билетов", this);
    menu_bar->addMenu(mnu_tickets);
    mnu_tickets->addAction("в&ыдать билеты", this, SLOT(tickets_out_form_show()));
    mnu_tickets->addAction("п&олучить отчёт за билеты", this, SLOT(ticket_report_oper_form_show()));
    mnu_tickets->addSeparator();
    mnu_tickets->addAction("реестр &выданных билетов", this, SLOT(list_tickets_form_show()));
    mnu_tickets->addAction("реестр &принятых отчётов", this, SLOT(list_report_form_show()));

    QMenu *mnu_mng = new QMenu("У&правление", this);
    menu_bar->addMenu(mnu_mng);
    mnu_mng->addAction("добавить &дом культуры", this, SLOT(add_branch_form_show()));
    mnu_mng->addAction("добавить &платную услугу", this, SLOT(add_pservice_form_show()));
    mnu_mng->addAction("добавить &заказчика", this, SLOT(add_customer_form_show()));
    mnu_mng->addAction("добавить &поселение", this, SLOT(add_location_form_show()));

    QMenu *mnu_handbook = new QMenu("Сп&равочники", this);
    menu_bar->addMenu(mnu_handbook);
    mnu_handbook->addAction("&дома культуры", this, SLOT(branches_form_show()));
    mnu_handbook->addAction("&платные услуги", this, SLOT(pservices_form_show()));
    mnu_handbook->addAction("&заказчики", this, SLOT(customers_form_show()));

    QMenu *mnu_help = new QMenu(tr("&Справка"), this);
    menu_bar->addMenu(mnu_help);
    mnu_help->addAction("&О программе", this, SLOT(about_form_show()));

    menu_bar->addMenu(mnu_help);

    return 0;
}

// окно пользователя
int user_form::frm_cre()
{
    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);

    home *h = new home(this);
    gl->addWidget(h, 0, 0, 1, 1);

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->showMaximized();
    this->setWindowTitle("Внебюджетная деятельность");

    return 0;
}


//-- учёт денег
// форма добавления приходной операции
int user_form::add_in_oper_form_show()
{
    add_in_oper_form *aiof = new add_in_oper_form;
    aiof->show();
    return 0;
}

// форма добавления расходной операции
int user_form::add_out_oper_form_show()
{
    add_out_oper_form *aoof = new add_out_oper_form;
    aoof->show();
    return 0;
}

// форма списка приходных операций
int user_form::list_in_oper_form_show()
{
    list_in_oper_form *liof = new list_in_oper_form;
    liof->setMenuBar(menu_bar);
    this->setCentralWidget(liof);
    return 0;
}

// форма списка расходных операций
int user_form::list_out_oper_form_show()
{
    list_out_oper_form *loof = new list_out_oper_form;
    loof->setMenuBar(menu_bar);
    this->setCentralWidget(loof);
    return 0;
}

// форма отчёта по приходным операциям
int user_form::report_in_oper_form_show()
{
    return 0;
}

// форма отчёта по расходным операциям
int user_form::report_out_oper_form_show()
{
    return 0;
}

//-- учёт билетов
// форма выдачи билетов
int user_form::tickets_out_form_show()
{
    add_tickets_out_form *atof = new add_tickets_out_form;
    atof->show();
    return 0;
}

// форма получения отчёта за билеты
int user_form::ticket_report_oper_form_show()
{
    add_tickets_reports_form *atrf = new add_tickets_reports_form;
    atrf->show();
    return 0;
}

// форма списка выданных билетов
int user_form::list_tickets_form_show()
{
    list_tickets_out_form *ltof = new list_tickets_out_form;
    ltof->setMenuBar(menu_bar);
    this->setCentralWidget(ltof);
    return 0;
}

// форма списка полученных отчётов
int user_form::list_report_form_show()
{
    list_tickets_reports_form *ltpf = new list_tickets_reports_form;
    ltpf->setMenuBar(menu_bar);
    this->setCentralWidget(ltpf);
    return 0;
}

// форма списка билетов "на руках"
int user_form::tickets_inposs_form_show()
{
    return 0;
}


//-- управление
// форма добавления филиала
int user_form::add_branch_form_show()
{
    add_branch_form *abf = new add_branch_form;
    abf->show();
    return 0;
}

// форма добавления платной услуги
int user_form::add_pservice_form_show()
{
    add_pservice_form *apf = new add_pservice_form;
    apf->show();
    return 0;
}

// форма добавления заказчика
int user_form::add_customer_form_show()
{
    add_customer_form *acf = new add_customer_form;
    acf->show();
    return 0;
}

int user_form::add_location_form_show()
{
    add_location_form *alf = new add_location_form;
    alf->show();
    return 0;
}


//-- справочник
// форма перечня филиалов
int user_form::branches_form_show()
{
    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);

    QPushButton *pb_add_from = new QPushButton("Добавить дом культуры");
    gl->addWidget(pb_add_from, 0, 0, 1, 1);
    pb_add_from->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add_from, SIGNAL(clicked()), this, SLOT(add_branch_form_show()));   // вызов функции добавления дома культуры

    QString str_sql = "select branch_name, director_name, address, location_name "
                      "from branches left join locations on branches.id_location = locations.id_location "
                      "order by branch_name";

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(str_sql);

    model->setHeaderData(0, Qt::Horizontal, tr("Название"));
    model->setHeaderData(1, Qt::Horizontal, tr("Имя заведующего"));
    model->setHeaderData(2, Qt::Horizontal, tr("Адрес"));
    model->setHeaderData(3, Qt::Horizontal, tr("Поселение"));

    QSortFilterProxyModel *m = new QSortFilterProxyModel;
    m->setSourceModel(model);

    QTableView *tv_branches = new QTableView;
    tv_branches->setModel(m);
    tv_branches->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv_branches->setSortingEnabled(true);
    tv_branches->resizeColumnsToContents();
    gl->addWidget(tv_branches, 1, 0, 1, 1);

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);

    return 0;
}

// форма перечня платных услуг
int user_form::pservices_form_show()
{
    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);

    QPushButton *pb_add_from = new QPushButton("Добавить платную услугу");
    gl->addWidget(pb_add_from, 0, 0, 1, 1);
    pb_add_from->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add_from, SIGNAL(clicked()), this, SLOT(add_pservice_form_show()));   // вызов функции добавления платной услуги

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("paid_services");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->removeColumn(0); // не показывать ID
    model->setHeaderData(0, Qt::Horizontal, tr("Название"));
    model->setHeaderData(1, Qt::Horizontal, tr("Стоимость"));

    QTableView *tv_branches = new QTableView;
    tv_branches->setModel(model);
    tv_branches->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv_branches->setSortingEnabled(true);
    tv_branches->resizeColumnsToContents();
    gl->addWidget(tv_branches, 1, 0, 1, 1);

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);

    return 0;
}

// форма перечня заказчиков
int user_form::customers_form_show()
{
    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);

    QPushButton *pb_add_from = new QPushButton("Добавить заказчика");
    gl->addWidget(pb_add_from, 0, 0, 1, 1);
    pb_add_from->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    connect(pb_add_from, SIGNAL(clicked()), this, SLOT(add_customer_form_show()));   // вызов функции добавления заказчика

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("customers");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->removeColumn(0); // не показывать ID
    model->setHeaderData(0, Qt::Horizontal, tr("Полное название (юр. лица)"));
    model->setHeaderData(1, Qt::Horizontal, tr("Сокращённое название / ФИО ИП"));
    model->setHeaderData(2, Qt::Horizontal, tr("Должность руководителя"));
    model->setHeaderData(3, Qt::Horizontal, tr("Фамилия \nруководителя \n(или ИП)"));
    model->setHeaderData(4, Qt::Horizontal, tr("Имя \nруководителя \n(или ИП)"));
    model->setHeaderData(5, Qt::Horizontal, tr("Отчество \nруководителя \n(или ИП)"));
    model->setHeaderData(6, Qt::Horizontal, tr("Адрес"));
    model->setHeaderData(7, Qt::Horizontal, tr("ИНН"));
    model->setHeaderData(8, Qt::Horizontal, tr("КПП"));
    model->setHeaderData(9, Qt::Horizontal, tr("Расчётный счёт"));
    model->setHeaderData(10, Qt::Horizontal, tr("Корреспондентский счёт"));
    model->setHeaderData(11, Qt::Horizontal, tr("БИК"));
    model->setHeaderData(12, Qt::Horizontal, tr("Название банка"));
    model->setHeaderData(13, Qt::Horizontal, tr("Телефон"));
    model->setHeaderData(14, Qt::Horizontal, tr("Прочее"));

    QTableView *tv_branches = new QTableView;
    tv_branches->setModel(model);
    tv_branches->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv_branches->setSortingEnabled(true);
    tv_branches->resizeColumnsToContents();
    gl->addWidget(tv_branches, 1, 0, 1, 1);

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);

    return 0;
}


//-- справка
// о программе
int user_form::about_form_show()
{
    QMessageBox::information(0, "О программе", "(c) Anton Kumbralyov, 2018");
    return 0;
}

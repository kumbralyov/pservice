#ifndef USER_FRM_H
#define USER_FRM_H

#include "home.h"
#include "add_forms/add_in_oper_form.h"
#include "add_forms/add_out_oper_form.h"
#include "add_forms/add_branch_form.h"
#include "add_forms/add_pservice_form.h"
#include "add_forms/add_customer_form.h"
#include "add_forms/add_location_form.h"
#include "add_forms/add_tickets_out_form.h"
#include "add_forms/add_tickets_reports_form.h"
#include "add_forms/add_tickets_form.h"
#include "list_forms/list_in_oper_form.h"
#include "list_forms/list_out_oper_form.h"
#include "list_forms/list_tickets_out_form.h"
#include "list_forms/list_tickets_reports_form.h"
#include <math.h>
#include <QCommonStyle>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QErrorMessage>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QStatusBar>
#include <QDebug>
#include <QDateTime>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QTableView>
#include <QToolBar>
#include "mainwindow.h"

class user_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit user_form(QWidget *parent = 0);
    ~user_form();

    QSqlDatabase db;
    QLineEdit *le_login;

    int strg;
    int t_oper;

    QMenuBar *menu_bar;
    QToolBar *tool_bar;
    QLabel *lb_db;
    QLineEdit *le_db;
    QPushButton *pb_cre;

    QAction *reload;
    QAction *filter;

signals:

public slots:
    int menu_cre();                     // меню окна пользователя
    int frm_cre();                      // окно пользователя

    //-- функции, вызываемые из меню
    int add_in_oper_form_show();        // форма добавления приходной операции
    int add_out_oper_form_show();       // форма добавления расходной операции
    int list_in_oper_form_show();       // форма списка приходных операций
    int list_out_oper_form_show();      // форма списка расходных операций
    int report_in_oper_form_show();     // форма отчёта по приходным операциям
    int report_out_oper_form_show();    // форма отчёта по расходным операциям

    int tickets_out_form_show();        // форма выдачи билетов
    int ticket_report_oper_form_show(); // форма получения отчёта за билеты
    int list_tickets_form_show();       // форма списка выданных билетов
    int list_report_form_show();        // форма списка полученных отчётов
    int tickets_inposs_form_show();     // форма списка билетов "на руках"

    int add_branch_form_show();         // форма добавления филиала
    int add_pservice_form_show();       // форма добавления платной услуги
    int add_customer_form_show();       // форма добавления заказчика
    int add_location_form_show();       // форма добавления поселения

    int branches_form_show();           // форма перечня филиалов
    int pservices_form_show();          // форма перечня платных услуг
    int customers_form_show();          // форма перечня заказчиков

    int about_form_show();              // о программе
};

#endif // USER_FRM_H

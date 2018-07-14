#ifndef ADD_BRANCH_FORM_H
#define ADD_BRANCH_FORM_H

#include <getlist.h>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QStatusBar>
#include <QDebug>
#include <QSqlError>

class add_branch_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_branch_form(QWidget *parent = 0);
    ~add_branch_form();

    QSqlDatabase db;

    QLabel *lb_branch;
    QLineEdit *le_branch;
    QLabel *lb_director;
    QLineEdit *le_director;
    QLabel *lb_location_list;
    QComboBox *cb_location_list;
    QLabel *lb_address;
    QLineEdit *le_address;

signals:

public slots:
    int add_branch_form_show();         // форма добавления филиала
    int add_branch();                   // добавление филиала
};

#endif // ADD_BRANCH_FORM_H

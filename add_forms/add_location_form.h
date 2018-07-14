#ifndef ADD_LOCATION_FORM_H
#define ADD_LOCATION_FORM_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QPushButton>
#include <QSqlQuery>
#include <QStatusBar>
#include <QDebug>
#include <QSqlError>

class add_location_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit add_location_form(QWidget *parent = 0);
    ~add_location_form();

    QSqlDatabase db;

    QLabel *lb_location;
    QLineEdit *le_location;

signals:

public slots:
    int add_location_form_show();         // форма добавления поселения
    int add_location();                   // добавление поселения
};

#endif // ADD_LOCATION_FORM_H

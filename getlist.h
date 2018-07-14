#ifndef GETLIST_H
#define GETLIST_H

#include <QSqlQuery>
#include <QComboBox>
#include <QStatusBar>

class getlist
{
public:
    getlist();
    ~getlist();

    QSqlDatabase db;

public slots:
    int branches(QComboBox *cb);            // получение списка филиалов
    int doctypes(QComboBox *cb);            // получение типов документов
    int customers(QComboBox *cb);           // получение списка заказчиков
    int pservices(QComboBox *cb);           // получение списка платных услуг
    int locations(QComboBox *cb);           // получение списка платных услуг
};

#endif // GETLIST_H

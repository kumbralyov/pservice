#include "getlist.h"
#include "mainwindow.h"
#include "QDebug"

getlist::getlist()
{

}

getlist::~getlist()
{
    db.close();
}

// получение списка филиалов
int getlist::branches(QComboBox *cb)
{
    QSqlQuery *quer;
    QString strsql;
    quer = new QSqlQuery(db);
    strsql.clear();
    strsql = "select id_branch, branch_name from branches";
    quer->exec(strsql);
    if (quer->isActive())
    {
        while (quer->next())
        {
            cb->insertItem(quer->value(0).toInt(), quer->value(1).toString());
        }
    }
    return 0;
}

// получение типов документов
int getlist::doctypes(QComboBox *cb)
{
    QSqlQuery *quer;
    QString strsql;
    quer = new QSqlQuery(db);
    strsql.clear();
    strsql = "select id_doc_type, doc_type from doc_type";
    quer->exec(strsql);
    if (quer->isActive())
    {
        while (quer->next())
        {
            cb->insertItem(quer->value(0).toInt(), quer->value(1).toString());
        }
    }
    return 0;
}

// получение списка заказчиков
int getlist::customers(QComboBox *cb)
{
    QSqlQuery *quer;
    QString strsql;
    quer = new QSqlQuery(db);
    strsql.clear();
    strsql = "select id_customer, abbr_name from customers";
    quer->exec(strsql);
    if (quer->isActive())
    {
        while (quer->next())
        {
            cb->insertItem(quer->value(0).toInt(), quer->value(1).toString());
        }
    }
    return 0;
}

// получение списка платных услуг
int getlist::pservices(QComboBox *cb)
{
    QSqlQuery *quer;
    QString strsql;
    quer = new QSqlQuery(db);
    strsql.clear();
    strsql = "select id_pservice, pservice_name from paid_services order by pservice_name";
    quer->exec(strsql);
    if (quer->isActive())
    {
        while (quer->next())
        {
            cb->insertItem(quer->value(0).toInt(), quer->value(1).toString());
        }
    }
    return 0;
}

int getlist::locations(QComboBox *cb)
{
    QSqlQuery *quer;
    QString strsql;
    quer = new QSqlQuery(db);
    strsql.clear();
    strsql = "select id_location, location_name from locations order by location_name";
    quer->exec(strsql);
    if (quer->isActive())
    {
        while (quer->next())
        {
            cb->insertItem(quer->value(0).toInt(), quer->value(1).toString());
        }
    }
    return 0;
}

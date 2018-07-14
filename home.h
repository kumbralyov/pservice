#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QTableView>
#include <QTextEdit>
#include <QDebug>
#include <QSqlError>
#include "tickets.h"
#include "diagram.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDesktopWidget>
#include <QToolBar>
//#include <QtWebKit/QWebView>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFile>
#include <QTextDocument>

class home : public QMainWindow
{
    Q_OBJECT
public:
    explicit home(QWidget *parent = 0);
    ~home();

    QSqlDatabase db;

    QTableView *tv;

    QToolBar *tb;
    QTextEdit *te;

    diagram *d_branches;
    diagram *d_kinds;

signals:

public slots:
    int form_show();    
    QToolBar *tool_bar_create();    // панель инструментов
    QString table_data();
    QVector<diagram::d_data> branches_complete();
    QVector<diagram::d_data> kinds_complete();
    void print_prev();
    void print_prev(QImage img);
    void print(QPrinter *printer);
    void print(QPrinter *printer, QImage img);
    void save_doc();
    void save_img(QImage img);
};

#endif // HOME_H

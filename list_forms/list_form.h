#ifndef LIST_FORM_H
#define LIST_FORM_H

#include "getlist.h"
#include "home.h"
#include "footer.h"
#include <QMainWindow>
#include <QToolBar>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QGridLayout>
#include <QTableView>
#include <QTableWidgetItem>
#include <QSortFilterProxyModel>
#include <QTableWidgetItem>
#include <QGroupBox>
#include <QTextEdit>
#include <QDate>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QStatusBar>
#include <QDebug>
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QTextCodec>
#include <QWidget>
#include <QToolButton>
#include <QObject>
#include <QtCore>
#include <QtGui>

#ifdef Q_OS_WIN32
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#endif

class list_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit list_form(QWidget *parent = 0);
    ~list_form();

    QSqlDatabase db;

    QString cur_path;
    QString str_query;
    QString file_doc;
    QString file_path_doc;
    QString file_path_html;

    QString user_position;
    QString user_surname;
    QString user_first_name;
    QString user_father_name;

    QSortFilterProxyModel *m;
    QVector<int> sels;

    QToolBar *tb;
    QTextEdit *te_view;
    QWidget *filter;

    QSqlQueryModel *model;
    QTableWidget *tw;
    QTableView *tv;
    QString *table;
    footer *list_footer;

    QAction *ac_save_table;
    QAction *ac_save_doc_cur;
    QAction *ac_save_doc;
    QToolButton *tbn_save;
    QAction *ac_print_table;
    QAction *ac_print_doc_cur;
    QAction *ac_print_doc;
    QToolButton *tbn_print;
    QAction *ac_filter;
    QAction *ac_reload;
    QAction *ac_print;
    QAction *ac_save;
    QAction *ac_add;
    QAction *ac_search;

    QVector<QCheckBox*> cb_sels;

    struct str_replace
    {
        QString old_str;
        QString new_str;
    };

signals:

public slots:
    int form_show();                    // форма списка приходных операций
    void slotCustomMenuRequested(QPoint pos);
    int table_show(QVector<QString> s); // отображение таблицы
    QToolBar *tool_bar_create();        // панель инструментов
    void get_user_data();               // получить информацию о пользователе

    int filter_create();                // заглушка - создание формы фильтра
    virtual QString filter_string();    // заглушка - текст фильтры для строки запроса
    int filter_show();                  // показать / скрыть фильтр
    int filter_clear();                 // заглушка - очистить фильтр

    void set_selected(QWidget *cb);     // установить выделение / снять выделение

    int reload();                       // обновить таблицу
    int save_table();
    int save_doc(int i);
    int save_doc_cur();
    int save_doc_sel();
    int prev_table();
    int print_table(QPrinter *printer);
    int prev_doc_sel();
    int print_doc_sel(QPrinter *printer);
    int prev_doc_cur();
    int print_doc_cur(QPrinter *printer);
    virtual int add();
    virtual QVector<str_replace> replace(int row);  // определяет информацию, вносимую в документ
    QString money(double n);
};

#endif // LIST_FORM_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QStatusBar>
#include <QSettings>
#include <QCoreApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSettings settings;         // настройки программы
    QSqlDatabase db;
    QLabel *lb_db;
    QLineEdit *le_db;
    QLabel *lb_login;
    QLineEdit *le_login;
    QLabel *lb_pass;
    QLineEdit *le_pass;
    QPushButton *pb_conn;
    QGridLayout *gl;

public slots:
    int frm_cre();              // окно входа пользователя
    int user_form_show();       // вызов окна пользователя
    int le_pass_finish();       // делает активной кнопку создать после ввода пароля
    int pb_conn_click();        // соединение с базой данных
};

#endif // MAINWINDOW_H

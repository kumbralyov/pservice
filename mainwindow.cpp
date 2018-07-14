#include "mainwindow.h"
#include "user_form.h"
#include "tickets.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    #ifdef Q_OS_LINUX
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    #endif

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

    if (settings.contains("db/name") == true)   // если БД уже имеется (её название записано в settings)
        frm_cre();      // открывается окно входа в режим пользователя
    else
    {
        QMessageBox::critical(this, "Ошибка!", "База данных для этой программы не настроена. Обратитесь к администратору", QMessageBox::Ok);
        this->hide();
    }
}

MainWindow::~MainWindow()
{
    db.close();
}

// окно входа пользователя
int MainWindow::frm_cre()
{
    QGridLayout *gl = new QGridLayout;

    lb_login = new QLabel("Логин");             // надпись "логин"
    gl->addWidget(lb_login, 1, 0, 1, 1);

    le_login = new QLineEdit();          // поле ввода логина
    gl->addWidget(le_login, 1, 1, 1, 1);

    lb_pass = new QLabel("Пароль");             // надпись "пароль"
    gl->addWidget(lb_pass, 2, 0, 1, 1);

    le_pass = new QLineEdit();             // поле ввода пароля
    gl->addWidget(le_pass, 2, 1, 1, 1);
    le_pass->setEchoMode(QLineEdit::Password);  // неотображение пароля на экране
    connect(le_pass, SIGNAL(textEdited(QString)),this,SLOT(le_pass_finish()));   // активизация кнопки ввода после ввода пароля

    pb_conn = new QPushButton("Вход");          // кнопка ввода
    gl->addWidget(pb_conn, 3, 1, 1, 1);
//    pb_conn->setEnabled(false);               // кнопка делается неактивной
    pb_conn->setShortcut(QKeySequence(Qt::Key_Return));   // связь с клавишей return
    connect(pb_conn, SIGNAL(clicked()), this, SLOT(pb_conn_click()));   // вызов функции соединения с базой данных

    QWidget *wgt = new QWidget (this);  // создаётся окно
    wgt->setLayout(gl);                 // устанавливается сетка в окне
    this->setCentralWidget(wgt);
    this->resize(300, 100);
    this->move(200, 200);               // размеры формы
    this->setTabOrder(le_login, le_pass);   // порядок перрехода по tab
    this->setTabOrder(le_pass, pb_conn);    // порядок перрехода по tab
    this->setWindowTitle("Вход");       // название окна

    return 0;
}

// вызов окна пользователя
int MainWindow::user_form_show()
{
    user_form *ufrm = new user_form();
    ufrm->show();
    return 0;
}

// делает активной кнопку создать после ввода пароля
int MainWindow::le_pass_finish()
{
    if (le_pass->text() != "")
        pb_conn->setEnabled(true);    // если в поле ввода введён пароль - кнопка ввода делается активной
    else
        pb_conn->setEnabled(false);   // иначе - неактивной
    return 0;
}

// соединение с базой данных
int MainWindow::pb_conn_click()
{
    db = QSqlDatabase::addDatabase("QMYSQL");   // создаётся база данных

    db.setHostName("localhost");        // название хоста
    db.setPort(3306);                   // номер порта
    db.setDatabaseName(settings.value("db/name").toString());  // название базы данных
    db.setUserName(le_login->text());   // имя пользователя
    db.setPassword(le_pass->text());    // пароль

    if (db.open())
    {
        statusBar()->showMessage("Соединение установлено");   // вывод результата соединения с базой данных в статусную строку
        user_form_show();   // вход пользователя
        this->hide();
    }
    else
    {
        statusBar()->showMessage("Соединение не установлено");   // вывод результата соединения с базой данных в статусную строку
    }
    return 0;
}

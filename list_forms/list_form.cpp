#include "list_form.h"
#include "mainwindow.h"
#include "user_form.h"

#include <QToolButton>
#include <QWebView>
#include <QWebFrame>

list_form::list_form(QWidget *parent) : QMainWindow(parent)
{    
    cur_path = (new QFileInfo("."))->canonicalPath();
    form_show();
    get_user_data();
}

list_form::~list_form()
{
    db.close();
}

// форма списка приходных операций
int list_form::form_show()
{
    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);

    // добавление панели инструментов
    this->addToolBar(tool_bar_create());

    // создание фильтра
    this->filter_create();
    filter->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    gl->addWidget(filter, 0, 0, 2, 1);
    filter->hide();

    model = new QSqlQueryModel;

    tv = new QTableView;
    tv->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tv->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tv, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    gl->addWidget(tv, 0, 1, 1, 1);

    list_footer = new footer(model);
    list_footer->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    gl->addWidget(list_footer, 1, 1, 1, 1);

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);

    return 0;
}

void list_form::slotCustomMenuRequested(QPoint pos)
{    
    ac_save_doc_cur = new QAction(QIcon(), "сохранить документ", this);
    connect(ac_save_doc_cur, SIGNAL(triggered()), this, SLOT(save_doc_cur()));

    ac_print_doc_cur = new QAction(QIcon(), "распечатать документ", this);
    connect(ac_print_doc_cur, SIGNAL(triggered()), this, SLOT(prev_doc_cur()));

    QMenu * menu = new QMenu(this);
    menu->addAction(ac_save_table);
    menu->addAction(ac_save_doc_cur);
    menu->addAction(ac_save_doc);
    menu->addSeparator();
    menu->addAction(ac_print_table);
    menu->addAction(ac_print_doc_cur);
    menu->addAction(ac_print_doc);
    menu->addSeparator();
    menu->addAction(ac_reload);
    menu->popup(tv->viewport()->mapToGlobal(pos));
}

int list_form::table_show(QVector<QString> s)
{
    reload();

    // устанавливаются заголовки столбцов
    for (int i = 0; i < s.size(); i++)
    {
        m->setHeaderData(i+1, Qt::Horizontal, s[i]);
    }
    m->setHeaderData(0, Qt::Horizontal, "");

    tv->resizeColumnsToContents();

    return 0;
}

// панель инструментов
QToolBar *list_form::tool_bar_create()
{
    tb = new QToolBar;

    ac_save_table = new QAction(QIcon(), "сохранить таблицу", this);
    connect(ac_save_table, SIGNAL(triggered()), this, SLOT(save_table()));

    ac_save_doc = new QAction(QIcon(), "сохранить отмеченные документы", this);
    connect(ac_save_doc, SIGNAL(triggered()), this, SLOT(save_doc_sel()));

    tbn_save = new QToolButton();
    tbn_save->setPopupMode(QToolButton::InstantPopup);
    tbn_save->setIcon(QIcon(":/img/save-pic"));
    tbn_save->addAction(ac_save_table);
    tbn_save->addAction(ac_save_doc);
    tb->addWidget(tbn_save);

    ac_print_table = new QAction(QIcon(), "распечатать таблицу", this);
    connect(ac_print_table, SIGNAL(triggered()), this, SLOT(prev_table()));

    ac_print_doc = new QAction(QIcon(), "распечатать отмеченные документы", this);
    connect(ac_print_doc, SIGNAL(triggered()), this, SLOT(prev_doc_sel()));

    tbn_print = new QToolButton();
    tbn_print->setPopupMode(QToolButton::InstantPopup);
    tbn_print->setIcon(QIcon(":/img/print-pic"));
    tbn_print->addAction(ac_print_table);
    tbn_print->addAction(ac_print_doc);
    tb->addWidget(tbn_print);

    ac_filter = new QAction(QIcon(":/img/filter-pic"), "Показать фильтр", this);
    connect(ac_filter, SIGNAL(triggered()), this, SLOT(filter_show()));
    tb->addAction(ac_filter);

    ac_reload = new QAction(QIcon(":/img/reload-pic"), "Обновить", this);
    connect(ac_reload, SIGNAL(triggered()), this, SLOT(reload()));
    tb->addAction(ac_reload);

    ac_add = new QAction(QIcon(":/img/add-pic"), "Обновить", this);
    connect(ac_add, SIGNAL(triggered()), this, SLOT(add()));
    tb->addAction(ac_add);

    return tb;
}

void list_form::get_user_data()
{
     QSqlQuery *quer;
     QString strsql;
     quer = new QSqlQuery(db);
     strsql.clear();
     strsql = "select position, surname, first_name, father_name from users";
     quer->exec(strsql);
     if (quer->isActive())
     {
         while (quer->next())
         {
             user_position = quer->value(0).toString();
             user_surname = quer->value(1).toString();
             user_first_name = quer->value(2).toString();
             user_father_name = quer->value(3).toString();
         }
     }
}

// заглушка - создание формы фильтра
int list_form::filter_create()
{
    filter = new QWidget();
    return 0;
}

// заглушка - текст фильтры для строки запроса
QString list_form::filter_string()
{
    return "";
}

// показать / скрыть фильтр
int list_form::filter_show()
{
    if (filter->isHidden())
    {
        filter->show();
        ac_filter->setText("Скрыть фильтр");
    }
    else
    {
        filter->hide();
        ac_filter->setText("Показать фильтр");
    }
    return 0;
}

// заглушка - очистить фильтр
int list_form::filter_clear()
{
    return 0;
}

void list_form::set_selected(QWidget *cb)
{
    if (static_cast<QCheckBox*>(cb)->isChecked())
        sels.append(cb->objectName().toInt());
    else
        sels.remove(cb->objectName().toInt());
    list_footer->recount_sel(sels);
}

int list_form::reload()
{
    model->setQuery(filter_string());
    model->insertColumn(0);
    list_footer->set_shift(1);
    m = new QSortFilterProxyModel;
    m->setSourceModel(model);

    tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv->setSortingEnabled(true);
    tv->setModel(m);
    tv->resizeColumnsToContents();

    for (int i = 0; i < m->rowCount(); i++)
    {
        QSignalMapper * mapper = new QSignalMapper(this);
        QObject::connect(mapper,SIGNAL(mapped(QWidget*)),this,SLOT(set_selected(QWidget*)));
        QCheckBox *chb = new QCheckBox;
        chb->setObjectName(QString::number(i));
        connect(chb, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(chb, chb);
        cb_sels.append(chb);
        tv->setIndexWidget(m->index(i, 0), chb);
    }

    list_footer->recount_all();

    return 0;
}

int list_form::save_table()
{
    QString table = "<table border=\"1\" width=\"100%\" cellspacing=\"-1\" cellpadding=\"5\">";
    table += "<tr class=\"top\">";
    for (int i = 1; i < m->columnCount(); i++)
    {
        table += "<td>" + m->headerData(i, Qt::Horizontal).toString() + "</td>";
    }
    table += "</tr>";
    for (int i = 0; i < m->rowCount(); i++)
    {
        table += "<tr>";
        for (int j = 1; j < m->columnCount(); j++)
        {
            table += "<td>" + m->data(m->index(i, j)).toString() + "</td>";
        }
        table += "</tr>";
    }
    table += "</table>";

#ifdef Q_OS_WIN32
    QString sfx = "doc";
#endif

#ifdef Q_OS_LINUX
    QString sfx = "odt";
#endif

    QFileDialog fd;
    fd.setDefaultSuffix(sfx);
    QString str = fd.getSaveFileName(this, QString("Сохранить документ"), "file."+sfx, "Тестовые файлы (*."+sfx+")", nullptr);

    QTextDocument textDocument;
    textDocument.setHtml(table);
    QTextDocumentWriter writer(str);
#ifdef Q_OS_WIN32
    writer.setFormat("html");
#endif
#ifdef Q_OS_LINUX
    writer.setFormat("odt");
#endif
    writer.write(&textDocument);

    return 0;
}

int list_form::save_doc(int i)
{
    #ifdef Q_OS_WIN32

    QVector<str_replace> replaces = replace(i);

    QAxObject * word = new QAxObject("Word.Application");
    word->querySubObject("Documents")->querySubObject("Open(const QVariant&)", cur_path+"/pservice/docs/"+file_doc);

    word->querySubObject("Selection")->querySubObject("Find");

    if (word->isNull())
    {
        (new QErrorMessage(this))->showMessage("Файл "+file_doc+" не найден!");
        return 1;
    }

    QList<QVariant> params;
    for (int i = 0; i < replaces.size(); i++)
    {
        params.operator << (QVariant(replaces[i].old_str));
        params.operator << (QVariant(false));
        params.operator << (QVariant(false));
        params.operator << (QVariant(false));
        params.operator << (QVariant(false));
        params.operator << (QVariant(false));
        params.operator << (QVariant(true));
        params.operator << (QVariant(false));
        params.operator << (QVariant(false));
        params.operator << (QVariant(replaces[i].new_str));
        params.operator << (QVariant("2"));
        params.operator << (QVariant(false));
        params.operator << (QVariant(false));
        params.operator << (QVariant(false));
        params.operator << (QVariant(false));

        word->querySubObject("Selection")->querySubObject("Find")->dynamicCall("Execute(const QVariant&,const QVariant&,"
                       "const QVariant&, const QVariant&, const QVariant&, const QVariant&, const QVariant&, "
                       "const QVariant&, const QVariant&, const QVariant&, const QVariant&, const QVariant&, "
                       "const QVariant&, const QVariant&, const QVariant&)",
                       params);
        params.clear();
    }

    QFileDialog *fd = new QFileDialog;
    QString str = fd->getSaveFileName(this, QString("Сохранить документ"), QString(), QString("(*.doc)\n (*.odt)\n (*.html)"), nullptr);
    QVariant newFileName(str);

    word->querySubObject("ActiveDocument")->querySubObject("SaveAs(const QVariant&, const QVariant&)", newFileName);

    word->querySubObject("ActiveDocument")->dynamicCall("Close()");
    word->dynamicCall("Quit()");

    #endif

    #ifdef Q_OS_LINUX

    QVector<str_replace> replaces = replace(i);

    QFile file(file_path_html);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;
    QString html = QString(file.readAll());

    for (int i = 0; i < replaces.size(); i++)
    {
        html.replace(replaces[i].old_str, replaces[i].new_str);
    }

//    QString sfx = "odt";
    QString sfx = "pdf";

    QFileDialog fd;
    fd.setDefaultSuffix(sfx);
    QString str = fd.getSaveFileName(this, QString("Сохранить документ"), "file."+sfx, "Тестовые файлы (*."+sfx+")", nullptr);

//    QTextDocument textDocument;
//    textDocument.setHtml(html);
//    QTextDocumentWriter writer(str);
//    writer.setFormat("odt");
//    writer.write(&textDocument);

    QWebView *webView = new QWebView;
    webView->setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(str);
//    textDocument.print(&printer);
    webView->print(&printer);

    #endif

    return 0;
}

int list_form::save_doc_cur()
{
    save_doc(tv->currentIndex().row());
    return 0;
}

int list_form::save_doc_sel()
{
    QString s = "";
    for (int i = 0; i < sels.size(); i++)
    {
        save_doc(sels[i]);
    }
    return 0;
}

int list_form::prev_table()
{
    QPrinter printer;
    printer.setPageMargins(30, 20, 15, 20, QPrinter::Millimeter);
    QPrintPreviewDialog *prev = new QPrintPreviewDialog(&printer);
    connect(prev, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print_table(QPrinter*)));
    prev->exec();
    delete prev;

    return 0;
}

int list_form::print_table(QPrinter *printer)
{
    QString table = "<table border=\"1\" width=\"100%\" cellspacing=\"-1\" cellpadding=\"5\">";
    table += "<tr class=\"top\">";
    for (int i = 1; i < m->columnCount(); i++)
    {
        table += "<td>" + m->headerData(i, Qt::Horizontal).toString() + "</td>";
    }
    table += "</tr>";
    for (int i = 0; i < m->rowCount(); i++)
    {
        table += "<tr>";
        for (int j = 1; j < m->columnCount(); j++)
        {
            table += "<td>" + m->data(m->index(i, j)).toString() + "</td>";
        }
        table += "</tr>";
    }
    table += "</table>";

    QTextDocument textDocument;
    textDocument.setHtml(table);
    textDocument.setPageSize(QSizeF(printer->pageRect().size()));
    textDocument.print(printer);

    return 0;
}

int list_form::prev_doc_sel()
{
    QPrinter printer;
    printer.setPageMargins(30, 20, 15, 20, QPrinter::Millimeter);
    QPrintPreviewDialog *prev = new QPrintPreviewDialog(&printer);
    connect(prev, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print_doc_sel(QPrinter*)));
    prev->exec();
    delete prev;

    return 0;
}

int list_form::print_doc_sel(QPrinter* printer)
{
    #ifdef Q_OS_LINUX

    QWebView *webView = new QWebView;
    QWebPage page;
    page.setView(webView);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QPainter painter;
    painter.begin(printer);
    for (int i = 0; i < sels.size(); i++)
    {
        QVector<str_replace> replaces = replace(sels[i]);

        QFile file(file_path_html);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return 1;
        QString html = QString(file.readAll());

        for (int j = 0; j < replaces.size(); j++)
        {
            html.replace(replaces[j].old_str, replaces[j].new_str);
        }

        page.mainFrame()->setHtml(html);
        page.mainFrame()->render(&painter);

        if (i < sels.size()-1)
            printer->newPage();

    }

    painter.end();

    #endif

    return 0;
}

int list_form::prev_doc_cur()
{
    QPrinter printer;
    printer.setPageMargins(10, 20, 5, 20, QPrinter::Millimeter);
    QPrintPreviewDialog *prev = new QPrintPreviewDialog(&printer);
    connect(prev, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print_doc_cur(QPrinter*)));
    prev->exec();
    delete prev;

    return 0;
}

int list_form::print_doc_cur(QPrinter *printer)
{
    QWebView *webView = new QWebView;
    QWebPage page;
    page.setView(webView);
    page.setViewportSize(printer->pageRect().size());

    QPainter painter;
    painter.begin(printer);

    QVector<str_replace> replaces = replace(tv->currentIndex().row());

    QFile file(file_path_html);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;
    QString html = QString(file.readAll());

    for (int j = 0; j < replaces.size(); j++)
    {
        html.replace(replaces[j].old_str, replaces[j].new_str);
    }

    page.mainFrame()->setHtml(html);
    page.mainFrame()->render(&painter);

    painter.end();

    return 0;
}

int list_form::add()
{
    return 0;
}

QVector<list_form::str_replace> list_form::replace(int row)
{
    QVector<str_replace> r = {};
    return r;
}

QString list_form::money(double n)
{
    if ( n > 999999999999.99 )
        return QString::fromUtf8("Очень много денег ...");

    if ( n < 0 )
        return QString::fromUtf8("Отрицательная сумма !");

    static QString cap[4][10] =
    {
        {
            "",
            QString::fromUtf8("один "),
            QString::fromUtf8("два "),
            QString::fromUtf8("три "),
            QString::fromUtf8("четыре "),
            QString::fromUtf8("пять "),
            QString::fromUtf8("шесть "),
            QString::fromUtf8("семь "),
            QString::fromUtf8("восемь "),
            QString::fromUtf8("девять ")
        },
        {
            "",
            QString::fromUtf8("одна "),
            QString::fromUtf8("две "),
            QString::fromUtf8("три "),
            QString::fromUtf8("четыре "),
            QString::fromUtf8("пять "),
            QString::fromUtf8("шесть "),
            QString::fromUtf8("семь "),
            QString::fromUtf8("восемь "),
            QString::fromUtf8("девять ")
        },
        {
            "",
            "",
            QString::fromUtf8("двадцать "),
            QString::fromUtf8("тридцать "),
            QString::fromUtf8("сорок "),
            QString::fromUtf8("пятьдесят "),
            QString::fromUtf8("шестьдесят "),
            QString::fromUtf8("семьдесят "),
            QString::fromUtf8("восемьдесят "),
            QString::fromUtf8("девяносто ")
        },
        {
            "",
            QString::fromUtf8("сто "),
            QString::fromUtf8("двести "),
            QString::fromUtf8("триста "),
            QString::fromUtf8("четыреста "),
            QString::fromUtf8("пятьсот "),
            QString::fromUtf8("шестьсот "),
            QString::fromUtf8("семьсот "),
            QString::fromUtf8("восемьсот "),
            QString::fromUtf8("девятьсот ")
        }
    };

    static QString cap2[10] =
    {
        QString::fromUtf8("десять "),
        QString::fromUtf8("одиннадцать "),
        QString::fromUtf8("двенадцать "),
        QString::fromUtf8("тринадцать "),
        QString::fromUtf8("четырнадцать "),
        QString::fromUtf8("пятнадцать "),
        QString::fromUtf8("шестнадцать "),
        QString::fromUtf8("семнадцать "),
        QString::fromUtf8("восемнадцать "),
        QString::fromUtf8("девятнадцать ")
    };

    static QString cap3[5][3] =
    {
        {
            QString::fromUtf8("копейка "),
            QString::fromUtf8("копейки "),
            QString::fromUtf8("копеек ")
        },
        {
            QString::fromUtf8("рубль, "),
            QString::fromUtf8("рубля, "),
            QString::fromUtf8("рублей, ")
        },
        {
            QString::fromUtf8("тысяча "),
            QString::fromUtf8("тысячи "),
            QString::fromUtf8("тысяч ")
        },
        {
            QString::fromUtf8("миллион "),
            QString::fromUtf8("милиона "),
            QString::fromUtf8("миллионов ")
        },
        {
            QString::fromUtf8("миллиард "),
            QString::fromUtf8("миллиарда "),
            QString::fromUtf8("миллиардов ")
        }
    };

    QString s;

    qlonglong nn = ((qlonglong)(n)*10000 + (qlonglong)(n*1000) % 1000 + 5 ) / 10;

    qlonglong lo = 0;
    qlonglong hi = nn;
    int r[3];
    int rod;

    for ( int nPor = 0; true; ++nPor )
    {
        QString olds = s;
        s = "";

        lo = hi%1000;
        hi = hi/1000;

        if ((nPor == 1) && (lo == 0) && (hi == 0))
        {
            s = QString::fromUtf8("ноль ") + cap3[1][2] + olds;
            break;
        }

        for ( int nRaz = 0; nRaz < 3; ++nRaz )
        {
            r[nRaz] = lo%10;
            lo      = lo/10;
        }

        switch ( nPor )
        {
            case 0:
            case 1:
            case 2:
                rod = 1;
                break;
            default:
                rod = 0;
        }

        QString capt;
        if (r[1] != 1)
        {
            if (r[0] == 1)
                capt = cap3[nPor][0];
            else if ((r[0] > 1 ) && (r[0] < 5))
                capt = cap3[nPor][1];
        }
        if (capt.isEmpty())
            capt = cap3[nPor][2];

        if (nPor == 0)
        {
            s = QString::number(r[1]) + QString::number(r[0]) + " " + capt;
            continue;
        }
        if (nPor == 1)
            rod = 0;

        s += cap[2+1][r[2]];
        s += ((r[1] == 1) ? cap2[r[0]] : cap[1+1][r[1]]+cap[0+rod][r[0]])+capt;
        s += olds;

        if ((hi == 0) && (nPor >= 1))
            break;
    }
    QString up(s[0]);
    s.replace(0,1,up);
    return s;
}
